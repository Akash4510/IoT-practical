#include <ESPS266WiFi.h>
#include <Ubidots.h>

const char *UBIDOTS_TOKEN = "";
const char *WIFI_SSID = "";
const char *WIFI_PASSWORD = "";

Ubidots ubidotsClient(UBIDOTS_TOKEN, UBI_HTTP);

int ldrValue;
const int ldrPin = A0;

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
  Serial.begin(115200);
  ubidotsClient.wifiConnect(WIFI_SSID, WIFI_PASSWORD);
}

void loop()
{
  ldrValue = analogRead(ldrPin);
  Serial.println(ldrValue);

  publishData("ldr", ldrValue);
  delay(5000);
}
