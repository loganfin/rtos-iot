#pragma once

#include <Arduino.h>
#include <stdint.h>

extern QueueHandle_t xQTemperature;
extern QueueHandle_t xQHumidity;

uint16_t read_config();
uint16_t read_man_id();
float temp_c();
float temp_f();
float humidity();
void vTemperature(void* parameters);
