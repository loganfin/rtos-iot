#include "i2c.h"
#include "iot_server.h"
#include "light_sensor.h"
#include "temp_sensor.h"
#include "web_server.h"

#include <Arduino.h>
#include <WiFi.h>
#include <Wire.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <stdint.h>

/*
 * Defines WIFI_SSID, WIFI_PASS, SERVER_ADDR and AUTH_CODE.
 * You will have to create this file yourself.
 */
#include "auth.h"

void wifi_init();

void setup()
{
    // initialize serial
    Serial.begin(115200);

    // create the semaphores
    xi2cSem = xSemaphoreCreateBinary();

    // create the queues
    xQVisibleLight = xQueueCreate(1, sizeof(uint16_t));

    //start i2c
    Wire.begin();
    Wire.setClock(100 * 1000);

    // initalize pins
    light_init();

    // connect to wifi
    wifi_init();

    // start the tasks
    xTaskCreate(vWebServer, "Web Server", 4096, nullptr, 1, nullptr);
    xTaskCreate(vIotServer, "IoT Server", 4096, nullptr, 1, nullptr);
    xTaskCreate(vLightSensor, "Light Sensor", 2048, nullptr, 1, nullptr);
    xTaskCreate(vTemperature, "Temperature Sensor", 2048, nullptr, 1, nullptr);

    xSemaphoreGive(xi2cSem);
}

void wifi_init()
{
    Serial.print("Connecting to ");
    Serial.println(WIFI_SSID);
    WiFi.begin(WIFI_SSID, WIFI_PASS);

    while (WiFi.status() != WL_CONNECTED) {
        vTaskDelay(500 / portTICK_PERIOD_MS);
        Serial.print(".");
    }

    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(WIFI_SSID);
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
}

void loop() {}
