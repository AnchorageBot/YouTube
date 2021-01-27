# This script will register temperature and show a color stoplight (Red, Green, Blue)

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
  
# Software
    # Mu Python Editor Webpage
    # https://codewith.mu/en/download

# Adafruit Circuit Playground API
    # https://circuitpython.readthedocs.io/projects/circuitplayground/en/latest/api.html#adafruit-circuitplayground-bluefruit

# Anchorage Tech Solutions YouTubes & Code
    # https://www.youtube.com/channel/UCDuWq2wFqeVII1KC7grySRg?view_as=subscriber
    # https://github.com/AnchorageBot/YouTube

import adafruit_thermistor
import board
import neopixel
import time

pin = board.TEMPERATURE
resistor = 10000
resistance = 10000
nominal_temp = 25
b_coefficient = 3950

thermistor = adafruit_thermistor.Thermistor(
    pin, resistor, resistance, nominal_temp, b_coefficient
)

pixels = neopixel.NeoPixel(board.NEOPIXEL, 10, brightness = 0.25, auto_write=True)
                            # https://learn.adafruit.com/circuitpython-essentials/circuitpython-neopixel
                            # https://github.com/adafruit/Adafruit_CircuitPython_NeoPixel
                            # pixels is a variable that also functions as a list

RedColor = (255, 0, 0)      # List item - color choice
GreenColor = (0, 255, 0)
BlueColor = (0, 0, 255)
NoColor = (0, 0, 0)


# print the temperature in C and F to the serial console and show color stoplight 
while True:
    celsius = thermistor.temperature
    fahrenheit = (celsius * 9 / 5) + 32
    print("== Temperature ==\n{} *C\n{} *F\n".format(celsius, fahrenheit))
    
    if celsius >= 30:               # if this happens
        pixels.fill(RedColor)           # take this action
    elif celsius >= 25:             # if that happens
        pixels.fill(GreenColor)         # take that action
    else:                           # if this and that did not occur
        pixels.fill(BlueColor)          # perform action on this line
