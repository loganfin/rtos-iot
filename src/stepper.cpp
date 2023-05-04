#include "stepper.h"

#include <Arduino.h>
#include <stdint.h>

const int stepper_coil_1_pin = 26;
const int stepper_coil_2_pin = 8;
const int stepper_coil_3_pin = 7;
const int stepper_coil_4_pin = 12;
const int stepper_clockwise = 1;

void stepper_init()
{
    pinMode(stepper_coil_1_pin, OUTPUT);
    pinMode(stepper_coil_2_pin, OUTPUT);
    pinMode(stepper_coil_3_pin, OUTPUT);
    pinMode(stepper_coil_4_pin, OUTPUT);
}

void stepper_step(uint steps, uint direction)
{
    TickType_t delay = 1;

    if (direction == stepper_clockwise) {
        for (int i = 0; i < steps; i++) {
            digitalWrite(stepper_coil_4_pin, 1);
            vTaskDelay(delay);
            digitalWrite(stepper_coil_1_pin, 0);
            vTaskDelay(delay);
            digitalWrite(stepper_coil_3_pin, 1);
            vTaskDelay(delay);
            digitalWrite(stepper_coil_4_pin, 0);
            vTaskDelay(delay);
            digitalWrite(stepper_coil_2_pin, 1);
            vTaskDelay(delay);
            digitalWrite(stepper_coil_3_pin, 0);
            vTaskDelay(delay);
            digitalWrite(stepper_coil_1_pin, 1);
            vTaskDelay(delay);
            digitalWrite(stepper_coil_2_pin, 0);
            vTaskDelay(delay);
        }
        return;
    }

    for (int i = 0; i < steps; i++) {
        digitalWrite(stepper_coil_1_pin, 1);
        vTaskDelay(delay);
        digitalWrite(stepper_coil_4_pin, 0);
        vTaskDelay(delay);
        digitalWrite(stepper_coil_2_pin, 1);
        vTaskDelay(delay);
        digitalWrite(stepper_coil_1_pin, 0);
        vTaskDelay(delay);
        digitalWrite(stepper_coil_3_pin, 1);
        vTaskDelay(delay);
        digitalWrite(stepper_coil_2_pin, 0);
        vTaskDelay(delay);
        digitalWrite(stepper_coil_4_pin, 1);
        vTaskDelay(delay);
        digitalWrite(stepper_coil_3_pin, 0);
        vTaskDelay(delay);
    }
}

void vStepper(void* parameters)
{
    while (true) {
        stepper_step(1, stepper_clockwise);
    }
}
