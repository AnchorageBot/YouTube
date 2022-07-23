# This script will blink the onboard LED of a Raspberry Pi Pico

# Reference
  # Programming the Pico, Simon Monk
  # https://github.com/simonmonk/prog_pico_ed1

# Software
  # Thonny 3.3.13
  # MicroPython v1.18
  
# Hardware
  # Raspberry Pi Pico with RP2040 and micro USB cable

from machine import Pin
from utime import sleep

led = Pin(25, Pin.OUT)

SleepVariable1 = 0.5

while True:
    led.on()
    sleep(SleepVariable1)
    led.off()
    sleep(SleepVariable1)
