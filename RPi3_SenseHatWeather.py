#  Python v 3.4.2
#  This program will check air temperature, pressure, and humidity
#
#  Materials List
#
#    RPi 3B+ https://www.raspberrypi.org/products/raspberry-pi-3-model-b-plus/
#    SenseHAT https://www.raspberrypi.org/products/sense-hat/
#
#  ATS
#    https://github.com/AnchorageBot
#
#  Libraries
from sense_hat import SenseHat
#
#  Setup
sense = SenseHat()
sense.set_rotation(270)
blue = (0,0,255)
#
#  Main Loop
while True:
    t = sense.get_temperature()
    p = sense.get_pressure()
    h = sense.get_humidity()
    
    t = round(t, 1)
    p = round(p, 1)
    h = round(h, 1)
    
    msg = "Temp = {0}, Press = {1}, Humidity = {2}".format(t.p.h)
    
    sense.show_message(msg, scroll_speed=0.03, text_colour=blue)
