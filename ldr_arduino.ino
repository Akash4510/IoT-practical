const int ldrPin = A0;
int ldrValue;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  ldrValue = analogRead(ldrPin);
  Serial.println(ldrValue);
}
