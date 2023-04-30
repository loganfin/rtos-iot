#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

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
    // initalize pins

    // connect to wifi
    wifi_init();
    // start the tasks
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
