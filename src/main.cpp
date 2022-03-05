#include <Arduino.h>

#include <DNSServer.h>
#ifdef ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif

#include "LittleFS.h"
#include "ESPAsyncWebServer.h"

#include "config.h"

AsyncWebServer server(80);


void setup()
{
  Serial.begin(115200);

  if (!LittleFS.begin())
  {
    Serial.println("An Error has occurred while mounting LittleFS");
    return;
  }

  File file = LittleFS.open("/build", "r");
  if (!file)
  {
    Serial.println("Failed to open file for reading");
    return;
  };
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println(WiFi.localIP());
  server.serveStatic("/", LittleFS, "/build");
  server.begin();
}

void loop()
{
}