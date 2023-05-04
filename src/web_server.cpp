#include "web_server.h"
#include "light_sensor.h"

#include <string>
#include <WiFi.h>

void vWebServer(void* parameters)
{
    WiFiServer web_server(80);
    WiFiClient client;
    String header;
    String current_line = "";
    char client_data;

    const uint64_t timeout_ms = 2000;
    uint64_t current_time = millis();
    uint64_t previous_time = 0;

    uint16_t vis_light;
    char buffer[256];

    web_server.begin();

    while (true) {
        client = web_server.available();

        if (client) {
            current_time = millis();
            previous_time = current_time;
            Serial.println("New client.");

            while (client.connected() && current_time - previous_time <= timeout_ms) {
                current_time = millis();

                if (client.available()) {
                    client_data = client.read();
                    Serial.write(client_data);
                    header += client_data;

                    if (client_data == '\n') {
                        if (current_line.length() == 0) {
                            // http header
                            client.println("HTTP/1.1 200 OK");
                            client.println("Content-type:text/html");
                            client.println("Connection: close");
                            client.println();
                            // http page content
                            client.print(
                                "<!DOCTYPE html>"
                                "<html lang='en'>"
                                    "<head>"
                                        "<link rel='stylesheet' href='https://cdn.jsdelivr.net/npm/bootstrap@5.3.0-alpha1/dist/css/bootstrap.min.css' integrity='sha384-GLhlTQ8iRABdZLl6O3oVMWSktQOp6b7In1Zl3/Jr59b6EGGoI1aFkw7cmDA6j6gD' crossorigin='anonymous'>"
                                    "</head>"
                                    "<body>"
                                        "<div class='container mt-3 text-center'>"
                                            "<h1>Logan Finley</h1>"
                                            "<table class='table'>"
                                                "<thead>"
                                                    "<tr>"
                                                        "<td scope='col'>Light Sensor</td>"
                                                        "<td scope='col'>Stepper Motor</td>"
                                                        "<td scope='col'>Action</td>"
                                                    "</tr>"
                                                "</thead>"
                                                "<tbody>"
                                                    "<tr>"
                                                        "<td>"
                                    );
                            xQueuePeek(xQVisibleLight, &vis_light, 0);
                            client.print(
                                                            std::to_string(vis_light).c_str()
                                    );
                            client.println(
                                                        "</td>"
                                                        "<td>Clockwise</td>"
                                                        "<td>"
                                                            "<form action='submit'>"
                                                                "<button class='btn btn-outline-primary'>"
                                                                    "Change Direction"
                                                                "</button>"
                                                            "</form>"
                                                        "</td>"
                                                    "</tr>"
                                                "</tbody>"
                                            "</table>"
                                        "</div>"
                                    "</body>"
                                "</html>"
                                    );
                            client.println();
                            break;
                        }
                        else {
                            current_line = "";
                        }
                    } else if (client_data != '\r') {
                        current_line += client_data;
                    }
                }
            }
            header = "";

            client.stop();
            Serial.println("Client disconnected.");
            Serial.println("");
        }
        client.stop();
    }
}
