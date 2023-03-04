# This script will display temperature on the Microbit & transmit via BLE (V1, Firmware 0249, Sept 2021)

# IDE (Integrated Development Environment)
  # https://codewith.mu
  
# Bill of Materials
  # Microbit v2 Go Kit
  # https://www.adafruit.com/product/4834

# Source code
  # https://microbit.org/projects/make-it-code-it/thermometer/?editor=python
  # https://microbit.org/projects/make-it-code-it/max-min-thermometer/?editor=python
  # https://github.com/AnchorageBot
  
# Engineering background  
  # https://lancaster-university.github.io/microbit-docs/ble/temperature-service/
  # https://lancaster-university.github.io/microbit-docs/ubit/thermometer/
  # https://microbit-micropython.readthedocs.io/en/v1.0.1/tutorials/radio.html
  # https://microbit-micropython.readthedocs.io/en/v1.0.1/filesystem.html  
  # https://core-electronics.com.au/tutorials/micropython-workshop-for-microbit.html  
  
from microbit import *
import radio
radio.config(group=23)
radio.on()

while True:
    if button_a.was_pressed():
        display.scroll(temperature())
        radio.send(str(temperature()))
    else:
        radio.send('lights off')
    sleep(10000)
