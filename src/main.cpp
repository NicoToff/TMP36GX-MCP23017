#include <Arduino.h>
#include <Wire.h>
#include "MCP23017.h"

#define I2C_ADDRESS 0x27
#define I2C_CONNECTION_OK 0

#define TMP36 35

float getTempC(byte pin, int offset = 0, float maxVoltage = 3.3, int resolution = 4096)
{
    uint16_t read = analogRead(TMP36) + offset;
    float voltage = read * (maxVoltage / resolution);
    float temperatureC = (voltage - 0.5) * 100.0;
    return temperatureC;
}

MCP23017 mcp(HIGH, HIGH, HIGH);

void setup()
{
    Serial.begin(115200);
    Wire.begin();

    mcp.portMode(PORTA, ALL_OUTPUT);

    pinMode(TMP36, INPUT);
}

void loop()
{
    float temp = getTempC(TMP36, 110);
    Serial.print(" Temperature (C): ");
    Serial.println(temp);

    byte mask = (temp >= 20.0 ? GPA7 : 0) | (temp >= 21.0 ? GPA6 : 0) | (temp >= 22.0 ? GPA5 : 0) | (temp >= 23.0 ? GPA4 : 0) | (temp >= 24.0 ? GPA3 : 0) | (temp >= 25.0 ? GPA2 : 0) | (temp >= 26.0 ? GPA1 : 0) | (temp >= 27.0 ? GPA0 : 0);

    mcp.portWrite(PORTA, mask);

    delay(3000);
}