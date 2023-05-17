#include <ESP8266WiFi.h>
#include <Ubidots.h>

const char *UBIDOTS_TOKEN = "";
const char *WIFI_SSID = "";
const char *WIFI_PASSWORD = "";

Ubidots ubidotsClient(UBIDOTS_TOKEN);

const char *DEVICE_LABEL = "MY_DEVICE";
const char *VARIABLE_LABEL = "LDR_DATA";

int subscribedValue;
int ldrValue;
const int ldrPin = A0;

// Adding asynchronous delay for publishing data
unsigned long previousMillis = 0;
const long publishDelay = 1000;

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

void callback(char *topic, byte *payload, unsigned long length)
{
  Serial.print("\nMessage arrived: [");
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
  Serial.begin(115200);
  ubidotsClient.wificonnect(WIFI_SSID, WIFI_PASSWORD);
  ubidotsClient.begin(callback);
  ubidotsClient.subscribe(DEVICE_LABEL, VARIABLE_LABEL);
}

void loop()
{
  if (!ubidotsClient.connected())
  {
    ubidotsClient.reconnect();
    ubidotsClient.subscribe(DEVICE_LABEL, VARIABLE_LABEL);
  }
  else
  {
    ldrValue = analogRead(ldrPin);
    Serial.println(ldrValue);

    if (millis() - previousMillis >= publishDelay)
    {
      publishData("ldr", ldrValue);
      previousMillis = millis();
    }

    ubidotsClient.loop();
  }
}
