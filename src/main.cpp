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

#define BUILTIN_LED 2

AsyncWebServer server(80);

bool ledStatus = false;


void setup()
{
  Serial.begin(115200);
  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(BUILTIN_LED, !ledStatus);

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

  // connect wifi
  WiFi.begin(ssid, password);

  Serial.println();
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("\n🚀 http://" + (WiFi.localIP()).toString());

  // server config
  // React app
  server.serveStatic("/web/", LittleFS, "/build");
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->redirect("/web/index.html"); }); // redirect from / to /web/index.html

  // API examples
  server.on("/api", HTTP_ANY, [](AsyncWebServerRequest *request)
            {
              if (request->hasParam("led"))
                ledStatus = request->getParam("led")->value() == "true" ;
              digitalWrite(BUILTIN_LED, !ledStatus);
      
              String ledStatusString =  ledStatus ? "true" : "false"; // convert to string
              String response = "{\"led\":\"" + ledStatusString + ",\"uptime\":\"" + String(millis() / 1000) +  "\"}";
              request->send(200, "application/json", response); 
          }
  );

  server.begin();
}

void loop()
{
}