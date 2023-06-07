import Rpi.GPIO as GPIO
from time import sleep
import requests
import Adafruit_DHT as dht

THINGSPEAK_API_KEY = ""
BASE_URL = "https://api.thingspeak.com/update"

dht_pin = 21
dht_type = dht.DHT11

while True:
    humidity, temperature = dht.read_retry(dht_type, dht_pin)

    if humidity is not None and temperature is not None:
        print(f"Temp: {temperature} °C, Humidity: {humidity} %")

    try:
        params = {
            "api_key": THINGSPEAK_API_KEY,
            "field1": temperature,
            "field2": humidity,
        }
        response = requests.get(url=BASE_URL, params=params)
        print(response.status_code)
        print(response.json())
    except:
      print("Error")

    sleep(15)
