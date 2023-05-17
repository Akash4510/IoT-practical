const int sensorPin = A0;
int value, voltageOut, celcius;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  value = analogRead(sensorPin);
  voltageOut = (value * 5000) / 1024;
  celcius = voltageOut / 10;

  Serial.print("Temperature: ");
  Serial.print(celcius);
  Serial.println(" °C");
}
