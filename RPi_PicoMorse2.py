# This script will flash an SOS with the onboard LED of a RPi Pico

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

SleepVariable1 = 0.2
SleepVariable2 = 0.6

while True:
    
    # Code for the letter S = three dots
    led.on()
    sleep(SleepVariable1)
    led.off()
    sleep(SleepVariable1)
    
    led.on()
    sleep(SleepVariable1)
    led.off()
    sleep(SleepVariable1)
    
    led.on()
    sleep(SleepVariable1)
    led.off()
    sleep(SleepVariable1)
    
    # Time gap between S and O
    sleep(SleepVariable2)
    
    # Code for the letter O = three dashes
    led.on()
    sleep(SleepVariable2)
    led.off()
    sleep(SleepVariable2)
    
    led.on()
    sleep(SleepVariable2)
    led.off()
    sleep(SleepVariable2)
    
    led.on()
    sleep(SleepVariable2)
    led.off()
    sleep(SleepVariable2)
    
