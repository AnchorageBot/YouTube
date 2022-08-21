# This script will blink the Badger2040's onboard LED

# Hardware
    # Pimoroni Badger2040 (PIM607), https://shop.pimoroni.com
    # USB C to USB A cable (CAB0237), https://shop.pimoroni.com
    # Computer: RPi4, etc.

# Software
    # Thonny v 3.3.13, https://thonny.org
    # Python 3.7.9, https://www.python.org/downloads/release/python-379/
    # MicroPython, http://micropython.org 
    
# Badger2040 Resources
    # Tutorial: https://learn.pimoroni.com/article/getting-started-with-badger-2040
    # uf2 for Badger2040, https://github.com/pimoroni/pimoroni-pico/releases
    # Pimoroni Scripts: https://github.com/pimoroni/pimoroni-pico/tree/main/micropython/examples/badger2040
    # ATS Scripts: https://github.com/AnchorageBot/YouTube
    
# How to run this script:
    # Raspberry Pi Computers have Thonny preinstalled
    # Open the script in Thonny
    # Connect the Badger2040 to your computer via the cable
    # Select MicroPython (Raspberry Pi Pico) in Thonny (bottom right of screen)
    # Save the script as main.py on the Raspberry Pi Pico using Thonny
    # Press run current script in Thonny (Red Arrow or F5)  

import badger2040
import time

badger = badger2040.Badger2040()

interval = 0.25

while True:
    badger.led(255)
    time.sleep(interval)
    badger.led(0)
    time.sleep(interval)
