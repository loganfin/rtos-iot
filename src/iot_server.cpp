#include "iot_server.h"
#include "auth.h"
#include "light_sensor.h"
#include "temp_sensor.h"

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

    uint16_t vis_light = 0;
    float temperature = 0.0;
    float humidity = 0.0;
    float latitude = 0.0;
    float longitude = 0.0;
    float altitude = 0.0;

    while (true) {
        if((xTaskGetTickCount() - last_time) > delay) {
            http.useHTTP10(true);
            http.begin(client, SERVER_ADDR);
            http.addHeader("Content-Type", "application/json");

            xQueueReceive(xQVisibleLight, &vis_light, 0);
            xQueueReceive(xQTemperature, &temperature, 0);
            xQueueReceive(xQHumidity, &humidity, 0);

            json_buffer["auth_code"] = AUTH_CODE;
            json_buffer["temperature"] = temperature;
            json_buffer["humidity"] = humidity;
            json_buffer["light"] = vis_light;
            json_buffer["latitude"] = latitude;
            json_buffer["longitude"] = longitude;
            json_buffer["altitude"] = altitude;
            json_buffer["time"] = "2023-05-04 00:00:01";
            serializeJson(json_buffer, http_request_data);

            int http_response_code = http.POST(http_request_data);

            deserializeJson(json_buffer, http.getStream());
            Serial.print("Server address: ");
            Serial.println(SERVER_ADDR);
            Serial.print("Request json: ");
            Serial.println(http_request_data);
            Serial.print("Response json: ");
            Serial.println(json_buffer.as<String>());

            last_time = xTaskGetTickCount();

            http_request_data = "";
        }
    }
}
