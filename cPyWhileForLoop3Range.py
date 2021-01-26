# This script uses a while loop, a for loop, Variables & Lists to light neopixels on the CPB with CircuitPython
# Three range numbers are used
    # Start point is the first range number
    # Stop point is one number before the last range number
    # Increment, or step size, is the third range number

# Coding concepts used in the script

    # while True means loop forever
        # The while statement takes an expression and executes the loop body.
            # while the expression evaluates to (boolean) "true". True always evaluates to
            # boolean "true" and thus executes the loop body indefinitely.
    #https://stackoverflow.com/questions/3754620/what-does-while-true-mean-in-python

    # A for loop will repeat indented commands a specified number of times
        # Dr Gallaugher's CPB Tutorials
        # https://www.youtube.com/watch?v=v-mGgjM6leo&list=PL9VJ9OpT-IPSsQUWqQcNrVJqy4LhBjPX2&index=7
        # https://www.youtube.com/playlist?list=PL9VJ9OpT-IPSsQUWqQcNrVJqy4LhBjPX2

    # Variables are symbolic names that reference or point (pointer) to an object.
        # Once an object is assigned to a variable, you can refer to the object by that name.
    # https://realpython.com/python-variables/

    # A list is a data structure in Python that is a mutable (changeable) ordered sequence of elements.
        # Each element or value that is inside of a list is called an item.
        # Lists are defined by having values between square brackets [ ].
    # https://www.digitalocean.com/community/tutorials/understanding-lists-in-python-3

# Materials
  # Circuit Playground Bluefruit (CPB) https://www.adafruit.com/product/4333
  # USB A to Micro B data cable https://www.adafruit.com/product/592

# Adafruit Circuit Playground API
    # https://circuitpython.readthedocs.io/projects/circuitplayground/en/latest/api.html#adafruit-circuitplayground-bluefruit

# Anchorage Tech Solutions YouTubes & Code
    # https://www.youtube.com/channel/UCDuWq2wFqeVII1KC7grySRg?view_as=subscriber
    # https://github.com/AnchorageBot/YouTube

import board                # CircuitPython Library https://circuitpython.org/libraries
import neopixel
import time

pixels = neopixel.NeoPixel(board.NEOPIXEL, 10, brightness = 0.25, auto_write=True)
                            # https://learn.adafruit.com/circuitpython-essentials/circuitpython-neopixel
                            # https://github.com/adafruit/Adafruit_CircuitPython_NeoPixel
                            # pixels is a variable that also functions as a list

while True:                 # While True Loop
    for NeoPixelNumber in range(2,8,2):             # Variable - NeoPixelNumber, Range runs across the list [2,3,4,5,6,7] however it counts by twos
        pixels[NeoPixelNumber] = (255,0,255)
        time.sleep(0.5)
    pixels.fill((0, 0, 0))                        # Turn off the NeoPixels
    time.sleep(0.5)
