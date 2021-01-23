# This script uses a while True loop and Variables to light neopixels on the CPB with CircuitPython

# Coding concepts used in the script

    # while True means loop forever
        # The while statement takes an expression and executes the loop body.
            # while the expression evaluates to (boolean) "true". True always evaluates to
            # boolean "true" and thus executes the loop body indefinitely.
    #https://stackoverflow.com/questions/3754620/what-does-while-true-mean-in-python

    # Variables are symbolic names that reference or point (pointer) to an object.
        # Once an object is assigned to a variable, you can refer to the object by that name.
    # https://realpython.com/python-variables/

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

numberOfNeoPixels = 10      # Variable - the number of neopixels that light up

pixels = neopixel.NeoPixel(board.NEOPIXEL, numberOfNeoPixels, brightness = 0.25, auto_write=True)
                            # https://learn.adafruit.com/circuitpython-essentials/circuitpython-neopixel
                            # https://github.com/adafruit/Adafruit_CircuitPython_NeoPixel

RedColor = (255, 0, 0)      # Variable - color choice
GreenColor = (0, 255, 0)
BlueColor = (0, 0, 255)
NoColor = (0, 0, 0)

TimeOnOff = 1.0             # Variable - the amount of time the neopixels are on or off

while True:                 # While True Loop
    pixels.fill(RedColor)
    time.sleep(TimeOnOff)
    pixels.fill(NoColor)
    time.sleep(TimeOnOff)

    pixels.fill(GreenColor)
    time.sleep(TimeOnOff)
    pixels.fill(NoColor)
    time.sleep(TimeOnOff)

    pixels.fill(BlueColor)
    time.sleep(TimeOnOff)
    pixels.fill(NoColor)
    time.sleep(TimeOnOff)
