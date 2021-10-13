""" This script reads/shares the CPB's Temp & Light Sensor Data via BLE, serial, and neopixels """

# Script origins
  # Adafruit CPB Tutorial
    # https://learn.adafruit.com/adafruit-circuit-playground-bluefruit
  # Prof G's CPB Tutorials
    # https://www.youtube.com/profgallaugher
  # ATS
    # https://github.com/AnchorageBot/YouTube

# Software
    # Mu Python Editor https://codewith.mu
    # CircuitPython for CPB https://circuitpython.org
    # CircuitPython Libraries https://circuitpython.org/libraries
    # Copy/Paste the following CircuitPython Libraries into the CPB lib folder
      # adafruit_ble
      # adafruit_bluefruit_connect
      # adafruit_bus_device
      # adafruit_circuitplayground
      # adafruit_gizmo
      # adafruit_hid
      # adafruit_lis3dh.mpy
      # adafruit_thermistor.mpy
      # neopixel.mpy
    # Bluefruit LE Connect for iPhone/Android https://learn.adafruit.com/bluefruit-le-connect

# Bill of Materials - Hardware
  #  CPB https://www.adafruit.com/product/4333
  #  USB Cable A to Micro B https://www.adafruit.com/product/592
  #  Desktop or laptop
  #  Cellphone

# Import required libraries for light sensor, thermistor, BLE radio, and neopixels
import time
import board
import analogio
import adafruit_thermistor
from adafruit_ble import BLERadio
from adafruit_ble.advertising.standard import ProvideServicesAdvertisement
from adafruit_ble.services.nordic import UARTService
import neopixel

# Setup the BLE radio
ble = BLERadio()
uart_server = UARTService()
advertisement = ProvideServicesAdvertisement(uart_server)
# Give your CPB a unique name between the quotes below
advertisement.complete_name = "AK_CPB"

# Setup the thermistor and light sensor
tmp = adafruit_thermistor.Thermistor(board.TEMPERATURE, 10000, 10000, 25, 3950)
light = analogio.AnalogIn(board.LIGHT)

# Setup neopixels
BLUE = (0, 0, 255)
NAVY = (0,0,128)
BLACK = (0, 0, 0)
leadColor = BLUE
chaseColor = NAVY
pauseTime = 0.1
pxl = neopixel.NeoPixel(board.NEOPIXEL, 10, brightness =0.1, auto_write = True)

# Neopixel pattern for BLE connection
def colorChaser():
    pxl.fill(BLACK)
    for i in range(0, len(pxl), 2):
        pxl[i] = leadColor
        time.sleep(pauseTime)
        pxl[i] = BLACK
        pxl[i+1] = chaseColor
        time.sleep(pauseTime)
        pxl[i+1] = BLACK

# Define the sensor data reporting functions
def SensorSerial_Report():
        print("CPB MCU")
        print("air temp: " + str(tmp.temperature) + "  light intensity: " + str(light.value))
        print("\n")

def SensorBLE_Report():    
    uart_server.write("{}\n".format("CPB MCU ")) 
    uart_server.write("{},{}\n".format(" air temp " + str(tmp.temperature), " light intensity " + str(light.value)))    
    #uart_server.write("{}\n {},{}\n".format("CPB MCU ", "air temp: " + str(tmp.temperature),"light intensity: " + str(light.value)))

TIMESLEEP = 2

# Microcontroller Task Loop
while True:
    # Advertise via BLE
    ble.start_advertising(advertisement)

    # While CPB is not connected to Bluefruit LE Connect
    while not ble.connected:
        SensorSerial_Report()
        pass
        time.sleep(TIMESLEEP)
    ble.stop_advertising()

    # While CPB is connected to Bluefruit LE Connect
    while ble.connected:
        colorChaser()
        SensorSerial_Report()
        SensorBLE_Report()
        time.sleep(TIMESLEEP)
