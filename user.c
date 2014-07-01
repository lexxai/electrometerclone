/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
#include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
#include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */
#include "user.h"
#include "unionLATC.h"     /*Structure for Ports LATCH*/
#include "lib/LCDHD44780.h"
#include "globals.h"

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

void InitIOC(void) {
    ANSEL = 0; // Analog / Digial ports. 0 - Digital I/O
    WPUA = 0; //  Pull-up. 0 =  disabled
    //set initial state for interupt on change state

    //LED_TRIS = 0; //output
    //LED_IO = 0; //off
    Sensor1.state = 1;
    Sensor2.state = 1;
    ButtonSelect.state = 1;
    ButtonMode.state = 1;
    // set input / output mode
    S1_TRIS = 1; //input mode
    S2_TRIS = 1; //input mode
    BSELECT_TRIS = 1; //input mode
    BMODE_TRIS = 1; //input mode
    NOP();
    //    Sensor1.state=S1_IO;
    //    Sensor2.state=S2_IO;
    //    ButtonSelect.state=BSELECT_IO;
    //    ButtonMode.state= BMODE_IO;

    Sensor1.state = 1;
    Sensor2.state = 1;
    ButtonSelect.state = 1;
    ButtonMode.state = 1;

    Sensor1.detecting = 0;
    Sensor2.detecting = 0;
    ButtonSelect.detecting = 0;
    ButtonMode.detecting = 0;

     ButtonSelect.timerstart = 0;
     ButtonSelect.debounce = 0;

    // set Interupt on Change enable bit
    S1_IOC = 0; //sensor 1
    S2_IOC = 0; //sensor 2
    BSELECT_IOC = 1; //button select
    BMODE_IOC = 0; //button mode
    PORTA;
    INTCONbits.RABIF = 0; //RAB     RESET Interrupt FLAG
    INTCONbits.RABIE = 1; //RAB     Interrupt ENABLE
}

void InitTimer1(void) {
    T1CONbits.T1OSCEN = 1; //Timer1 use INTOSC (internal Timer1 Oscillator 32.768 kHz )
    T1CONbits.TMR1CS = 1; //Timer1 not use Fosc/4, use INTOSC
    T1CONbits.T1CKPS = 0b11; //Timer1 prescaler 1=max 2sec,2=max 4sec,4=max 8sec,8=max 16sec
    T1CONbits.nT1SYNC = 1; //in sleep Timer1  work only in asynchronously mode
    T1CONbits.TMR1GE = 0; // Timer1 Gate Enable = 1

    TRISAbits.TRISA4 = 1;
    TRISAbits.TRISA5 = 1;

    TMR1 = 0;
    __delay_ms(1);
    T1CONbits.TMR1ON = 1; //Enable Timer1
    PIE1bits.TMR1IE = 1;
    INTCONbits.PEIE = 0;
}

void InitApp(void) {
    LCD_TRIS = 0;
    //WATCH_DOG
    //WDTCONbits.SWDTEN=1;     // WDT is turned on
    OPTION_REGbits.PSA = 1; //PSA = 1 (Prescaler Assignment bit 1 = Prescaler is assigned to the WDT)
    OPTION_REGbits.PS = 0b111; // PS = 1:128
    //WDTCONbits.WDTPS=0b110; // 16-bit WDT Prescaler 1:2048  SUM = 8s
    //WDTCONbits.WDTPS=0b0100; // 16-bit WDT Prescaler 1:512  SUM = 2s
    //WDTCONbits.WDTPS=0b0011; // 16-bit WDT Prescaler 1:256  SUM = 1.04s
    //WDTCONbits.WDTPS=0b0010; // 16-bit WDT Prescaler 1:128  SUM = 0.52s
    WDTCONbits.WDTPS = 0b0001; // 16-bit WDT Prescaler 1:64  SUM = 0.251s
    /* TODO Initialize User Ports/Peripherals/Project here */

    /* Setup analog functionality and port direction */

    /* Initialize peripherals */

    /* Enable interrupts */


    InitTimer1();
    InitIOC();
}

