# This script will demonstrate a interrupt using a RPi Pico and a hardware timer

# Programming the Pico by Simon Monk
    # http://simonmonk.org/prog_pico/
    # Chapter 9
    # https://github.com/simonmonk

# Hardware
    # Pimoroni Pico W (SC0918), https://shop.pimoroni.com
    # USB C to USB A cable (CAB0237), https://shop.pimoroni.com
    # Computer: RPi4, etc.

# Software
    # Thonny v 3.3.13, https://thonny.org
    # Python 3.7.9, https://www.python.org/downloads/release/python-379/
    # MicroPython 1.19, http://micropython.org  
    
# Raspberry Pi Pico Resources
    # Tutorial: https://learn.pimoroni.com/article/getting-started-with-pico
    # uf2 for Pico, https://github.com/pimoroni/pimoroni-pico/releases
    # Pimoroni Scripts: https://github.com/pimoroni/pimoroni-pico/tree/main/micropython/examples/badger2040
    # ATS Scripts: https://github.com/AnchorageBot/YouTube
    
# How to run this script:
    # Raspberry Pi Computers have Thonny preinstalled
    # Open the script in Thonny
    # Connect the RPi Pico to your computer via the cable
    # Select MicroPython (Raspberry Pi Pico) in Thonny (bottom right of screen)
    # Save the script as main.py on the Raspberry Pi Pico using Thonny
    # Press run current script in Thonny (Red Arrow or F5)
    
from machine import Pin, Timer
from utime import sleep

led = Pin(25, Pin.OUT)

def tick(timer):
    global led
    led.toggle()
    print("LED")

Timer().init(freq=1, mode=Timer.PERIODIC, callback=tick)

x = 0
while True:
    print(x)
    x += 1
    sleep(1.2)  
