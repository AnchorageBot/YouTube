""" This script will demonstrate the FBS' onboard NeoPixel with RGB color example """

# Script Source/Engineering
  # https://learn.adafruit.com/adafruit-feather-rp2040-pico/built-in-neopixel-led
  # https://www.youtube.com/profgallaugher
  # https://github.com/AnchorageBot/YouTube

# BOM
  # Feather Bluefruit Sense https://www.adafruit.com/product/4516
  # USB C to Micro B Cable https://www.adafruit.com/product/3878

# Software
  # Mu Python Editor https://codewith.mu
  # CircuitPython v 6.3.0 https://circuitpython.org/board/feather_bluefruit_sense/
  # Libraries v 6.x bundle https://circuitpython.org/libraries
    # neopixel.mpy

# Import libraries 
import time
import board
import neopixel

# Setup neopixel 
pixel = neopixel.NeoPixel(board.NEOPIXEL, 1)
pixel.brightness = 0.3
RED = (255, 0, 0)
GREEN = (0, 255, 0)
BLUE = (0, 0, 255)

TIMESLEEP = 0.3

# Microcontroller task loop
while True:
    pixel.fill(RED)
    time.sleep(TIMESLEEP)
    pixel.fill(GREEN)
    time.sleep(TIMESLEEP)
    pixel.fill(BLUE)
    time.sleep(TIMESLEEP)
    print("Neopixel is flashing Red, Green, Blue")  
