#pragma once

#include <stdint.h>

uint16_t read_config();
uint16_t read_man_id();
float temp_c();
float temp_f();
float humidity();
void vTemperature(void* parameters);
