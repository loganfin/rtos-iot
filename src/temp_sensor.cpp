#include "temp_sensor.h"
#include "i2c.h"

#include <Arduino.h>
#include <stdint.h>
#include <Wire.h>

const byte hdc_address = 0x40;
const byte hdc_temp_reg = 0x00;
const byte hdc_humid_reg = 0x01;
const byte hdc_config_reg = 0x02;
const byte hdc_man_id_reg = 0xFE;

uint16_t read_config()
{
    return read_16(hdc_address, hdc_config_reg);
}

uint16_t read_man_id()
{
    return read_16(hdc_address, hdc_man_id_reg);
}

// return the current temperature in celsius
float temp_c()
{
    uint16_t raw_temp = read_16(hdc_address, hdc_temp_reg);
    return ((float)raw_temp / 65536) * 165 - 40;
}

// return the current temperature in fahrenheit
float temp_f()
{
    float celsius = temp_c();
    return (celsius * 9/5) + 32;
}

// return the current humidity in percent
float humidity()
{
    uint16_t raw_humidity = read_16(hdc_address, hdc_humid_reg);
    return ((float)raw_humidity / 65536) * 100;
}

void vTemperature(void* parameters)
{
    while (true) {
        if (xSemaphoreTake(xi2cSem, 0) == pdTRUE) {
            Serial.print("Temperature (C): ");
            Serial.println(temp_c());
            Serial.print("Temperature (F): ");
            Serial.println(temp_f());
            Serial.print("Humidity (%): ");
            Serial.println(humidity());
            Serial.println();

            xSemaphoreGive(xi2cSem);
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
        taskYIELD();
    }
}

