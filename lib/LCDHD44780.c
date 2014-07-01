/*
 * ������ � ����������� ������������������ ������������ �� �������� HD44780 ��� ��� ������������
 * ������ Catcatcat electronics
 * ����� ���� ������ 2013-2014
 * ������ - 1.0
 * ������ - 1.1 ����������� �������� �������  String �� StringLCD
 * ������ - 1.2 ��������� ������ SendLCDd � SendLCDc - ��� ��������� �������� ������, ���� �������������� ������� SendLCDdata
 * ������ - 1.3 Microchip MPLAB XC8 C Compiler V1.12
 * ������ - 2.0 Microchip MPLAB XC8 C Compiler V1.30 ���������� ������ �� ����� ��������� ���������
 * 2.1 LAT tune
 *///-------------------------------------------------------------------------

#include <xc.h>							// ����������� ��������� ��������
#include "LCDHD44780.h"						// ���������� ������ � ����������� �� �������� HD44780

//-------------------------------------------------------------------------

// �������������� - ��������������
const char SHRIFT[];

void SendLCDc(unsigned char data) // ������, �������/������
{
unsigned char temp;

    temp=LCD_LAT&0b00001111;		//
    LCD_LAT = data|temp;			//
    RW_LAT = 0;				// ����� ������ � ���������
    RS_LAT = 0;				// 0-�������/1-������
    E_LAT = 1;				// ������ ������
    LCD_LAT_FLUSH;
    __delay_us(1);
    E_LAT = 0;    
    LCD_LAT_FLUSH;
    temp=LCD_LAT&0b00001111;		//
    LCD_LAT = (data << 4)|temp;		//
    E_LAT = 1;				// pulse E
    LCD_LAT_FLUSH;   
    __delay_us(1);
    E_LAT = 0;
    LCD_LAT_FLUSH;   
    // �������� �� ��������� ����������
//    LCD_TRIS = 0xF0;			// ��������� R0--R4 �� ����
//    RS_LAT = 0;				// ������ ������
//    RW_LAT = 1;				// ����� ������
//    data = 0xFF;                         // ��������� ������
//    while (data & 0b10000000)        // ��������� ��������� �����
//    {
//        E_LAT = 1;			        // �������� ������� ��������
//        LCD_LAT_FLUSH;
//        __delay_us(1);
//        E_LAT = 0;			        //
//        LCD_LAT_FLUSH;
//        data = LCD;                     //  ��������� ������
//        E_LAT = 1;			        // �������� ������� ��������
//        LCD_LAT_FLUSH;
//        __delay_us(1);
//        E_LAT = 0;
//        LCD_LAT_FLUSH;
//    }
    __delay_us(10);
//    LCD_TRIS = 0;			// ��������� ���� �� �����
}//

void SendLCDd(unsigned char data) // ������, �������/������
{
unsigned char temp;

    temp=LCD_LAT&0b00001111;		//
    LCD_LAT = data|temp;			//
    RW_LAT = 0;				// ����� ������ � ���������
    RS_LAT = 1;				// 0-�������/1-������
    E_LAT = 1;				// ������ ������
    LCD_LAT_FLUSH;       
    __delay_us(1);			//
    E_LAT = 0;                              //
    LCD_LAT_FLUSH;      
    temp=LCD_LAT&0b00001111;		//
    LCD_LAT = (data << 4)|temp;		//
    E_LAT = 1;				// pulse E
    LCD_LAT_FLUSH;      
    __delay_us(1);			//
    E_LAT = 0;                      	//
    LCD_LAT_FLUSH;   
    // �������� �� ��������� ����������
//    LCD_TRIS = 0xF0;			// ��������� R7-R4 �� ����
//    RS_LAT = 0;				// ������ ������
//    RW_LAT = 1;				// ����� ������
//    data = 0xFF;                         // ��������� ������
//    while (data & 0b10000000)        // ��������� ��������� �����
//    {
//        E_LAT = 1;			        // �������� ������� ��������
//        LCD_LAT_FLUSH;
//        __delay_us(1);
//        E_LAT = 0;			        //
//        LCD_LAT_FLUSH;
//        data = LCD;                     //  ��������� ������
//        E_LAT = 1;			        // �������� ������� ��������
//        LCD_LAT_FLUSH;
//        __delay_us(1);
//        E_LAT = 0;
//        LCD_LAT_FLUSH;
//    }
    __delay_us(10);
 //   LCD_TRIS = 0;			// ��������� ���� �� �����
}//

void SendLCDdata(unsigned char data, unsigned char rs) // ������, �������/������
{
unsigned char temp;

    temp=LCD_LAT&0b00001111;		//
    LCD_LAT = data|temp;			//
    RW_LAT = 0;				// ����� ������ � ���������
    RS_LAT = rs;				// 0-�������/1-������
    E_LAT = 1;				// ������ ������
    LCD_LAT_FLUSH;            
    __delay_us(1);
    E_LAT = 0;
    LCD_LAT_FLUSH;
    temp=LCD_LAT&0b00001111;
    LCD_LAT = (data << 4)|temp;
    E_LAT = 1;				// pulse E
    LCD_LAT_FLUSH;  
    __delay_us(1);
    E_LAT = 0;
    LCD_LAT_FLUSH;
    // �������� �� ��������� ����������
//    LCD_TRIS = 0xF0;			// ��������� R0--R4 �� ����
//    RS_LAT = 0;				// ������ ������
//    RW_LAT = 1;				// ����� ������
//    data = 0xFF;                         // ��������� ������
//    while (data & 0b10000000)        // ��������� ��������� �����
//    {
//        E_LAT = 1;			        // �������� ������� ��������
//        LCD_LAT_FLUSH;
//        __delay_us(1);
//        E_LAT = 0;			        //
//        LCD_LAT_FLUSH;
//        data = LCD;                     //  ��������� ������
//        E_LAT = 1;			        // �������� ������� ��������
//        LCD_LAT_FLUSH;
//        __delay_us(1);
//        E_LAT = 0;
//        LCD_LAT_FLUSH;
//    }
    __delay_us(10);
//    LCD_TRIS = 0;			// ��������� ���� �� �����
}//

void InitLCD(void) // ������� ��������� ������������ �������
{
	char a,temp;
	__delay_ms(10);
	__delay_ms(10);
	__delay_ms(10);
	RW_LAT=0;//����� ������ � �������
	RS_LAT=0;//����� ������
        LCD_LAT_FLUSH;
	for ( a = 0; a < 4; a++ )
	{
            temp=LCD_LAT&0b00001111;
            LCD_LAT = 0b00110000|temp;	// ��� ������������ 0�03 (4 ������� ����������) 3 ����
            E_LAT = 1;		// ���������
            LCD_LAT_FLUSH;
            __delay_us(1);
            E_LAT = 0;		//
            LCD_LAT_FLUSH;
            __delay_ms(6);
	}
        temp=LCD_LAT&0b00001111;
        LCD_LAT = 0b00100000|temp;	// �������� ����� 4������ ���������.
        E_LAT = 1;			// ���������
        LCD_LAT_FLUSH;
        __delay_us(1);	//
        E_LAT = 0;
        LCD_LAT_FLUSH;
        __delay_ms(2);
		
	SendLCDc( 0b00101000 );	// ��������� �������
	SendLCDc( 0b00001100 );	// �������� �������
	SendLCDc( 0b00000001 );	// ������� ��������
	SendLCDc( 0b00000110 );	// Entry Mode
	SendLCDc( 0b10000000 );	// DDRAM addresss 0000
	SendLCDc( 0b00000010 );	// return home
	
}//

 // ������� �����������
void ClearLCD(void)
{
	SendLCDc( 0x01 );	// send 0x01
        __delay_us(2000);
}//

 // ����� 
void StringLCD(const unsigned char *str)
{
unsigned char simbol;
unsigned int ptr = 0;
	while (str[ptr] != 0)
	{
		simbol=str[ptr++];
		if(simbol>0xBF)
		{
			simbol=SHRIFT[(simbol-0xC0)];
		}
		SendLCDd(simbol);	// ���� �������� �������� ���� �� ��������� ���� (����� ������) 	
	}
}//

// ����� ������ � ��������� �������
// ��������� �������� ��� ����, ����  � ������� �������� �������� �� 20 ��������
// �������� ����������� � ������� ������, ������� ��� stroka 0-3
// stolbec - ������� 0-19
void CursorLCD(unsigned char stroka,unsigned char stolbec) // ��������� ������� 0�������/�������
{
// ������� ������������ ����� 2 ������ �� 40 ��������
// 0-1-������ 0-19
// 1-2-������ 0-19
// 2-1-������ 20-39
// 3-2-������ 20-39
//	stroka=stroka&0b00000011;
//	if(stroka>1)
	if(0b00000010&stroka)stolbec=stolbec+20;
	if(0b00000001 & stroka)stolbec=stolbec|= 0b11000000;
	else stolbec=stolbec|= 0b10000000;
	SendLCDc(stolbec);	
}//

void DisplayLCD(unsigned char state){
    if (state) SendLCDc( 0b00001100 );	// �������� �������
    else
    SendLCDc( 0b00001000 );	// �������� �������
}



// �������������� WINDOWS
const char SHRIFT[] = {

		0x41,	// 0xC0	� 
		0xA0,	// �
		0x42,	// �
		0xA1,	// �
		0xE0,	// �
		0x45,	// �
		0xA3,	// 0��6 �
		0xA4,	// �
		0xA5,	// �
		0xA6,	// �
		0x4B,	// �
		0xA7,	// �
		0x4D,	// �
		0x48,	// �
		0x4F,	// �
		0xA8,	// �
		0x50,	// �			
		0x43,	// �			
		0x54,	// �			
		0xA9,	// �			
		0xAA,	// �	
		0x58,	// �			
		0xE1,	// �
		0xAB,	// �			
		0xAC,	// �								
		0xE2,	// �			
		0xAD,	// �
		0xAE,	// �
		0x62,	// �			
		0xAF,	// �			
		0xB0,	// �			
		0xB1,	// �			

		0x61,	// �	
		0xB2,	// �
		0xB3,	// �
		0xB4,	// �
		0xE3,	// �
		0x65,	// �
		0xB6,	// �
		0xB7,	// �
		0xB8,	// �
		0xB9,	// �
		0xBA,	// �
		0xBB,	// �
		0xBC,	// �
		0xBD,	// �
		0x6F,	// o
		0xBE,	// �
		0x70,	// �
		0x63,	// �
		0xBF,	// �
		0x79,	// �
		0xE4,	// �
		0x78,	// �
		0xE5,	// �
		0xC0,	// �
		0xC1,	// �
		0xE6,	// �
		0xC2,	// �
		0xC3,	// �
		0xC4,	// �
		0xC5,	// �
		0xC6,	// �
		0xC7,	// �
};
