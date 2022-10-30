#include <Arduino.h>
#include <Wire.h>

enum MCP23017Port
{
    IODIRA,
    IODIRB
};

#define PORTA IODIRA
#define GPIOA 0x12 // PortA reg addr
#define GPA0 1 << 0
#define GPA1 1 << 1
#define GPA2 1 << 2
#define GPA3 1 << 3
#define GPA4 1 << 4
#define GPA5 1 << 5
#define GPA6 1 << 6
#define GPA7 1 << 7

#define PORTB IODIRB
#define GPIOB 0x13 // PortB reg addr
#define GPB0 1 << 0
#define GPB1 1 << 1
#define GPB2 1 << 2
#define GPB3 1 << 3
#define GPB4 1 << 4
#define GPB5 1 << 5
#define GPB6 1 << 6
#define GPB7 1 << 7

#define ALL_OUTPUT 0x00
#define ALL_INPUT 0xFF

#define I2C_CONNECTION_OK 0

class MCP23017
{
private:
    byte address;

public:
    MCP23017(uint8_t address)
    {
        this->address = address;
    };
    MCP23017(uint8_t a0, uint8_t a1, uint8_t a2)
    {
        this->address = 0x20 | (a0 << 0) | (a1 << 1) | (a2 << 2);
    };

    void portMode(MCP23017Port port, uint8_t mode)
    {
        do
        {
            Wire.beginTransmission(address);
            Wire.write(port);
            Wire.write(mode);
        } while (Wire.endTransmission() != I2C_CONNECTION_OK);
    };
    void portWrite(MCP23017Port port, uint8_t value)
    {
        byte destPort;
        switch (port)
        {
        case PORTA:
            destPort = GPIOA;
            break;
        case PORTB:
            destPort = GPIOB;
            break;
        }
        do
        {
            Wire.beginTransmission(address);
            Wire.write(destPort);
            Wire.write(value);
        } while (Wire.endTransmission() != I2C_CONNECTION_OK);
    };
    uint8_t digitalRead(uint8_t pin);
};