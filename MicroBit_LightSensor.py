# This script will use the Microbit LEDs as a light sensor (V1, Firmware 0249, Sept 2021)

# IDE (Integrated Development Environment)
  # https://codewith.mu
  
# Bill of Materials
  # Microbit v2 Go Kit
  # https://www.adafruit.com/product/4834

# Source code
  # https://microbit.org/projects/make-it-code-it/sunlight-sensor/?editor=python#step-2:-code-it
  
# Engineering background
  # https://lancaster-university.github.io/microbit-docs/extras/light-sensing/
  # https://core-electronics.com.au/tutorials/micropython-workshop-for-microbit.html
  # https://microbit-micropython.readthedocs.io/en/v1.0.1/tutorials/images.html  

from microbit import *

while True:
    if display.read_light_level() > 25:
        display.show(Image(
        "90909:"
        "09990:"
        "99999:"
        "09990:"
        "90909"))
    else:
        display.clear()
