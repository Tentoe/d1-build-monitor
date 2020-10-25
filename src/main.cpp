#include <Arduino.h>
#include "ArduinoJson.h"
#include <string>
#include "Music.cpp"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
// Network SSID
const char *ssid = "K-LAN";
const char *password = "";

void setup()
{
  Serial.begin(9600);
  Serial.println("Serial.begin");
  Music::playCoin();
  WiFi.hostname("Name");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
  Music::playCoin();
}

int count = 0;

void loop()
{
  if (WiFi.isConnected())
  {

    std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);

    client->setInsecure();

    HTTPClient https;

    Serial.print("[HTTPS] begin...\n");
    if (https.begin(*client, "https://date.nager.at/api/v2/PublicHolidays/2017/AT"))
    {
      int httpCode = https.GET();

      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY)
      {
        const size_t capacity = JSON_ARRAY_SIZE(13) + 13 * JSON_OBJECT_SIZE(9) + 670;
        DynamicJsonDocument doc(capacity);

        DeserializationError error = deserializeJson(doc, https.getString());
        if (error)
        {
          Serial.println("deserializeJson() failed: ");
          Serial.println(error.c_str());
        }
        //https://arduinojson.org/v6/assistant/
        JsonObject root_0 = doc[0];
        const char *root_0_date = root_0["date"];               // "2017-01-01"
        const char *root_0_localName = root_0["localName"];     // "Neujahr"
        const char *root_0_name = root_0["name"];               // "New Year's Day"
        const char *root_0_countryCode = root_0["countryCode"]; // "AT"
        bool root_0_fixed = root_0["fixed"];                    // true
        bool root_0_global = root_0["global"];                  // true
        int root_0_launchYear = root_0["launchYear"];           // 1967
        const char *root_0_type = root_0["type"];               // "Public"
        Serial.println(root_0_type);

        //Serial.println(payload);
      }

      https.end();
    }
    else
    {
      Serial.printf("[HTTPS] Unable to connect\n");
    }
  }

  Serial.println("Wait 10s before next round...");
  delay(10000);
}
