/*
 * ������ � ����������� ������������������ ������������ �� �������� HD44780 ��� ��� ������������
 * ������ Catcatcat electronics
 * ����� ���� ������ 2013-2014
 * ������ - 1.0
 * ������ - 1.1 ����������� �������� �������  String �� StringLCD
 * ������ - 1.2 ��������� ������ SendLCDd � SendLCDc - ��� ��������� �������� ������, ���� �������������� ������� SendLCDdata
 * ������ - 1.3 Microchip MPLAB XC8 C Compiler V1.12
 * ������ - 2.0 Microchip MPLAB XC8 C Compiler V1.30 ���������� ������ �� ����� ��������� ���������
 */
//------------------------------------------------------------------------- 
 
#pragma jis					// ��������� ���������������� �� ��������� �������� � ����������� �����
#include "../system.h"

#include "../unionLATC.h"

//-------------------------------------------------------------------------
/*
���������� �������������, ��� ��� ������ ����������� ������������ ���� ���� �����������
������������ 4 ������ ���������, ��� �������� ������������ 4 ������� ���� �����


#define	LCD	PORTB			// ����������� �����
#define	LCD_TRIS TRISB			//
#define	E	RB3			// ����������� E
#define	RW	RB2			// ����������� RW
#define	RS	RB1			// ����������� RS
#define	LCD_LED	RC6			// ����������� ����� ���������� ����������
*/
//#define	LCD	PORTC			// ����������� �����
//#define	LCD_LAT	LATPORTC.byte		// ����������� ����� LAT
//
//#define	LCD_TRIS TRISC			//
//#define	E	PORTCbits.RC3			// ����������� E
//#define	RW	PORTCbits.RC2			// ����������� RW
//#define	RS	PORTCbits.RC1			// ����������� RS
//#define	LCD_LED	PORTCbits.RC0			// ����������� ����� ���������� ����������
//
//#define	E_LAT	LATPORTC.bits.RC3			// ����������� E
//#define	RW_LAT	LATPORTC.bits.RC2			// ����������� RW
//#define	RS_LAT	LATPORTC.bits.RC1			// ����������� RS
//#define	LCD_LED_LAT	LATPORTC.bits.RC0			// ����������� ����� ���������� ����������
//#define LCD_LAT_FLUSH LATPORTC_FLUSH


#define	LCD	PORTC			// ����������� �����
#define	LCD_LAT	LATPORTC.byte		// ����������� ����� LAT

#define	LCD_TRIS TRISC			//
#define	E	PORTCbits.RC3			// ����������� E
#define	RW	PORTCbits.RC2			// ����������� RW
#define	RS	PORTCbits.RC1			// ����������� RS
#define	LCD_LED	PORTCbits.RC0			// ����������� ����� ���������� ����������

#define	E_LAT	LATPORTC.bits.RC3			// ����������� E
#define	RW_LAT	LATPORTC.bits.RC2			// ����������� RW
#define	RS_LAT	LATPORTC.bits.RC1			// ����������� RS
#define	LCD_LED_LAT	LATPORTC.bits.RC0			// ����������� ����� ���������� ����������
#define LCD_LAT_FLUSH LATPORTC_FLUSH


//-------------------------------------------------------------------------

void InitLCD(void); // ������� ��������� ������������� �������
void ClearLCD(void); // ������� �����������
void DisplayLCD(unsigned char state); // 
void StringLCD(const unsigned char *str); // ����� ������ � ��������� ������� 
void CursorLCD(unsigned char stroka,unsigned char stolbec); // ��������� ������� ������ 0-3/������� 0-40
void SendLCDdata(unsigned char data, unsigned char rs); // ������, 0-�������/1-������
void SendLCDd(unsigned char data); // ������
void SendLCDc(unsigned char data); // �������

//-------------------------------------------------------------------------
