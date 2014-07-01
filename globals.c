#include <stdint.h>        /* For uint8_t definition */

volatile unsigned long device_value[] = {9999900, 9999000};

//typedef struct {
//        unsigned state : 1;
//        unsigned detecting : 1;
//        unsigned press : 1;
//        unsigned long_press : 1;
//        int16_t timerstart;
//} sensor_t;

//volatile sensor_t Sensor1;
//volatile sensor_t Sensor2;
//volatile sensor_t ButtonSelect;
//volatile sensor_t ButtonMode;

volatile uint32_t seconds=0;

volatile const int16_t SENSOR_MIN_TIME = 2048;  //software press filter 0.5sec
volatile const int16_t BUTTON_PRESS_MIN_TIME = 205;  //software press filter 0.05sec
volatile const int16_t BUTTON_LONGPRESS_MIN_TIME = 4096;  //software long press filter 1 ses



