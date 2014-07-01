/* 
 * File:   globals.h
 * Author: lex
 *
 * Created on 8 червня 2014, 22:25
 */

#ifndef GLOBALS_H
#define	GLOBALS_H


#if defined(__XC)
#include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
#include <htc.h>        /* HiTech General Include File */
#endif

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */
#include <stdlib.h>
#include <stdio.h>

    
volatile const int16_t SENSOR_MIN_TIME;  //software press filter
volatile const int16_t BUTTON_PRESS_MIN_TIME;  //software press filter
volatile const int16_t BUTTON_LONGPRESS_MIN_TIME;  //software long press filter

typedef struct {
        unsigned state : 1;
        unsigned detecting : 1;
        unsigned press : 1;
        unsigned long_press : 1;
        int16_t timerstart;
        uint8_t debounce;
} sensor_t;

volatile unsigned long device_value[];

volatile sensor_t Sensor1;
volatile sensor_t Sensor2;
volatile sensor_t ButtonSelect;
volatile sensor_t ButtonMode;
volatile uint32_t seconds;

volatile unsigned char IOC;



#ifdef	__cplusplus
}
#endif

#endif	/* GLOBALS_H */

