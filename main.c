/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
#include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
#include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>        /* For uint8_t definition */
#include <stdlib.h>
#include <stdbool.h>       /* For true/false definition */

#include "globals.h"      /* Gloval variables */
#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */
#include <string.h>
#include <stdio.h>
#include "unionLATC.h"     /*Structure for Ports LATCH*/
#include "lib/LCDHD44780.h"

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
//CONSTANTS
// Visual names of devices
#define DEVICES 2
#define LCD_STRING 12
const char DEVICE_NAME[DEVICES][4] = {"к45", "к46"};
// device ticks per 0.1 device values ,if for dedice value 1 used 3200 tick, use 320.
const uint16_t DEVICE_DIVIDER[] = {40, 40};
// start values of devices
volatile uint16_t device_tick[] = {0, 0};
volatile int16_t timer = 0;

volatile bit lcd_need_refresh;

// Primary Data Type with eeprom qualifier
eeprom unsigned long device_value_e[] = {11115, 9999000};

volatile bit display_state;
bit tmpbit;

/******************************************************************************/
/* Functions                                           */

/******************************************************************************/


void ledchange(void) {
    LCD_LED_LAT = 1 - LCD_LED_LAT;
    LCD_LAT_FLUSH;
}

void lcd_sleep(void) {
    LCD_LAT = (LCD_LED_LAT) ? 0xFF : 0;
    LCD_LAT_FLUSH;
    //ledchange();
}

char * splitdecimal(unsigned long id) {
    // 123456.7
    char buff1 [7 + 1];
    static char buff2 [7 + 2];
    uint8_t i, j = 0;
    sprintf(buff1, "%07lu", id);
    for (i = 0; i<sizeof (buff1); i++) {
        if (i == (sizeof (buff1) - 2)) buff2[j++] = '.';
        buff2[j++] = buff1[i];
    }
    return buff2;
}

void printlcd(void) {
    if (LCD_LED_LAT && display_state && lcd_need_refresh) {
        //uldiv_t r;
        char buff[13];
        //r = uldiv(device_value[0], 10);
        //sprintf(buff, "%s:%06lu.%1u", DEVICE_NAME[0], r.quot, r.rem);
        sprintf(buff, "%s:%s", DEVICE_NAME[0], splitdecimal(device_value[0]));
        //r = uldiv(device_value[1], 10);
        CursorLCD(0, 0);
        StringLCD(buff);
        //sprintf(buff, "%s:%06lu.%1u", DEVICE_NAME[1], r.quot, r.rem);
        sprintf(buff, "%s:%s", DEVICE_NAME[1], splitdecimal(device_value[1]));
        CursorLCD(1, 0);
        StringLCD(buff);
        lcd_sleep();
        lcd_need_refresh = 0;
    }
}

void device_ticked(uint8_t id) {
    device_tick[id]++;
    if (device_tick[id] >= DEVICE_DIVIDER[id]) {
        device_tick[id] = 0;
        device_value[id]++;
        //detect overflow of max device values
        if (device_value[id] > 9999999) device_value[id] = 0;
        device_value_e[id] = device_value[id]; //store to eeprom
        lcd_need_refresh = 1;
    }
}

void lcd_on(void) {
    ledchange();
    __delay_us(1);
    InitLCD(); // функция начальной инициализации дисплея
    ClearLCD(); // очистка ииндикатора
    display_state = 1;
}

void lcd_off(void) {
    LCD_LED_LAT = 0;
    lcd_sleep();
    //ledchange();
}

void display_on(void) {
    display_state = 1;
    DisplayLCD(display_state);
}

void display_off(void) {
    display_state = 0;
    DisplayLCD(display_state);
}

void kickisr(uint8_t id) {
    device_value[id] += 10;
    lcd_need_refresh = 1;
}

void InitComparator(void) {
    //Comparator mode #1
    ANSELbits.ANS1 = 1; // analog mode AN1 18 pin
    TRISAbits.TRISA1 = 1; // input mode AN1
    CM1CON0bits.C1OE = 0; // 0 = C1OUT is internal only
    CM1CON0bits.C1CH = 0; // CIN+ AN1 18 pin C12IN0-
    CM1CON0bits.C1R = 1; // 1 = C1VIN+ connects to C1VREF output
    CM1CON0bits.C1POL = 0; // 1 = C1OUT logic is inverted
    CM1CON0bits.C1OUT = 1; // C1OUT = 1 when C1VIN+ > C1VIN

    VRCONbits.C1VREN = 1;
    VRCONbits.VP6EN = 0;
    VRCONbits.VRR = 1;
    VRCONbits.VR = 2; // 0.25V (VDD=3V)

    CM1CON0bits.C1ON = 1; // Comparator C1 is enabled

    INTCONbits.PEIE = 1; //peripheral  interrupt enable
    PIE2bits.C1IE = 1; //enable peripheral  compare 1
    PIR2bits.C1IF = 0; //reset flag peripheral  compare 1
}

void InitULPWU(void) {
    PCONbits.ULPWUE = 1;
    TRISAbits.TRISA0 = 0; //output mode A0
    PORTAbits.RA0 = 1; //set initial state for interupt on change state

    ANSELbits.ANS0 = 0; // 0 - Digital I/O
    WPUAbits.WPUA0 = 0; //0 = Pull-up disabled
    TRISAbits.TRISA0 = 1; //input mode A0
    IOCAbits.IOCA0 = 1; //interrupt on change state
    INTCONbits.RABIE = 1; //RAB     Interrupt ENABLE
    INTCONbits.RABIF = 0; //RAB     RESET Interrupt FLAG
}

void InitDeviceFromEEPROM(void) {
    unsigned char i;
    //init from eerpom
    for (i = 0; i < DEVICES; i++) {
        device_value[i] = device_value_e[i];
    }
}


/******************************************************************************/
/* Main Program                                                               */

/******************************************************************************/


void main(void) {
    unsigned char i;
    int16_t tmp;
    int16_t t;
    uint16_t j, ledoff = 0;

    ConfigureOscillator();
    CLRWDT();
    InitDeviceFromEEPROM();
    /* Initialize I/O and Peripherals for application */
    CLRWDT();
    InitApp();
    lcd_need_refresh = 1;
    lcd_on();

    INTCONbits.GIE = 1; //Global Interrupt ENABLE

    //    TMR1=5;
    //    Sensor2.timerstart = 64000;
    //
    //    tmp = TMR1 - Sensor2.timerstart;

    //    if (tmp > 500) {
    printlcd();
    //    }
    while (1) {
        CLRWDT();
        //PORTA;
        PORTA;
        INTCONbits.RABIF = 0;
        SLEEP();
        NOP();

        //Analize Interrupt on Change
        if (IOC) {//INTCONbits.RABIF
            IOC = 0;
            if (BSELECT_IO != ButtonSelect.state) {
                BSELECT_IOC = 0; // disbale Interupt On Change for this
                ButtonSelect.state = !ButtonSelect.state;
                LED_IO = ButtonSelect.state;
                ButtonSelect.debounce = 0xFF;
                if (ButtonSelect.state == 0) {
                    ButtonSelect.timerstart = TMR1;
                } else if (ButtonSelect.timerstart) {
                    tmp = TMR1 - ButtonSelect.timerstart;
                    if (tmp > BUTTON_LONGPRESS_MIN_TIME) {
                        ButtonSelect.long_press = 1;
                    } else if (tmp > BUTTON_PRESS_MIN_TIME) {
                        ButtonSelect.press = 1;
                    }
                }
            }

            //debouncing loop
            while (ButtonSelect.debounce /*| ButtonMode.debounce | Sensor1.debounce | Sensor2.debounce*/) {
                __delay_us(500);
                if (ButtonSelect.debounce) {
                    ButtonSelect.debounce = (ButtonSelect.debounce << 1);
                    ButtonSelect.debounce = ButtonSelect.debounce | ((ButtonSelect.state) ? (!BSELECT_IO & 0x1) : BSELECT_IO);
                    if (ButtonSelect.debounce == 0) {
                        //now stable state in button
                        BSELECT_IOC = 1; //enable IOC for this
                    }
                }
            }

            //PORTA;
            //INTCONbits.RABIF = 0; // ready for new wake from sleep by IOC

            // Work with state
            if (ButtonSelect.press) {
                ButtonSelect.press = 0;
                ButtonSelect.timerstart = 0;
                //tmp = TMR1 - ButtonSelect.timerstart;
                // device_value[0] = tmp;
                kickisr(0);
                lcd_need_refresh = 1;
                // kickisr(0);
            } else if (ButtonSelect.long_press) {
                ButtonSelect.long_press = 0;
                //tmp = TMR1 - ButtonSelect.timerstart;
                //device_value[1] = tmp;
                kickisr(1);
                lcd_need_refresh = 1;
                if (LCD_LED_LAT) {
                    lcd_off();
                } else {
                    lcd_on();
                }
            }

            if (ButtonMode.press) {
                ButtonMode.press = 0;
                device_value[1] = (unsigned long) TMR1;
                lcd_need_refresh = 1;
                // kickisr(0);
            } else if (ButtonMode.long_press) {
                ButtonMode.long_press = 0;
                device_value[1] = 555000;
                //            if (LCD_LED_LAT) {
                //                lcd_off();
                //            } else {
                //                lcd_on();
                //            }
            }

            if (Sensor1.press) {
                Sensor1.press = 0;
                kickisr(0);
                tmp = TMR1 - Sensor1.timerstart;
                device_value[1] = tmp;
                lcd_need_refresh = 1;
            }
            if (Sensor2.press) {
                Sensor2.press = 0;
                kickisr(1);
                tmp = Sensor2.state;
                device_value[0] = tmp;
                lcd_need_refresh = 1;

            }


        }; //(INTCONbits.RABIF)


        //        if (STATUSbits.nTO | STATUSbits.nPD == 0) {
        //            //Wakeup by WDT
        //            timer++;
        //        }

        printlcd();

    }
}