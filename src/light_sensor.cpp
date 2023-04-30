#include "light_sensor.h"

#include <Arduino.h>
#include <stdint.h>
#include <Wire.h>

const byte si1145_param_chlist = 0x01;
const byte si1145_param_chlist_enable_visible = 0x10;
const byte si1145_addr = 0x60;
const byte si1145_visible_reg = 0x22;
const byte si1145_part_id_reg = 0x00;
const byte si1145_meas_rate_reg = 0x08;
const byte si1145_command_reg = 0x18;
const byte si1145_meas_auto = 0x0f;
const byte si1145_reg_paramwr = 0x17;
const byte si1145_param_set = 0xa0;
const byte si1145_reg_paramrd = 0x2e;


uint16_t read_visible()
{
    return read_16(si1145_addr, si1145_visible_reg);
}

uint8_t read_part_id()
{
    return read_8(si1145_addr, si1145_part_id_reg);
}

void light_init()
{
    // set automatic measurement rate
    write_8(si1145_addr, si1145_meas_rate_reg, 0xFF);
    // set automatic measurement
    write_8(si1145_addr, si1145_command_reg, si1145_meas_auto);

    // enable visible light sensor
    write_param(si1145_param_chlist, si1145_param_chlist_enable_visible);
}

void vLightSensor(void* parameters)
{
    while (true) {
        Serial.print("Current light level: ");
        Serial.println(read_visible());
        Serial.print("Part id: ");
        Serial.println(read_part_id());
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}

uint8_t read_8(uint8_t dev_addr, uint8_t reg)
{
    Wire.beginTransmission(dev_addr);
    Wire.write(reg);
    Wire.endTransmission();
    vTaskDelay(100 / portTICK_PERIOD_MS);
    Wire.requestFrom(dev_addr, 1);
    return Wire.read();
}

uint16_t read_16(uint8_t dev_addr, uint8_t reg)
{
    byte buffer[2];

    Wire.beginTransmission(dev_addr);
    Wire.write(reg);
    Wire.endTransmission();
    vTaskDelay(100 / portTICK_PERIOD_MS);
    Wire.requestFrom(dev_addr, 2);
    Wire.readBytes(buffer, 2);
    return ((uint16_t)buffer[0]) | ((uint16_t)buffer[1] << 8);
    //return Wire.read();
}

void write_8(uint8_t dev_addr, uint8_t reg, uint8_t data)
{
    Wire.beginTransmission(dev_addr);
    Wire.write(reg);
    Wire.write(data);
    Wire.endTransmission();
    return;
}

uint8_t write_param(uint8_t p, uint8_t v)
{
    write_8(si1145_addr, si1145_reg_paramwr, v);
    write_8(si1145_addr, si1145_command_reg, p | si1145_param_set);
    return read_8(si1145_addr, si1145_reg_paramrd);
}
