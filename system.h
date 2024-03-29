/******************************************************************************/
/* System Level #define Macros                                                */
/******************************************************************************/

/* TODO Define system operating frequency */

/* Microcontroller MIPs (FCY) */

#define _XTAL_FREQ 4000000
//#define _XTAL_FREQ 1000000
//#define _XTAL_FREQ 500000
//#define _XTAL_FREQ 125000
//#define _XTAL_FREQ 31000

#define SYS_FREQ        {_XTAL_FREQ}L
#define FCY             SYS_FREQ/4


/******************************************************************************/
/* System Function Prototypes                                                 */
/******************************************************************************/

/* Custom oscillator configuration funtions, reset source evaluation
functions, and other non-peripheral microcontroller initialization functions
go here. */

void ConfigureOscillator(void); /* Handles clock switching/osc initialization */