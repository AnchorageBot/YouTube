# This script connects a RPi to a MCU (Microcontroller) and saves sensor data to a csv file
    # csv file will be located in the same folder that this script resides in
  
# RPi Zero hardware kit
  # https://www.adafruit.com/product/3410
    
# IDE: Mu version 1.0.3, https://codewith.mu
  
# Source code references
  # https://docs.python.org/3/index.html
    # https://docs.python.org/3/tutorial/inputoutput.html#reading-and-writing-files
    # https://docs.python.org/3/library/datetime.html
  # https://pyserial.readthedocs.io/en/latest/
    # https://pyserial.readthedocs.io/en/latest/shortintro.html#opening-serial-ports
  
# Modified by ATS, April 2022

import serial
import datetime

CSVfileName = "AK_CLUE_1.csv"

openCommoLine = serial.Serial('/dev/ttyACM0', 9600)

while True:
    getMCUdata = str(openCommoLine.readline())
    getTimeNow = str(datetime.datetime.now())
    print(getMCUdata, getTimeNow)
    file = open(CSVfileName, "a")
    file.write(getMCUdata + getTimeNow + "\n")

file.close()
