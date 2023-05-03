#pragma once

#include <stdint.h>

uint16_t read_visible();
void light_init();
uint8_t write_param(uint8_t p, uint8_t v);
void vLightSensor(void* parameters);
