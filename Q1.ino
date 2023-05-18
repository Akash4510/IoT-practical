#include <ESP8266WiFi.h>
#include <Thingspeak.h>

const unsigned long THINGSPEAK_CHANNEL_ID = 0;
const char *THINGSPEAK_READ_API_KEY = "";
const char *THINGSPEAK_WRITE_API_KEY = "";

const char *WIFI_SSID = "";
const char *WIFI_PASSWORD = "";

WiFiClient client;

const int ldrPin = A0;
const int ledPin = D1;
float ldrValue, cloudValue;

void setup()
{
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Thingspeak.begin(client);

  pinmode(ledPin, OUTPUT);
}

void loop()
{
  ldrValue = analogRead(ldrPin);
  Serial.println(ldrValue);

  Thingspeak.setField(1, ldrValue);
  Thingspeak.writeFields(THINGSPEAK_CHANNEL_ID, THINGSPEAK_WRITE_API_KEY);

  cloudValue = Thingspeak.readField(THINGSPEAK_CHANNEL_ID, 1, THINGSPEAK_READ_API_KEY);

  if (cloudValue < 200)
    digitalWrite(ledPin, HIGH);
  else
    digialWrite(ledPin, LOW);

  delay(15000);
}
