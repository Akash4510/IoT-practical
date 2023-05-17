#include <ESP8266WiFi.h>
#include <Thingspeak.h>

const char *WIFI_SSID = "";
const char *WIFI_PASSWORD = "";

unsigned long THINGSPEAK_CHANNEL_ID = 0;
const char *THINGSPEAK_READ_API_KEY = "";
const char *THINGSPEAK_WRITE_API_KEY = "";

const int ldrPin = A0;
const int ledPin = D1;
int ldrValue;
int cloudValue;

WiFiClient client;

void setup()
{
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Thingspeak.begin(client);

  pinMode(ledPin, OUTPUT);
}

void loop()
{
  ldrValue = analogRead(ldrPin);
  Serial.println(ldrValue);

  ThingSpeak.setField(1, ldrValue);
  ThingSpeak.writeFields(THINGSPEAK_CHANNEL_ID, THINGSPEAK_WRITE_API_KEY);

  cloudValue = ThingSpeak.readLongField(THINGSPEAK_CHANNEL_ID, 1, THINGSPEAK_READ_API_KEY);
  Serial.print("Cloud value: ");
  Serial.println(cloudValue);

  if (cloudValue < 200)
  {
    digitalWrite(ledPin, HIGH);
  }
  else
  {
    digitalWrite(ledPin, LOW);
  }

  delay(15000);
}
