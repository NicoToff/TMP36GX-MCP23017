#include <Arduino.h>
#include <Wire.h>
#define GPA0 1 << 0
#define GPA1 1 << 1
#define GPA2 1 << 2
#define GPA3 1 << 3
#define GPA4 1 << 4
#define GPA5 1 << 5
#define GPA6 1 << 6
#define GPA7 1 << 7
#define GPB0 1 << 0
#define GPB1 1 << 1
#define GPB2 1 << 2
#define GPB3 1 << 3
#define GPB4 1 << 4
#define GPB5 1 << 5
#define GPB6 1 << 6
#define GPB7 1 << 7

#define chipAddr 0x27
#define GPIOA 0x12  // PortA reg addr
#define GPIOB 0x13  // PortB reg addr
#define IODIRA 0x00 // PortA direction reg addr
#define IODIRB 0x01 // PortB direction reg addr

#define TMP36 35

byte i = 128;

float getTempC(byte pin, int offset = 0, float maxVoltage = 3.3, int resolution = 4096)
{
    uint16_t read = analogRead(TMP36) + offset;
    float voltage = read * (maxVoltage / resolution);
    float temperatureC = (voltage - 0.5) * 100.0;
    return temperatureC;
}

void setup()
{
    Serial.begin(115200);
    Wire.begin();

    Wire.beginTransmission(chipAddr);
    Wire.write(IODIRA); // IODIRA dir register
    Wire.write(0x00);   // set entire PORT A  as output
    Wire.endTransmission();

    Wire.beginTransmission(chipAddr);
    Wire.write(IODIRB); // IODIRB dir register
    Wire.write(0xff);   // set entire PORT B as input
    Wire.endTransmission();

    pinMode(TMP36, INPUT);
}

void loop()
{
    float temp = getTempC(TMP36, 110);
    Serial.print(" Temperature (C): ");
    Serial.println(temp);

    Wire.beginTransmission(chipAddr);
    Wire.write(GPIOA); // address PORT A
    byte mask = (temp >= 20.0 ? GPA7 : 0) | (temp >= 21.0 ? GPA6 : 0) | (temp >= 22.0 ? GPA5 : 0) | (temp >= 23.0 ? GPA4 : 0) | (temp >= 24.0 ? GPA3 : 0) | (temp >= 25.0 ? GPA2 : 0) | (temp >= 26.0 ? GPA1 : 0) | (temp >= 27.0 ? GPA0 : 0);
    Wire.write(mask); // PORT A
    Wire.endTransmission();

    delay(1000);
}