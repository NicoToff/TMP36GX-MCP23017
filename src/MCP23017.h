#ifndef MCP23017_H
#define MCP23017_H

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
#define GPA0 1 << 0  // PortA bit 0
#define GPA1 1 << 1  // PortA bit 1
#define GPA2 1 << 2  // PortA bit 2
#define GPA3 1 << 3  // PortA bit 3
#define GPA4 1 << 4  // PortA bit 4
#define GPA5 1 << 5  // PortA bit 5
#define GPA6 1 << 6  // PortA bit 6
#define GPA7 1 << 7  // PortA bit 7

#define PORTB IODIRB // I/O configuration bits for port B
#define GPB0 1 << 0  // PortB bit 0
#define GPB1 1 << 1  // PortB bit 1
#define GPB2 1 << 2  // PortB bit 2
#define GPB3 1 << 3  // PortB bit 3
#define GPB4 1 << 4  // PortB bit 4
#define GPB5 1 << 5  // PortB bit 5
#define GPB6 1 << 6  // PortB bit 6
#define GPB7 1 << 7  // PortB bit 7

#define ALL_OUTPUT 0x00 // Byte value for all pins as output (to be used with `portMode()`)
#define ALL_INPUT 0xFF  // Byte value for all pins as input (to be used with `portMode()`)
#define ALL_HIGH 0xFF   // Byte value for all pins as HIGH (to be used with `portWrite()`)
#define ALL_LOW 0x00    // Byte value for all pins as LOW (to be used with `portWrite()`)

#define I2C_CONNECTION_OK 0

class MCP23017
{
public:
    /**
     * @brief Construct a new MCP23017 object
     *
     * @param i2c_address The actual I2C address of the MCP23017 chip
     */
    MCP23017(byte i2c_address)
    {
        this->i2c_address = i2c_address;
    };

    /**
     * @brief Construct a new MCP23017 object
     *
     * @param a0 State of the A0 pin of the MCP23017 chip (HIGH or LOW)
     * @param a1 State of the A1 pin of the MCP23017 chip (HIGH or LOW)
     * @param a2 State of the A2 pin of the MCP23017 chip (HIGH or LOW)
     */
    MCP23017(byte a0, byte a1, byte a2)
    {
        this->i2c_address = 0x20 | (a0 << 0) | (a1 << 1) | (a2 << 2);
    };

    /**
     * @brief Set the port mode (input or output)
     *
     * @param port Port to configure (PORTA or PORTB)
     * @param mode A byte to set individual pins as input or output (0 = output, 1 = input)
                   Can also use the predefined macros ALL_OUTPUT or ALL_INPUT
     */
    void portMode(MCP23017ConfPort port, byte mode)
    {
        do
        {
            Wire.beginTransmission(i2c_address);
            Wire.write(port);
            Wire.write(mode);
        } while (Wire.endTransmission() != I2C_CONNECTION_OK);
    };

    /**
     * @brief Writes a byte value to the specified port.
     *
     * @param port Either PORTA/GPIOA or PORTB/GPIOB
     * @param value A byte value to write to the port (can also use predefined macros ALL_HIGH or ALL_LOW)
     */
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
        write(registerAddr, value);
    };
    void portWrite(MCP23017RegisterAddr registerAddr, byte value)
    {
        write(registerAddr, value);
    };
    byte getI2CAddress()
    {
        return i2c_address;
    };

private:
    byte i2c_address;
    void write(byte registerAddr, byte value)
    {
        do
        {
            Wire.beginTransmission(i2c_address);
            Wire.write(registerAddr);
            Wire.write(value);
        } while (Wire.endTransmission() != I2C_CONNECTION_OK);
    };
};
#endif