# This script will flash SOS with the onboard LED of the RPi Pico

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

Times1 = 3
Delay1 = 0.2
Delay2 = 0.4
Sleep1 = 0.6

def blink(times, delay):
    """for loop that controls LED blinks"""
    for x in range(1,times+1):
        led.on()
        sleep(delay)
        led.off()
        sleep(delay)
    
while True:
    #blink(3, 0.2)
    blink(Times1, Delay1)
    #sleep(0.4)
    sleep(Sleep1)
    #blink(3, 0.6)
    blink(Times1, Delay2)
    
