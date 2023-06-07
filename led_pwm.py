from Rpi.GPIO import GPIO
from time import sleep

motorPin = 21

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)
GPIO.setup(motorPin, GPIO.OUTPUT)

freq = 50
pi_pwm = GPIO.PWM(motorPin, freq)

pi_pwm.start(0)

while True:
    for duty in range(100):
        pi_pwm.changeDutyCycle(duty)
        sleep(1/freq)
    sleep(1)

    for duty in range(100):
        pi_pwm.changeDutyCycle(100 - duty)
        sleep(1/freq)
    sleep(1)
