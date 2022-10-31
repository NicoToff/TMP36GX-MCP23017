#include <Arduino.h>
#include <Wire.h>

enum MCP23017ConfPort
{
    IODIRA, // I/O configuration bits for port A
    IODIRB  // I/O configuration bits for port A
};

enum MCP23017RegisterAddr
{
    GPIOA = 0x12, // PortA reg addr
    GPIOB = 0x13  // PortB reg addr
};

#define PORTA IODIRA // I/O configuration bits for port A
#define GPA0 1 << 0 // PortA bit 0
#define GPA1 1 << 1 // PortA bit 1
#define GPA2 1 << 2 // PortA bit 2
#define GPA3 1 << 3 // PortA bit 3
#define GPA4 1 << 4 // PortA bit 4
#define GPA5 1 << 5 // PortA bit 5
#define GPA6 1 << 6 // PortA bit 6
#define GPA7 1 << 7 // PortA bit 7

#define PORTB IODIRB // I/O configuration bits for port B
#define GPB0 1 << 0 // PortB bit 0
#define GPB1 1 << 1 // PortB bit 1
#define GPB2 1 << 2 // PortB bit 2
#define GPB3 1 << 3 // PortB bit 3
#define GPB4 1 << 4 // PortB bit 4
#define GPB5 1 << 5 // PortB bit 5
#define GPB6 1 << 6 // PortB bit 6
#define GPB7 1 << 7 // PortB bit 7

#define ALL_OUTPUT 0x00 // Byte value for all output (to be used with `portMode()`)
#define ALL_INPUT 0xFF // Byte value for all input (to be used with `portMode()`)

#define I2C_CONNECTION_OK 0

class MCP23017
{
private:
    byte address;

public:
    MCP23017(byte address)
    {
        this->address = address;
    };

    MCP23017(byte a0, byte a1, byte a2)
    {
        this->address = 0x20 | (a0 << 0) | (a1 << 1) | (a2 << 2);
    };

    void portMode(MCP23017ConfPort port, byte mode)
    {
        do
        {
            Wire.beginTransmission(address);
            Wire.write(port);
            Wire.write(mode);
        } while (Wire.endTransmission() != I2C_CONNECTION_OK);
    };
    void portWrite(MCP23017ConfPort port, byte value)
    {
        byte registerAddr;
        switch (port)
        {
        case PORTA:
            registerAddr = GPIOA;
            break;
        case PORTB:
            registerAddr = GPIOB;
            break;
        }
        do
        {
            Wire.beginTransmission(address);
            Wire.write(registerAddr);
            Wire.write(value);
        } while (Wire.endTransmission() != I2C_CONNECTION_OK);
    };
    void portWrite(MCP23017RegisterAddr registerAddr, byte value)
    {
        do
        {
            Wire.beginTransmission(address);
            Wire.write(registerAddr);
            Wire.write(value);
        } while (Wire.endTransmission() != I2C_CONNECTION_OK);
    };
    uint8_t digitalRead(uint8_t pin);
};