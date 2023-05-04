#pragma once

#include <Arduino.h>
#include <stdint.h>

extern QueueHandle_t xQVisibleLight;

void light_init();
uint8_t read_part_id();
uint16_t read_visible();
uint8_t write_param(uint8_t p, uint8_t v);
void vLightSensor(void* parameters);
