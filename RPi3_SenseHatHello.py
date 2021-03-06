#  Python v 3.4.2
#  This program will show "Hello World" on the Sense Hat LED
#
#  Materials List
#    RPi 3B+ https://www.raspberrypi.org/products/raspberry-pi-3-model-b-plus/
#    SenseHAT https://www.raspberrypi.org/products/sense-hat/
#
# ATS
# https://github.com/AnchorageBot


#  Libraries
from sense_hat import SenseHat
#
#  Setup
sense = SenseHat()
sense.set_rotation(270)
red = (255,0,0)
green = (0,255,0)
blue = (0,0,255)
yellow = (255,255,0)
#
#  Main Loop
sense.show_message("Hello World")
sense.show_message("Hello World", scroll_speed=0.05, text_colour=red)
sense.show_message("Hello World", scroll_speed=0.04, text_colour=blue, back_colour=yellow)

While True:
    sense.show_message("Hello World", scroll_speed=0.03, text_colour=green)
