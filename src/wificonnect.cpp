#include <Arduino.h>
#include "WiFi.h"
#include "HTTPClient.h"
#include "WiFiClientSecure.h"
#include "wifisecrets.h"
#include "wificonnect.h"

HTTPClient http;
WiFiClientSecure client;

wificonnect::wificonnect(){
  #define WIFI_TIMEOUT 20000
}


void wificonnect::Connect()
{
  Serial.print("Connecting to Wifi");
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_NETWORK, WIFI_PASSWORD);

  unsigned long attemptTime = millis();

  while (WiFi.status() != WL_CONNECTED && millis() - attemptTime < WIFI_TIMEOUT)
  {
    Serial.print("-");
    delay(100);
  }

  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("Connection failed");
  }
  else
  {
    Serial.print("Connected");
    Serial.println(WiFi.localIP());
  }
  client.setCACert(ca_cert);
}

void wificonnect::httpReq(){
    http.setTimeout(10000);
  http.begin(client, "https://www.google.com/");
  
  int httpCode = http.GET();
  if (httpCode > 0)
  {
    String payload = http.getString();
    Serial.println(httpCode);
    Serial.println(payload);
  } else
  {
    Serial.println("Error on HTTP request");
  }
  http.end();
}
