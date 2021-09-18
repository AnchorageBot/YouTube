""" This script will demonstrate the FBS' onboard NeoPixel using a rainbow of color """

# Script Source/Engineering
  # https://learn.adafruit.com/adafruit-feather-rp2040-pico/built-in-neopixel-led
  # https://www.youtube.com/profgallaugher
  # https://github.com/AnchorageBot/YouTube

# Hardware BOM (Bill of Materials)
  # Feather Bluefruit Sense https://www.adafruit.com/product/4516
  # USB C to Micro B Cable https://www.adafruit.com/product/3878

# Software
  # Mu Python Editor https://codewith.mu
  # CircuitPython v 6.3.0 https://circuitpython.org/board/feather_bluefruit_sense/
  # Libraries v 6.x bundle https://circuitpython.org/libraries
    # neopixel.mpy

import time
import board
import neopixel

try:
    from rainbowio import colorwheel
except ImportError:
    try:
        from _pixelbuf import colorwheel
    except ImportError:
        from adafruit_pypixelbuf import colorwheel

pixel = neopixel.NeoPixel(board.NEOPIXEL, 1, auto_write=False)

pixel.brightness = 0.3

def rainbow(delay):
    for color_value in range(255):
        for led in range(1):
            pixel_index = (led * 256 // 1) + color_value
            pixel[led] = colorwheel(pixel_index & 255)
        pixel.show()
        time.sleep(delay)

while True:
    rainbow(0.02)
