# This code will provide serial communication between a RPi and a Bluefruit Sense
# This code is loaded on the RPi while this script is loaded on the Bluefruit Sense
    # https://github.com/AnchorageBot/YouTube/blob/master/FBS_USB_RPi.ino

# Software and materials list
    # Programming the RPi, 2nd Ed, by Simon Monk http://simonmonk.org/programming-raspberry-pi-ed2/
    # RPi 3B+ or RPi Zero https://www.adafruit.com/product/3400 
    # USB A to Micro B Cable https://www.adafruit.com/product/592 
    # Adafruit Bluefruit Sense https://www.adafruit.com/product/4516

# Connect RPi and Bluefruit via USB cable
# Code is run in the Python 3 Shell on the RPi


# Start RPi in listening mode (Bluefruit is in talking mode)
import serial
ser = serial.Serial('/dev/ttyACM0', 9600)
while True:
    print(ser.readline())
    
# Interupt Bluefruit using ctrl-c on the RPi keyboard then load & run code to blink Bluefruit LED 5X
# Puts RPi in talking mode (Bluefruit is in listening mode)
ser.write('5'.encode())
