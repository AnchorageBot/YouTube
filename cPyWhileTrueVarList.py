# This script uses a while True loop, Variables, and Lists to light neopixels on the CPB with CircuitPython

# Coding concepts used in the script

    # while True means loop forever
        # The while statement takes an expression and executes the loop body.
            # while the expression evaluates to (boolean) "true". True always evaluates to
            # boolean "true" and thus executes the loop body indefinitely.
    #https://stackoverflow.com/questions/3754620/what-does-while-true-mean-in-python

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

# Dr Gallaugher's CPB Tutorials
    # https://www.youtube.com/playlist?list=PL9VJ9OpT-IPSsQUWqQcNrVJqy4LhBjPX2

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

RedColor = (255, 0, 0)      # Variable - color choice
GreenColor = (0, 255, 0)
BlueColor = (0, 0, 255)
NoColor = (0, 0, 0)

TimeOnOff = 1.0             # Variable - the amount of time the neopixels are on or off

while True:                 # While True Loop

    pixels[0] = (RedColor)  # Each neopixel is an element of the list pixels and has a specific index position
    time.sleep(TimeOnOff)
    pixels[0] = (NoColor)
    time.sleep(TimeOnOff)

    pixels[2] = (GreenColor) # Each neopixel is an element of the list pixels and has a specific index position
    time.sleep(TimeOnOff)
    pixels[2] = (NoColor)
    time.sleep(TimeOnOff)

    pixels[4] = (BlueColor)  # Each neopixel is an element of the list pixels and has a specific index position
    time.sleep(TimeOnOff)
    pixels[4] = (NoColor)
    time.sleep(TimeOnOff)

    pixels[5] = (BlueColor)  # Each neopixel is an element of the list pixels and has a specific index position
    time.sleep(TimeOnOff)
    pixels[5] = (NoColor)
    time.sleep(TimeOnOff)

    pixels[7] = (GreenColor)  # Each neopixel is an element of the list pixels and has a specific index position
    time.sleep(TimeOnOff)
    pixels[7] = (NoColor)
    time.sleep(TimeOnOff)

    pixels[9] = (RedColor)  # Each neopixel is an element of the list pixels and has a specific index position
    time.sleep(TimeOnOff)
    pixels[9] = (NoColor)
    time.sleep(TimeOnOff)
