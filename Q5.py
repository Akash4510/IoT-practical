import Rpi.GPIO as GPIO
import Adafruit_DHT as dht
from time import sleep
import requests

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)

THINGSPEAK_API_KEY = ""

BASE_URL = "http://api.thingspeak.com/update"

dhtPin = 20
dhtType = dht.DHT11

while True:
  humidity, temperature = dht.read_retry(dhtType, dhtPin)

  if humidity is not None and temperature is not None:
    print(f"Temp: {temperature} °C, Humidity: {humidity} %")

  try:
    params = {
      "api_key": THINGSPEAK_API_KEY,
      "field1": temperature,
      "field2": humidity
    }
    response = requests.get(url=BASE_URL, params=params)
    print(response.status_code)
    print(response.json())
  except:
    print("Error")

  sleep(15)

