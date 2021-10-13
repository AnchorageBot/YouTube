# This script uses a while True loop to light neopixels on the CPB with CircuitPython

# Coding concepts used in the script

    # while True means loop forever
        # The while statement takes an expression and executes the loop body
            # while the expression evaluates to (boolean) "true". True always evaluates to
            # boolean "true" and thus executes the loop body indefinitely
    # https://stackoverflow.com/questions/3754620/what-does-while-true-mean-in-python

# Materials
  # Circuit Playground Bluefruit (CPB) https://www.adafruit.com/product/4333
  # USB A to Micro B data cable https://www.adafruit.com/product/592

# Dr Gallaugher's CPB Tutorials
    # https://www.youtube.com/playlist?list=PL9VJ9OpT-IPSsQUWqQcNrVJqy4LhBjPX2

# Anchorage Tech Solutions YouTubes & Code
    # https://www.youtube.com/channel/UCDuWq2wFqeVII1KC7grySRg?view_as=subscriber
    # https://github.com/AnchorageBot/YouTube

import board        # CircuitPython Library https://circuitpython.org/libraries
import neopixel
import time

pixels = neopixel.NeoPixel(board.NEOPIXEL, 10, brightness = 0.25, auto_write=True)
                    # https://learn.adafruit.com/circuitpython-essentials/circuitpython-neopixel
                    # https://github.com/adafruit/Adafruit_CircuitPython_NeoPixel

while True:
    pixels.fill((0, 211, 202))
    time.sleep(1.0)
    pixels.fill((0,0,0))
    time.sleep(1.0)
