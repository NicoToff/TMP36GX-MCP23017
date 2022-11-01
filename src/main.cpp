#include <Arduino.h>
#include <Wire.h>
#include "temperature.h"
#include "MCP23017.h"

#define TMP36 35

MCP23017 mcp(HIGH, HIGH, HIGH); // Mentioning hardware address pins

void setup()
{
    Wire.begin();
    mcp.portMode(PORTA, ALL_OUTPUT);
    pinMode(TMP36, INPUT);
    Serial.begin(115200);
}

void loop()
{
    float temp = getTempC(TMP36);
    Serial.print("Temperature: ");
    Serial.println(temp, 6);
    byte mask = getTempMask(temp);
    mcp.portWrite(PORTA, mask);
    delay(3000);
}