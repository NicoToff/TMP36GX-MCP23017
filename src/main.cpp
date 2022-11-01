#include <Arduino.h>
#include <Wire.h>
#include "temperature.h"
#include "MCP23017.h"

#define TMP36 35
#define MAX_VOLT 3.3
#define RESOLUTION 4096.0
#define RATIO (MAX_VOLT / RESOLUTION)
MCP23017 mcp(HIGH, HIGH, HIGH); // Mentioning hardware address pins

void setup()
{
    Wire.begin();
    mcp.portMode(PORTA, ALL_OUTPUT);
    pinMode(TMP36, INPUT);
    Serial.begin(115200);
    delay(3000); // A bit of time to initialize the the sensor
}

void loop()
{
    uint16_t analog = analogRead(TMP36);
    Serial.print("Analog: ");
    Serial.println(analog);
    double voltage = analog * RATIO;
    Serial.print("Voltage (V) : ");
    Serial.println(voltage, 4);
    float temp = getTempC(TMP36, 100); // My ESP32 reads 0.1V lower than the TMP36 output
    Serial.print("Temperature: ");
    Serial.println(temp);
    byte mask = getTempMask(temp);
    mcp.portWrite(PORTA, mask);
    Serial.println("==================================");
    delay(3000);
}