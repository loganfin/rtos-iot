#pragma once

#include <stdint.h>

uint16_t read_visible();
uint8_t read_8(uint8_t dev_addr, uint8_t reg);
uint16_t read_16(uint8_t dev_addr, uint8_t reg);
void write_8(uint8_t dev_addr, uint8_t reg, uint8_t data);
void light_init();
uint8_t write_param(uint8_t p, uint8_t v);
void vLightSensor(void* parameters);
