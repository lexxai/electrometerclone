/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/

#if defined(__XC)
#include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
#include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */
#include "globals.h"
#include "user.h"
#include "system.h"



/******************************************************************************/
/* Interrupt Routines                                                         */
/******************************************************************************/

/* Baseline devices don't have interrupts. Note that some PIC16's 
 * are baseline devices.  Unfortunately the baseline detection macro is 
 * _PIC12 */
#ifndef _PIC12

//volatile unsigned long device_value[];

void interrupt isr(void) {

    volatile static int16_t tmp;
    volatile static bit tmpb;
    volatile static uint8_t LPORTA;
    /* This code stub shows general interrupt handling.  Note that these
    conditional statements are not handled within 3 seperate if blocks.
    Do not use a seperate if block for each interrupt flag to avoid run
    time errors. */

#if 1
    if (PIR1bits.TMR1IF) {
        PIR1bits.TMR1IF = 0;
        seconds += 16;
    } else if (INTCONbits.RABIF) {
        IOC = 1;
        PORTA;
        INTCONbits.RABIF = 0;
    }

#else
    //start PORTAB on Change Interrrupt
    if (INTCONbits.RABIF) {
        // LPORTAbits=PORTAbits;
        // ButtonSelect.press = 1;
        //start checking sensors
        //SENSOR 1
        if (S1_IO != Sensor1.state) {
            S1_IOC = 0; // disbale Interupt On Change for this
            Sensor1.state = !Sensor1.state;
            Sensor1.debounce = 0xFF;
            if (Sensor1.state == 0) {
                Sensor1.timerstart = TMR1;
            } else {
                tmp = TMR1 - Sensor2.timerstart;
                if (tmp > SENSOR_MIN_TIME) {
                    Sensor1.press = 1;
                }
            }
        }
        //SENSOR 2
        if (S2_IO != Sensor2.state) {
            S2_IOC = 0; // disbale Interupt On Change for this
            Sensor2.state = !Sensor2.state;
            Sensor2.debounce = 0xFF;
            if (Sensor2.state == 0) {
                Sensor2.timerstart = TMR1;
            } else {
                tmp = TMR1 - Sensor2.timerstart;
                if (tmp > SENSOR_MIN_TIME) {
                    Sensor2.press = 1;
                }
            }
        }
        //BUTTON SELECT
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
        //BUTTON MODE
        if (BMODE_IO != ButtonMode.state) {
            BMODE_IOC = 0; // disbale Interupt On Change for this
            ButtonMode.state = !ButtonMode.state;
            ButtonMode.debounce = 0xFF;
            if (ButtonMode.state == 0) {
                ButtonMode.timerstart = TMR1;
            } else {
                tmp = TMR1 - ButtonMode.timerstart;
                if (tmp > BUTTON_LONGPRESS_MIN_TIME) {
                    ButtonMode.long_press = 1;
                } else if (tmp > BUTTON_PRESS_MIN_TIME) {
                    ButtonMode.press = 1;
                }
            }
        }
        //end checking sensors
        INTCONbits.RABIF = 0; // reset Interrrupt Flas
        //end PORTAB on Change Interrrupt

    } else if (PIR1bits.TMR1IF) {
        PIR1bits.TMR1IF = 0;
        seconds += 16;
    }
    //    else if (<Interrupt Flag 2>)
    //    {
    //        <Interrupt Flag 2=0>; /* Clear Interrupt Flag 2 */
    //    }
    //    else
    //    {
    //        /* Unhandled interrupts */
    //    }

#endif

}
#endif


