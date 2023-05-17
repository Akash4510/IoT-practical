import Rpi.GPIO as GPIO
from time import sleep

ledPin = 21

GPIO.setWarnings(False)
GPIO.setmode(GPIO.BCM)
GPIO.setup(ledPin, GPIO.OUT)

while True:
  GPIO.output(ledPin, GPIO.HIGH)
  sleep(1)
  GPIO.output(ledPin, GPIO.LOW)
  sleep(1)
