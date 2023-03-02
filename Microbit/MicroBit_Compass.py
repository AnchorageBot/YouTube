# This script will show a compass heading on the Microbit (V1, Firmware 0249, Sept 2021)

# IDE (Integrated Development Environment)
  # https://codewith.mu
  
# Bill of Materials
  # Microbit v2 Go Kit
  # https://www.adafruit.com/product/4834

# Source Code
  # https://microbit.org/projects/make-it-code-it/compass-bearing/?editor=python
  
# Engineering Background  
  # https://core-electronics.com.au/tutorials/micropython-workshop-for-microbit.html
  # https://microbit-micropython.readthedocs.io/en/v1.0.1/tutorials/buttons.html
  # https://microbit-micropython.readthedocs.io/en/v1.0.1/tutorials/direction.html  

from microbit import *
compass.calibrate()

while True:
    if button_a.was_pressed():
        display.scroll(str(compass.heading()))
