import Adafruit_DHT as dht

dhtPin = 21
dhtType = dht.DHT11

while True:
  humidity, temperature = dht.read_retry(dhtType, dhtPin)
  
  if humidity is not None and temperature is not None:
    print(f"Temp: {temperature} °C, Humidity: {humidity} %")
