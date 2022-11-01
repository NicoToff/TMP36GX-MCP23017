#ifndef temperature_h
#define temperature_h

#include <Arduino.h>
#include "MCP23017.h"

#define TMP36 35
#define FACTORY_TMP36_OFFSET -0.5

#define WHITE_LED GPA7
#define BLUE_LED1 GPA6
#define BLUE_LED2 GPA5
#define GREEN_LED1 GPA4
#define GREEN_LED2 GPA3
#define YELLOW_LED1 GPA2
#define YELLOW_LED2 GPA1
#define RED_LED GPA0

float getTempC(byte pin, int mVoltOffset = 0, double maxVoltage = 3.3, int resolution = 4096)
{    
    uint16_t read = analogRead(TMP36);
    float voltage = (float)read * (maxVoltage / resolution);
    float offsetVoltage = voltage + (mVoltOffset / 1000.0) + FACTORY_TMP36_OFFSET;
    float temperatureC = offsetVoltage * 100.0;
    return temperatureC;
}

byte getTempMask(float temp)
{
    return (
        WHITE_LED                          // Always on
        | (temp >= 18.0 ? BLUE_LED1 : 0)   //
        | (temp >= 19.0 ? BLUE_LED2 : 0)   //
        | (temp >= 20.0 ? GREEN_LED1 : 0)  //
        | (temp >= 21.0 ? GREEN_LED2 : 0)  //
        | (temp >= 22.0 ? YELLOW_LED1 : 0) //
        | (temp >= 24.0 ? YELLOW_LED2 : 0) //
        | (temp >= 27.0 ? RED_LED : 0)     //
    );
}
#endif