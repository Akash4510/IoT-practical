#include <ESP8266WiFi.h>
#include <Ubidots.h>

const char *UBIDOTS_TOKEN = "YOUR_TOKEN_HERE";
const char *DEVICE_LABEL = "DEVICE_LABEL";
const char *VARIABLE_LABEL = "VARIABLE_LABEL";

const char *WIFI_SSID = "";
const char *WIFI_PASSWORD = "";

Ubidots ubidotsClient(UBIDOTS_TOKEN, UBI_HTTP);

const int ldrPin = A0;
int ldrValue;

void publishData(variableLabel, value)
{
  bool bufferSent = false;

  ubidotsClient.add(variableLabel, value);
  bufferSent = ubidotsClient.send();

  if (bufferSent)
  {
    Serial.println("Data published successfully");
  }
  else
  {
    Serial.println("Failed to publish data");
  }
}

void setup()
{
  Serial.begin(9600);
  ubidotsClient.wifiConnect(WIFI_SSID, WIFI_PASSWORD);
}

void loop()
{
  ldrValue = analogRead(ldrPin);
  Serial.println(ldrValue);

  publishData(VARIABLE_LABEL, ldrValue);
  delay(15000);
}
