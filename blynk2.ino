#define BLYNK_TEMPLATE_ID "TMPLywJyKzdu"
#define BLYNK_DEVICE_NAME "MY_DEVICE"
#define BLYNK_AUTH_TOKEN "RE38yM7eNc0QsBTosMUMY36nGhhGSnlB"

#define variable_label_1 "V_LED"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define SENSOR_PIN D0
#define BLYNK_VIRTUAL_LED V0

int currentState;

const char *wifiSSID = "POCO M2 Pro";      // Your network SSID here
const char *wifiPassword = "************"; // Your network's password here
WiFiClient client;

void setup()
{
  Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, wifiSSID, wifiPassword);
}

void loop()
{
  Blynk.run();

  currentState = digitalRead(SENSOR_PIN);
  Serial.println(currentState);

  Blynk.virtualWrite(BLYNK_VIRTUAL_LED, currentState);
}
