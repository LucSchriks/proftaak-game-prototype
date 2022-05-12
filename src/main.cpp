#include <Arduino.h>
#include "WiFi.h"

#define WIFI_NETWORK "LAPTOP-6LHD9VFL 8634"
#define WIFI_PASSWORD "9>sA8315"
#define WIFI_TIMEOUT 20000

void wifiConnect(){
  Serial.print("Connecting to Wifi");
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_NETWORK, WIFI_PASSWORD);
  
  unsigned long attemptTime = millis();

  while(WiFi.status() != WL_CONNECTED && millis() - attemptTime < WIFI_TIMEOUT){
    Serial.print("-");
    delay(100);
  }

  if(WiFi.status() != WL_CONNECTED){
    Serial.println("Connection failed");
  }else{
    Serial.print("Connected");
    Serial.println(WiFi.localIP());
  }
}

void setup() {
  Serial.begin(9600);
  wifiConnect();
}

void loop() {

}