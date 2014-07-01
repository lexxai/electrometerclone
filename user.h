/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/

PORTAbits_t LPORTAbits;

#define S1_IO  LPORTAbits.RA2
#define S1_TRIS  TRISAbits.TRISA2
#define S1_IOC  IOCAbits.IOCA2
#define S2_IO  LPORTAbits.RA3
#define S2_TRIS  TRISAbits.TRISA3
#define S2_IOC  IOCAbits.IOCA3
#define BSELECT_IOL  LPORTAbits.RA0
#define BSELECT_IO  PORTAbits.RA0
#define BSELECT_TRIS  TRISAbits.TRISA0
#define BSELECT_IOC  IOCAbits.IOCA0
#define BMODE_IO  LPORTAbits.RA1
#define BMODE_TRIS  TRISAbits.TRISA1
#define BMODE_IOC  IOCAbits.IOCA1

#define LED_IO  PORTBbits.RB4
#define LED_TRIS TRISBbits.TRISB4
#define LED_ANSEL ANSELbits.ANS3

/* TODO Application specific user parameters used in user.c may go here */

/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/



/* TODO User level functions prototypes (i.e. InitApp) go here */

void InitApp(void);         /* I/O and Peripheral Initialization */
