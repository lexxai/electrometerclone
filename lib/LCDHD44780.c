/*
 * работа с символьными руссифицированными индикаторами на драйвере HD44780 или ему совместимыми
 * проект Catcatcat electronics
 * автор Гена Чернов 2013-2014
 * версия - 1.0
 * версия - 1.1 исправленно название функции  String на StringLCD
 * версия - 1.2 добавлены фунции SendLCDd и SendLCDc - это позволяет экономит память, если неиспользовать функцию SendLCDdata
 * версия - 1.3 Microchip MPLAB XC8 C Compiler V1.12
 * версия - 2.0 Microchip MPLAB XC8 C Compiler V1.30 корректная работа со всеми тактовыми частотами
 * 2.1 LAT tune
 *///-------------------------------------------------------------------------

#include <xc.h>							// стандартный заголовок описания
#include "LCDHD44780.h"						// библиотека работы с индикатором на драйвере HD44780

//-------------------------------------------------------------------------

// знакогенератор - переподировщик
const char SHRIFT[];

void SendLCDc(unsigned char data) // Данные, команда/данные
{
unsigned char temp;

    temp=LCD_LAT&0b00001111;		//
    LCD_LAT = data|temp;			//
    RW_LAT = 0;				// режим записи в индикатор
    RS_LAT = 0;				// 0-команда/1-данные
    E_LAT = 1;				// Импуль записи
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
    // проверка на занятости индикатора
//    LCD_TRIS = 0xF0;			// настройка R0--R4 на ввод
//    RS_LAT = 0;				// чтение команд
//    RW_LAT = 1;				// режим чтения
//    data = 0xFF;                         // загрузить данные
//    while (data & 0b10000000)        // проверяем индикатор занят
//    {
//        E_LAT = 1;			        // читатать младший полубайт
//        LCD_LAT_FLUSH;
//        __delay_us(1);
//        E_LAT = 0;			        //
//        LCD_LAT_FLUSH;
//        data = LCD;                     //  загрузить данные
//        E_LAT = 1;			        // читатать старший полубайт
//        LCD_LAT_FLUSH;
//        __delay_us(1);
//        E_LAT = 0;
//        LCD_LAT_FLUSH;
//    }
    __delay_us(10);
//    LCD_TRIS = 0;			// настроить порт на вывод
}//

void SendLCDd(unsigned char data) // Данные, команда/данные
{
unsigned char temp;

    temp=LCD_LAT&0b00001111;		//
    LCD_LAT = data|temp;			//
    RW_LAT = 0;				// режим записи в индикатор
    RS_LAT = 1;				// 0-команда/1-данные
    E_LAT = 1;				// Импуль записи
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
    // проверка на занятости индикатора
//    LCD_TRIS = 0xF0;			// настройка R7-R4 на ввод
//    RS_LAT = 0;				// чтение команд
//    RW_LAT = 1;				// режим чтения
//    data = 0xFF;                         // загрузить данные
//    while (data & 0b10000000)        // проверяем индикатор занят
//    {
//        E_LAT = 1;			        // читатать младший полубайт
//        LCD_LAT_FLUSH;
//        __delay_us(1);
//        E_LAT = 0;			        //
//        LCD_LAT_FLUSH;
//        data = LCD;                     //  загрузить данные
//        E_LAT = 1;			        // читатать старший полубайт
//        LCD_LAT_FLUSH;
//        __delay_us(1);
//        E_LAT = 0;
//        LCD_LAT_FLUSH;
//    }
    __delay_us(10);
 //   LCD_TRIS = 0;			// настроить порт на вывод
}//

void SendLCDdata(unsigned char data, unsigned char rs) // Данные, команда/данные
{
unsigned char temp;

    temp=LCD_LAT&0b00001111;		//
    LCD_LAT = data|temp;			//
    RW_LAT = 0;				// режим записи в индикатор
    RS_LAT = rs;				// 0-команда/1-данные
    E_LAT = 1;				// Импуль записи
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
    // проверка на занятости индикатора
//    LCD_TRIS = 0xF0;			// настройка R0--R4 на ввод
//    RS_LAT = 0;				// чтение команд
//    RW_LAT = 1;				// режим чтения
//    data = 0xFF;                         // загрузить данные
//    while (data & 0b10000000)        // проверяем индикатор занят
//    {
//        E_LAT = 1;			        // читатать младший полубайт
//        LCD_LAT_FLUSH;
//        __delay_us(1);
//        E_LAT = 0;			        //
//        LCD_LAT_FLUSH;
//        data = LCD;                     //  загрузить данные
//        E_LAT = 1;			        // читатать старший полубайт
//        LCD_LAT_FLUSH;
//        __delay_us(1);
//        E_LAT = 0;
//        LCD_LAT_FLUSH;
//    }
    __delay_us(10);
//    LCD_TRIS = 0;			// настроить порт на вывод
}//

void InitLCD(void) // функция начальной инциализации дисплея
{
	char a,temp;
	__delay_ms(10);
	__delay_ms(10);
	__delay_ms(10);
	RW_LAT=0;//режим записи в дисплей
	RS_LAT=0;//режим команд
        LCD_LAT_FLUSH;
	for ( a = 0; a < 4; a++ )
	{
            temp=LCD_LAT&0b00001111;
            LCD_LAT = 0b00110000|temp;	// код инциализации 0х03 (4 битного интерфейса) 3 раза
            E_LAT = 1;		// загрузить
            LCD_LAT_FLUSH;
            __delay_us(1);
            E_LAT = 0;		//
            LCD_LAT_FLUSH;
            __delay_ms(6);
	}
        temp=LCD_LAT&0b00001111;
        LCD_LAT = 0b00100000|temp;	// включить режим 4битный интерфейс.
        E_LAT = 1;			// загрузить
        LCD_LAT_FLUSH;
        __delay_us(1);	//
        E_LAT = 0;
        LCD_LAT_FLUSH;
        __delay_ms(2);
		
	SendLCDc( 0b00101000 );	// Настройка функций
	SendLCDc( 0b00001100 );	// Включить дисплей
	SendLCDc( 0b00000001 );	// Дисплей очистить
	SendLCDc( 0b00000110 );	// Entry Mode
	SendLCDc( 0b10000000 );	// DDRAM addresss 0000
	SendLCDc( 0b00000010 );	// return home
	
}//

 // очистка ииндикатора
void ClearLCD(void)
{
	SendLCDc( 0x01 );	// send 0x01
        __delay_us(2000);
}//

 // вывод 
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
		SendLCDd(simbol);	// цикл передачи символов пока не достигнут ноль (конец строки) 	
	}
}//

// вывод текста в положение курсора
// корректно работает для одно, двух  и четырех строчных дисплеев до 20 символов
// значение вписывается в формате строка, столбец где stroka 0-3
// stolbec - столбец 0-19
void CursorLCD(unsigned char stroka,unsigned char stolbec) // положение курсора 0хстрока/столбец
{
// дисплей представляет собой 2 строки по 40 символов
// 0-1-строка 0-19
// 1-2-строка 0-19
// 2-1-строка 20-39
// 3-2-строка 20-39
//	stroka=stroka&0b00000011;
//	if(stroka>1)
	if(0b00000010&stroka)stolbec=stolbec+20;
	if(0b00000001 & stroka)stolbec=stolbec|= 0b11000000;
	else stolbec=stolbec|= 0b10000000;
	SendLCDc(stolbec);	
}//

void DisplayLCD(unsigned char state){
    if (state) SendLCDc( 0b00001100 );	// Включить дисплей
    else
    SendLCDc( 0b00001000 );	// Вилючить дисплей
}



// знакогенератор WINDOWS
const char SHRIFT[] = {

		0x41,	// 0xC0	А 
		0xA0,	// Б
		0x42,	// В
		0xA1,	// Г
		0xE0,	// Д
		0x45,	// Е
		0xA3,	// 0хС6 Ж
		0xA4,	// З
		0xA5,	// И
		0xA6,	// Й
		0x4B,	// К
		0xA7,	// Л
		0x4D,	// М
		0x48,	// Н
		0x4F,	// О
		0xA8,	// П
		0x50,	// Р			
		0x43,	// С			
		0x54,	// Т			
		0xA9,	// У			
		0xAA,	// ф	
		0x58,	// Х			
		0xE1,	// Ц
		0xAB,	// Ч			
		0xAC,	// Ш								
		0xE2,	// Щ			
		0xAD,	// Ъ
		0xAE,	// Ы
		0x62,	// Ь			
		0xAF,	// Э			
		0xB0,	// Ю			
		0xB1,	// Я			

		0x61,	// а	
		0xB2,	// б
		0xB3,	// в
		0xB4,	// г
		0xE3,	// д
		0x65,	// е
		0xB6,	// ж
		0xB7,	// з
		0xB8,	// и
		0xB9,	// й
		0xBA,	// к
		0xBB,	// л
		0xBC,	// м
		0xBD,	// н
		0x6F,	// o
		0xBE,	// п
		0x70,	// р
		0x63,	// с
		0xBF,	// т
		0x79,	// у
		0xE4,	// Ф
		0x78,	// х
		0xE5,	// ц
		0xC0,	// ч
		0xC1,	// ш
		0xE6,	// щ
		0xC2,	// ъ
		0xC3,	// ы
		0xC4,	// ь
		0xC5,	// э
		0xC6,	// ю
		0xC7,	// я
};
