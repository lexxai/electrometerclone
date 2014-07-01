/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

#include "system.h"

/* Refer to the device datasheet for information about available
oscillator configurations. */
void ConfigureOscillator(void)
{
   //OSCCONbits.IRCF = 0b111;  //8 Mhz
   OSCCONbits.IRCF = 0b110;  //4 Mhz
   //OSCCONbits.IRCF = 0b100;  //1 Mhz
   //OSCCONbits.IRCF = 0b011;  //500 khz
   //OSCCONbits.IRCF = 0b001;  //125 khz
   //OSCCONbits.IRCF = 0b000;  //31 khz
   //OSCCONbits.HTS= 1; // 1 = HFINTOSC Status bit (High Frequency – 8 MHz to 125 kHz) HFINTOSC is stable
   //OSCCONbits.LTS= 1; // LFINTOSC Stable bit (Low Frequency – 31 kHz)
   //OSCCONbits.SCS =1;
}
