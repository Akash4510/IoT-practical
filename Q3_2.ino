#include <ESP8266WiFi.h>
#include <Ubidots.h>

const char *UBIDOTS_TOKEN = "YOUR_TOKEN_HERE";
const char *DEVICE_LABEL = "DEVICE_LABEL";
const char *VARIABLE_LABEL = "VARIABLE_LABEL";

const char *WIFI_SSID = "";
const char *WIFI_PASSWORD = "";

Ubidots ubidotsClient(UBIDOTS_TOKEN);

const int ldrPin = A0;
int ldrVal;

void publishData(char *variableLabel, int val)
{
  bool bufferSent = false;

  ubidotsClient.add(variableLabel, val);
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

void callback(char *topic, byte *payload, unsigned long length)
{
  Serial.print("Message arrived: [");
  Serial.print(topic);
  Serial.print("] ");

  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }

  Serial.println();
}

void setup()
{
  Serial.begin(9600);
  ubidotsClient.wifiConnect(WIFI_SSID, WIFI_PASSWORD);
  ubidotsClient.begin(callback);
}

void loop()
{
  if (!ubidotsClient.connected())
  {
    ubidotsClient.reconnect();
  }
  else
  {
    ldrVal = analogRead(ldrPin);
    Serial.println(ldrVal);

    publishData(VARIABLE_LABEL, ldrVal);
  }

  ubidotsClient.loop();
  delay(15000);
}
