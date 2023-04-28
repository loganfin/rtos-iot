#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

/*
 * Defines WIFI_SSID, WIFI_PASS, SERVER_ADDR and AUTH_CODE.
 * You will have to create this file yourself.
 */
#include "auth.h"

void setup()
{
    // initialize serial
    Serial.begin(115200);
    // initalize pins

    // connect to wifi
    Serial.print("Connecting to ");
    Serial.println(WIFI_SSID);
    WiFi.begin(WIFI_SSID, WIFI_PASS);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.print("Connected to WiFi network with IP Address: ");
    Serial.println(WiFi.localIP());
    // start the tasks
}

void loop() {}
