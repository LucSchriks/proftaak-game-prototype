#include <Arduino.h>
#include "wificonnect.h"
#include "playingField.h"

playingField game1;

void setup()
{
  Serial.begin(115200);
  game1.Init();
  Serial.println("esp32!!");
}

void loop()
{
  delay(1000);
  game1.fieldCallBack();
  int position = game1.getFieldPos();
  if (position == playingField::BOTTOM_LEFT){
    Serial.println("Bottom left");
  }
}