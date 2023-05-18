#include <ESP8266WiFi.h>
#include <Thingspeak.h>
#include <DHT.h>

#define DHT_PIN D0
#define DHT_TYPE DHT11

DHT dht(DHT_PIN, DHT_TYPE);

const unsigned long THINGSPEAK_CHANNEL_ID = 0;
const char *THINGSPEAK_READ_API_KEY = "";
const char *THINGSPEAK_WRITE_API_KEY = "";

const char *WIFI_SSID = "";
const char *WIFI_PASSWORD = "";

WiFiClient client;

const int ldrPin = A0;
const int ledPin1 = D1;
const int ledPin2 = D2;
const int ledPin3 = D3;

float ldrValue, temperature, humidity;
float cloudLdrVal, cloudTempVal, cloudHumiVal;

const float ldrThresh = 200;
const float tempThresh = 32;
const float humiThresh = 30;

void setup()
{
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Thingspeak.begin(client);

  pinmode(ledPin1, OUTPUT);
  pinmode(ledPin2, OUTPUT);
  pinmode(ledPin3, OUTPUT);
}

void loop()
{
  ldrValue = analogRead(ldrPin);
  Serial.println(ldrValue);

  temperature = dht.readTemperature();
  humidity = dht.readHumidity();

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C\n");

  Thingspeak.setField(1, ldrValue);
  Thingspeak.setField(2, temperature);
  Thingspeak.setField(3, humidity);
  Thingspeak.writeFields(THINGSPEAK_CHANNEL_ID, THINGSPEAK_WRITE_API_KEY);

  cloudLdrVal = Thingspeak.readField(THINGSPEAK_CHANNEL_ID, 1, THINGSPEAK_READ_API_KEY);
  cloudTempVal = Thingspeak.readField(THINGSPEAK_CHANNEL_ID, 2, THINGSPEAK_READ_API_KEY);
  cloudHumiVal = Thingspeak.readField(THINGSPEAK_CHANNEL_ID, 3, THINGSPEAK_READ_API_KEY);

  if (cloudLdrVal < ldrThresh)
    digitalWrite(ledPin1, HIGH);
  else
    digialWrite(ledPin1, LOW);

  if (cloudTempVal > tempThresh)
    digitalWrite(ledPin2, HIGH);
  else
    digialWrite(ledPin2, LOW);

  if (cloudHumiVal < humiThresh)
    digitalWrite(ledPin3, HIGH);
  else
    digialWrite(ledPin3, LOW);

  delay(15000);
}
