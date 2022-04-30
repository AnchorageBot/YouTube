#! /usr/bin/python3

# LED Wiring to GPIO
  # Power: Pin 1
  # Ground: Pin 6
  # Signal: Pin 18

from periphery import GPIO
import time

gpio = GPIO(138, "out")

gpio.write(True)
time.sleep(1)
gpio.write(False)
time.sleep(1)
gpio.write(True)
time.sleep(1)
gpio.write(False)
time.sleep(1)
gpio.write(True)
time.sleep(1)

gpio.close()
