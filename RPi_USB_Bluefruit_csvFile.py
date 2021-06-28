# This script connects a RPi to a Arduino/Adafruit and
# saves sensor data to a csv file

import serial
import datetime

CSVfileName = "BerryOneData.csv"

ser = serial.Serial('/dev/ttyACM0', 9600)

while True:
  getArduinoData = str(ser.readline())
  getCurrent_time = str(datetime.datetime.now())
  print(getArduinoData, getCurrent_time)
  file = open(CSVfileName, "a")
  file.write(getArduinoData + getCurrent_time + "\n")
  
file.close()  
