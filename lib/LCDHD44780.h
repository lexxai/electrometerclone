/*
 * работа с символьными руссифицированными индикаторами на драйвере HD44780 или ему совместимыми
 * проект Catcatcat electronics
 * автор Гена Чернов 2013-2014
 * версия - 1.0
 * версия - 1.1 исправленно название функции  String на StringLCD
 * версия - 1.2 добавлены фунции SendLCDd и SendLCDc - это позволяет экономит память, если неиспользовать функцию SendLCDdata
 * версия - 1.3 Microchip MPLAB XC8 C Compiler V1.12
 * версия - 2.0 Microchip MPLAB XC8 C Compiler V1.30 корректная работа со всеми тактовыми частотами
 */
//------------------------------------------------------------------------- 
 
#pragma jis					// допускает конфигурирование не латинских символов в обработчике строк
#include "../system.h"

#include "../unionLATC.h"

//-------------------------------------------------------------------------
/*
библиотека подразумевает, что для обмена информацией используется один порт контроллера
используется 4 битный интерфейс, для передачи используется 4 страших бита порта


#define	LCD	PORTB			// определение порта
#define	LCD_TRIS TRISB			//
#define	E	RB3			// определение E
#define	RW	RB2			// определение RW
#define	RS	RB1			// определение RS
#define	LCD_LED	RC6			// определение порта управления подсветкой
*/
//#define	LCD	PORTC			// определение порта
//#define	LCD_LAT	LATPORTC.byte		// определение порта LAT
//
//#define	LCD_TRIS TRISC			//
//#define	E	PORTCbits.RC3			// определение E
//#define	RW	PORTCbits.RC2			// определение RW
//#define	RS	PORTCbits.RC1			// определение RS
//#define	LCD_LED	PORTCbits.RC0			// определение порта управления подсветкой
//
//#define	E_LAT	LATPORTC.bits.RC3			// определение E
//#define	RW_LAT	LATPORTC.bits.RC2			// определение RW
//#define	RS_LAT	LATPORTC.bits.RC1			// определение RS
//#define	LCD_LED_LAT	LATPORTC.bits.RC0			// определение порта управления подсветкой
//#define LCD_LAT_FLUSH LATPORTC_FLUSH


#define	LCD	PORTC			// определение порта
#define	LCD_LAT	LATPORTC.byte		// определение порта LAT

#define	LCD_TRIS TRISC			//
#define	E	PORTCbits.RC3			// определение E
#define	RW	PORTCbits.RC2			// определение RW
#define	RS	PORTCbits.RC1			// определение RS
#define	LCD_LED	PORTCbits.RC0			// определение порта управления подсветкой

#define	E_LAT	LATPORTC.bits.RC3			// определение E
#define	RW_LAT	LATPORTC.bits.RC2			// определение RW
#define	RS_LAT	LATPORTC.bits.RC1			// определение RS
#define	LCD_LED_LAT	LATPORTC.bits.RC0			// определение порта управления подсветкой
#define LCD_LAT_FLUSH LATPORTC_FLUSH


//-------------------------------------------------------------------------

void InitLCD(void); // функция начальной инициализации дисплея
void ClearLCD(void); // очистка ииндикатора
void DisplayLCD(unsigned char state); // 
void StringLCD(const unsigned char *str); // вывод текста в положение курсора 
void CursorLCD(unsigned char stroka,unsigned char stolbec); // положение курсора строка 0-3/столбец 0-40
void SendLCDdata(unsigned char data, unsigned char rs); // Данные, 0-команда/1-данные
void SendLCDd(unsigned char data); // Данные
void SendLCDc(unsigned char data); // Команда

//-------------------------------------------------------------------------
