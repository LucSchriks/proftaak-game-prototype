#include <Arduino.h>
#include "wificonnect.h"

wificonnect wifi1;

void setup()
{
  Serial.begin(115200);
  wifi1.Connect();
}

void loop()
{
  wifi1.httpReq();
  delay(10000);
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            