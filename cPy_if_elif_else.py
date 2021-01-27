# This script uses a while True and a if - elif - else statement to light neopixels via buttons on the CPB with CircuitPython

# Coding concepts used in the script

    # while True means loop forever
        # The while statement takes an expression and executes the loop body.
            # while the expression evaluates to (boolean) "true". True always evaluates to
            # boolean "true" and thus executes the loop body indefinitely.
    #https://stackoverflow.com/questions/3754620/what-does-while-true-mean-in-python

    # if (an expression that is True or False)
        # indented statements are completed if true
    # elif (next expression that is True or False)
        # indented statements are completed if first expression is false but next expression is true 
    # Else: 
        # indented statements are completed if false

    # Dr Gallaugher's CPB Tutorials
        # https://www.youtube.com/playlist?list=PL9VJ9OpT-IPSsQUWqQcNrVJqy4LhBjPX2
        # https://www.youtube.com/watch?v=L1H_-ctldx4&list=PL9VJ9OpT-IPRo77roCKMzIh4q4Mu2dCBU

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
import digitalio

pixels = neopixel.NeoPixel(board.NEOPIXEL, 10, brightness = 0.25, auto_write=True)
                            # https://learn.adafruit.com/circuitpython-essentials/circuitpython-neopixel
                            # https://github.com/adafruit/Adafruit_CircuitPython_NeoPixel
                            # pixels is a variable that also functions as a list
                            

button_A = digitalio.DigitalInOut(board.BUTTON_A)
button_A.switch_to_input(pull=digitalio.Pull.DOWN)
button_B = digitalio.DigitalInOut(board.BUTTON_B)
button_B.switch_to_input(pull=digitalio.Pull.DOWN)

RedColor = (255, 0, 0)
GreenColor = (0, 255, 0)
BlueColor = (0,0, 255)
NoColor = (0,0,0)

colors = [RedColor, GreenColor, BlueColor, NoColor]

while True:
    if button_A.value:              # if this happens
        pixels.fill(RedColor)       # take this action
    elif button_B.value:            # if that happens
        pixels.fill(BlueColor)      # take that action
    else:                           # if this and that did not occur
        pixels.fill(NoColor)        # perform action
