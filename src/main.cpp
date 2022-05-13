#include <Arduino.h>
#include "WiFi.h"
#include "HTTPClient.h"

#define WIFI_NETWORK "LAPTOP-6LHD9VFL 8634"
#define WIFI_PASSWORD "9>sA8315"
#define WIFI_TIMEOUT 20000

const char* ca_cert = \
"-----BEGIN CERTIFICATE-----\n" \
"MIIN1zCCDL+gAwIBAgIQWUMcfA6xXEkKAU5gNLgssjANBgkqhkiG9w0BAQsFADBG\n" \
"MQswCQYDVQQGEwJVUzEiMCAGA1UEChMZR29vZ2xlIFRydXN0IFNlcnZpY2VzIExM\n" \
"QzETMBEGA1UEAxMKR1RTIENBIDFDMzAeFw0yMjA0MjUwODMxMThaFw0yMjA3MTgw\n" \
"ODMxMTdaMBcxFTATBgNVBAMMDCouZ29vZ2xlLmNvbTBZMBMGByqGSM49AgEGCCqG\n" \
"SM49AwEHA0IABIFjq9MpohVs7rdDZlXFiG5wm01DQGbqpPzABotM/WAjX/eg5Dxa\n" \
"r3/lNmOIVd3iYEFsoSc9SPsuaiFtAaouJX6jggu5MIILtTAOBgNVHQ8BAf8EBAMC\n" \
"B4AwEwYDVR0lBAwwCgYIKwYBBQUHAwEwDAYDVR0TAQH/BAIwADAdBgNVHQ4EFgQU\n" \
"iwkxiN0wplnThuU96gZt88AlltUwHwYDVR0jBBgwFoAUinR/r4XN7pXNPZzQ4kYU\n" \
"83E1HScwagYIKwYBBQUHAQEEXjBcMCcGCCsGAQUFBzABhhtodHRwOi8vb2NzcC5w\n" \
"a2kuZ29vZy9ndHMxYzMwMQYIKwYBBQUHMAKGJWh0dHA6Ly9wa2kuZ29vZy9yZXBv\n" \
"L2NlcnRzL2d0czFjMy5kZXIwggloBgNVHREEgglfMIIJW4IMKi5nb29nbGUuY29t\n" \
"ghYqLmFwcGVuZ2luZS5nb29nbGUuY29tggkqLmJkbi5kZXaCEiouY2xvdWQuZ29v\n" \
"Z2xlLmNvbYIYKi5jcm93ZHNvdXJjZS5nb29nbGUuY29tghgqLmRhdGFjb21wdXRl\n" \
"Lmdvb2dsZS5jb22CCyouZ29vZ2xlLmNhggsqLmdvb2dsZS5jbIIOKi5nb29nbGUu\n" \
"Y28uaW6CDiouZ29vZ2xlLmNvLmpwgg4qLmdvb2dsZS5jby51a4IPKi5nb29nbGUu\n" \
"Y29tLmFygg8qLmdvb2dsZS5jb20uYXWCDyouZ29vZ2xlLmNvbS5icoIPKi5nb29n\n" \
"bGUuY29tLmNvgg8qLmdvb2dsZS5jb20ubXiCDyouZ29vZ2xlLmNvbS50coIPKi5n\n" \
"b29nbGUuY29tLnZuggsqLmdvb2dsZS5kZYILKi5nb29nbGUuZXOCCyouZ29vZ2xl\n" \
"LmZyggsqLmdvb2dsZS5odYILKi5nb29nbGUuaXSCCyouZ29vZ2xlLm5sggsqLmdv\n" \
"b2dsZS5wbIILKi5nb29nbGUucHSCEiouZ29vZ2xlYWRhcGlzLmNvbYIPKi5nb29n\n" \
"bGVhcGlzLmNughEqLmdvb2dsZXZpZGVvLmNvbYIMKi5nc3RhdGljLmNughAqLmdz\n" \
"dGF0aWMtY24uY29tgg9nb29nbGVjbmFwcHMuY26CESouZ29vZ2xlY25hcHBzLmNu\n" \
"ghFnb29nbGVhcHBzLWNuLmNvbYITKi5nb29nbGVhcHBzLWNuLmNvbYIMZ2tlY25h\n" \
"cHBzLmNugg4qLmdrZWNuYXBwcy5jboISZ29vZ2xlZG93bmxvYWRzLmNughQqLmdv\n" \
"b2dsZWRvd25sb2Fkcy5jboIQcmVjYXB0Y2hhLm5ldC5jboISKi5yZWNhcHRjaGEu\n" \
"bmV0LmNughByZWNhcHRjaGEtY24ubmV0ghIqLnJlY2FwdGNoYS1jbi5uZXSCC3dp\n" \
"ZGV2aW5lLmNugg0qLndpZGV2aW5lLmNughFhbXBwcm9qZWN0Lm9yZy5jboITKi5h\n" \
"bXBwcm9qZWN0Lm9yZy5jboIRYW1wcHJvamVjdC5uZXQuY26CEyouYW1wcHJvamVj\n" \
"dC5uZXQuY26CF2dvb2dsZS1hbmFseXRpY3MtY24uY29tghkqLmdvb2dsZS1hbmFs\n" \
"eXRpY3MtY24uY29tghdnb29nbGVhZHNlcnZpY2VzLWNuLmNvbYIZKi5nb29nbGVh\n" \
"ZHNlcnZpY2VzLWNuLmNvbYIRZ29vZ2xldmFkcy1jbi5jb22CEyouZ29vZ2xldmFk\n" \
"cy1jbi5jb22CEWdvb2dsZWFwaXMtY24uY29tghMqLmdvb2dsZWFwaXMtY24uY29t\n" \
"ghVnb29nbGVvcHRpbWl6ZS1jbi5jb22CFyouZ29vZ2xlb3B0aW1pemUtY24uY29t\n" \
"ghJkb3VibGVjbGljay1jbi5uZXSCFCouZG91YmxlY2xpY2stY24ubmV0ghgqLmZs\n" \
"cy5kb3VibGVjbGljay1jbi5uZXSCFiouZy5kb3VibGVjbGljay1jbi5uZXSCDmRv\n" \
"dWJsZWNsaWNrLmNughAqLmRvdWJsZWNsaWNrLmNughQqLmZscy5kb3VibGVjbGlj\n" \
"ay5jboISKi5nLmRvdWJsZWNsaWNrLmNughFkYXJ0c2VhcmNoLWNuLm5ldIITKi5k\n" \
"YXJ0c2VhcmNoLWNuLm5ldIIdZ29vZ2xldHJhdmVsYWRzZXJ2aWNlcy1jbi5jb22C\n" \
"HyouZ29vZ2xldHJhdmVsYWRzZXJ2aWNlcy1jbi5jb22CGGdvb2dsZXRhZ3NlcnZp\n" \
"Y2VzLWNuLmNvbYIaKi5nb29nbGV0YWdzZXJ2aWNlcy1jbi5jb22CF2dvb2dsZXRh\n" \
"Z21hbmFnZXItY24uY29tghkqLmdvb2dsZXRhZ21hbmFnZXItY24uY29tghhnb29n\n" \
"bGVzeW5kaWNhdGlvbi1jbi5jb22CGiouZ29vZ2xlc3luZGljYXRpb24tY24uY29t\n" \
"giQqLnNhZmVmcmFtZS5nb29nbGVzeW5kaWNhdGlvbi1jbi5jb22CFmFwcC1tZWFz\n" \
"dXJlbWVudC1jbi5jb22CGCouYXBwLW1lYXN1cmVtZW50LWNuLmNvbYILZ3Z0MS1j\n" \
"bi5jb22CDSouZ3Z0MS1jbi5jb22CC2d2dDItY24uY29tgg0qLmd2dDItY24uY29t\n" \
"ggsybWRuLWNuLm5ldIINKi4ybWRuLWNuLm5ldIIUZ29vZ2xlZmxpZ2h0cy1jbi5u\n" \
"ZXSCFiouZ29vZ2xlZmxpZ2h0cy1jbi5uZXSCDGFkbW9iLWNuLmNvbYIOKi5hZG1v\n" \
"Yi1jbi5jb22CDSouZ3N0YXRpYy5jb22CFCoubWV0cmljLmdzdGF0aWMuY29tggoq\n" \
"Lmd2dDEuY29tghEqLmdjcGNkbi5ndnQxLmNvbYIKKi5ndnQyLmNvbYIOKi5nY3Au\n" \
"Z3Z0Mi5jb22CECoudXJsLmdvb2dsZS5jb22CFioueW91dHViZS1ub2Nvb2tpZS5j\n" \
"b22CCyoueXRpbWcuY29tggthbmRyb2lkLmNvbYINKi5hbmRyb2lkLmNvbYITKi5m\n" \
"bGFzaC5hbmRyb2lkLmNvbYIEZy5jboIGKi5nLmNuggRnLmNvggYqLmcuY2+CBmdv\n" \
"by5nbIIKd3d3Lmdvby5nbIIUZ29vZ2xlLWFuYWx5dGljcy5jb22CFiouZ29vZ2xl\n" \
"LWFuYWx5dGljcy5jb22CCmdvb2dsZS5jb22CEmdvb2dsZWNvbW1lcmNlLmNvbYIU\n" \
"Ki5nb29nbGVjb21tZXJjZS5jb22CCGdncGh0LmNuggoqLmdncGh0LmNuggp1cmNo\n" \
"aW4uY29tggwqLnVyY2hpbi5jb22CCHlvdXR1LmJlggt5b3V0dWJlLmNvbYINKi55\n" \
"b3V0dWJlLmNvbYIUeW91dHViZWVkdWNhdGlvbi5jb22CFioueW91dHViZWVkdWNh\n" \
"dGlvbi5jb22CD3lvdXR1YmVraWRzLmNvbYIRKi55b3V0dWJla2lkcy5jb22CBXl0\n" \
"LmJlggcqLnl0LmJlghphbmRyb2lkLmNsaWVudHMuZ29vZ2xlLmNvbYIbZGV2ZWxv\n" \
"cGVyLmFuZHJvaWQuZ29vZ2xlLmNughxkZXZlbG9wZXJzLmFuZHJvaWQuZ29vZ2xl\n" \
"LmNughhzb3VyY2UuYW5kcm9pZC5nb29nbGUuY24wIQYDVR0gBBowGDAIBgZngQwB\n" \
"AgEwDAYKKwYBBAHWeQIFAzA8BgNVHR8ENTAzMDGgL6AthitodHRwOi8vY3Jscy5w\n" \
"a2kuZ29vZy9ndHMxYzMvUU92SjBOMXNUMkEuY3JsMIIBBQYKKwYBBAHWeQIEAgSB\n" \
"9gSB8wDxAHYAKXm+8J45OSHwVnOfY6V35b5XfZxgCvj5TV0mXCVdx4QAAAGAYA+0\n" \
"9gAABAMARzBFAiEAlumo5t9ZA1rplQha53MjnQ+GQWz/1ssmkLYHwt/2V2kCIG3e\n" \
"LWEDB7ZfXiyRjKAj+OvEx0TCdFqlavSSV6ln6I+AAHcA36Veq2iCTx9sre64X04+\n" \
"WurNohKkal6OOxLAIERcKnMAAAGAYA+1IQAABAMASDBGAiEAkTY6sD/X+7xm/K9t\n" \
"C30liXKatfN8rstm3cq1s9XUrggCIQDnVdmCtu5H+vbbJZAkRM9tR8tCGesNkonQ\n" \
"7NeSukUQqjANBgkqhkiG9w0BAQsFAAOCAQEAXCti7PbukgwomJKvNfB4W3XyosXp\n" \
"VgTaMe0MkhY6FEf5YH3kNjOCE2hUN0eB+LYOZqeHxPWCylhiohVjFihbjrznGK+X\n" \
"ovSSkuMvad+6eoCSIBQiTz0macb4kNEsNlcKXCAAhtK9UtsZOUYSsGUdFj3xWEvW\n" \
"GcBLDeutC7kcA63L0QQzoiy4M/YBfHF/6IoywXSaEferuf/4iZnz+VB7Mcf6/HHR\n" \
"xvK00oKThK7Y61VB1N6df0dEBUr7pwmyiZmnf2QTUr5z7gC5HK3hREhBpHdVjQrI\n" \
"sLtp/pqEpc0tqWE7YJLkQ9YredZaDdv3f3r8fcNZ433XR3jCsn1t8np1SQ==    \n" \
"-----END CERTIFICATE-----\n";

HTTPClient http;

void wifiConnect()
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
}

void setup()
{
  Serial.begin(115200);
  wifiConnect();
}

void loop()
{
  http.begin("https://www.google.com/", ca_cert);
  
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
  delay(10000);
}