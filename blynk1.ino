//--------------- BLYNK APP SETUP -------------//
// (MUST BE IN THE VERY TOP OF THE FILE)
#define BLYNK_TEMPLATE_ID "TMPLywJyKzdu"
#define BLYNK_DEVICE_NAME "MY_DEVICE"
#define BLYNK_AUTH_TOKEN "RE38yM7eNc0QsBTosMUMY36nGhhGSnlB"

#define variable_label_1 "V_LED"

//------------- INCLUDE LIBRARIES -------------//
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

//------------- DEFINE SENSOR PINS ------------//
#define SENSOR_PIN D0

//------------- DEFINE BLYNK PINS -------------//
#define BLYNK_VIRTUAL_LED V0

//-- VARIABLES TO STORE TOUCH SENSOR DATA --//
int currentState;

//---------- DEFINE WIFI CREDENTIALS ----------//
const char *wifiSSID = "POCO M2 Pro";      // Your network SSID here
const char *wifiPassword = "************"; // Your network's password here

//----------- CREATING WIFI CLIENT ------------//
WiFiClient client;

//------------- SETUP FUNCTION ---------------//
void setup()
{
  Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, wifiSSID, wifiPassword);
}

//-------------- LOOP FUNCTION ----------------//
void loop()
{
  // Run the Blynk client
  Blynk.run();

  currentState = digitalRead(SENSOR_PIN);
  Serial.println(currentState);

  // Send the sensor values to Blynk
  Blynk.virtualWrite(BLYNK_VIRTUAL_LED, gasValue);
}
