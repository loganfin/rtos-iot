#include "i2c.h"

#include <Arduino.h>
#include <stdint.h>
#include <Wire.h>

SemaphoreHandle_t xi2cSem;

// read the data from an 8 bit register
uint8_t read_8(uint8_t dev_addr, uint8_t reg)
{
    Wire.beginTransmission(dev_addr);
    Wire.write(reg);
    Wire.endTransmission();
    vTaskDelay(100 / portTICK_PERIOD_MS);
    Wire.requestFrom(dev_addr, 1);
    return Wire.read();
}

// read the data from a 16 bit register
uint16_t read_16(uint8_t dev_addr, uint8_t reg)
{
    byte buffer[2];

    Wire.beginTransmission(dev_addr);
    Wire.write(reg);
    Wire.endTransmission();
    vTaskDelay(100 / portTICK_PERIOD_MS);
    Wire.requestFrom(dev_addr, 2);
    Wire.readBytes(buffer, 2);
    return ((uint16_t)buffer[1]) | ((uint16_t)buffer[0] << 8);
}

// write 8 bits of data
void write_8(uint8_t dev_addr, uint8_t reg, uint8_t data)
{
    Wire.beginTransmission(dev_addr);
    Wire.write(reg);
    Wire.write(data);
    Wire.endTransmission();
    return;
}
