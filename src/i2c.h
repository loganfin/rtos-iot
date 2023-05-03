#pragma once

#include <stdint.h>

uint8_t read_8(uint8_t dev_addr, uint8_t reg);
uint16_t read_16(uint8_t dev_addr, uint8_t reg);
void write_8(uint8_t dev_addr, uint8_t reg, uint8_t data);
