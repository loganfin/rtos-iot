#pragma once

#include <Arduino.h>

extern const int stepper_clockwise;
extern QueueHandle_t xQStepper;

void stepper_init();
void vStepper(void* parameters);
