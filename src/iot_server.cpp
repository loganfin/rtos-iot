#include "iot_server.h"
#include "auth.h"

#include <Arduino.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <stdint.h>
#include <WiFi.h>

void vIotServer(void* parameters)
{
    TickType_t last_time = 0;
    TickType_t delay = 1000 / portTICK_PERIOD_MS;

    WiFiClient client;
    HTTPClient http;
    DynamicJsonDocument json_buffer(2048);
    String http_request_data;

    json_buffer["auth_code"] = AUTH_CODE;
    serializeJson(json_buffer, http_request_data);

    while (true) {
            if((xTaskGetTickCount() - last_time) > delay) {
                http.useHTTP10(true);
                http.begin(client, SERVER_ADDR);
                http.addHeader("Content-Type", "application/json");

                int http_response_code = http.POST(http_request_data);

                deserializeJson(json_buffer, http.getStream());
                Serial.print("Server address: ");
                Serial.println(SERVER_ADDR);
                Serial.print("Request json: ");
                Serial.println(http_request_data);
                Serial.print("Response json: ");
                Serial.println(json_buffer.as<String>());

                last_time = xTaskGetTickCount();
            }
    }
}
