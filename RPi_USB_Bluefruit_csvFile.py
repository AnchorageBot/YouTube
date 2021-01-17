# This script connects a RPi to a Arduino/Adafruit and
# saves sensor data to a csv file

import serial

CSVfileName = "BerryOneData.csv"
dataLine = 0
dataLinesSampled = 10

ser = serial.Serial('/dev/ttyACM0', 9600)

#while dataLine <= dataLinesSampled:
while True:
  getArduinoData = str(ser.readline())
  print(getArduinoData)
  file = open(CSVfileName, "a")
  file.write(getArduinoData + "\\n")
  #dataLine = dataLine + 1
  
file.close()  
