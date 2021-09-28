# This script will use the Microbit LEDs as a light sensor and transmit an alert (V1, Firmware 0249, Sept 2021)

# IDE (Integrated Development Environment)
  # https://codewith.mu
  
# Bill of Materials
  # Microbit v2 Go Kit
  # https://www.adafruit.com/product/4834

# Source code
  # https://microbit.org/projects/make-it-code-it/light-alarm/?editor=python

# Engineering background
  # https://lancaster-university.github.io/microbit-docs/extras/light-sensing/
  # https://core-electronics.com.au/tutorials/micropython-workshop-for-microbit.html
  # https://microbit-micropython.readthedocs.io/en/v1.0.1/tutorials/buttons.html
  # https://microbit-micropython.readthedocs.io/en/v1.0.1/tutorials/radio.html  

from microbit import *
import radio
radio.config(group=5)
radio.on()

while True:
    if button_a.was_pressed():
        display.scroll(display.read_light_level())
    if display.read_light_level() > 50:
        radio.send('lights on')
    else:
        radio.send('lights off')
    sleep(10000)
