""" This script will read/share data from a capacitive soil sensor using the FBS' serial, BLE, and onboard neopixel"""

# Script Source/Engineering
  # https://learn.adafruit.com/adafruit-stemma-soil-sensor-i2c-capacitive-moisture-sensor/python-circuitpython-test
  # https://www.youtube.com/profgallaugher
  # https://github.com/AnchorageBot/YouTube

# Hardware BOM (Bill of Materials)
  # Soil Sensor https://www.adafruit.com/product/4026
  # JST Cable https://www.adafruit.com/product/3955
  # Feather Bluefruit Sense https://www.adafruit.com/product/4516
  # USB C to Micro B Cable https://www.adafruit.com/product/3878

# Software
  # Mu Python Editor https://codewith.mu
  # CircuitPython v 6.3.0 https://circuitpython.org/board/feather_bluefruit_sense/
  # Libraries v 6.x bundle https://circuitpython.org/libraries
    # adafruit_seesaw.mpy
    # adafruit_bus_device
    # adafruit_ble
    # adafruit_bluefruit_connect

# Wiring Pattern for Soil Sensor to FBS
  # Red   - 3.3V
  # Black - Ground
  # White - SCA
  # Green - SCL

# Import libraries
import time
import board
from adafruit_seesaw.seesaw import Seesaw
from adafruit_ble import BLERadio
from adafruit_ble.advertising.standard import ProvideServicesAdvertisement
from adafruit_ble.services.nordic import UARTService
import neopixel

# Setup I2C
i2c_bus = board.I2C()

# Setup Soil Sensor
ss = Seesaw(i2c_bus, addr=0x36)

# Setup the BLE radio
ble = BLERadio()
uart_server = UARTService()
advertisement = ProvideServicesAdvertisement(uart_server)

# Setup the onboard neopixel
pixel = neopixel.NeoPixel(board.NEOPIXEL, 1)
pixel.brightness = 0.1
BLUE = (0, 0, 255)
NAVY = (0,0,128)
SHORTBLINK = 0.25
LONGBLINK = 0.5

def NeoPixelPattern():
    pixel.fill(BLUE)
    time.sleep(SHORTBLINK)
    pixel.fill(NAVY)
    time.sleep(LONGBLINK)
    pixel.fill(BLUE)
    time.sleep(SHORTBLINK)

while True:
    # When not connected via BLERadio
    ble.start_advertising(advertisement)
    while not ble.connected:
        Stemp = ss.get_temp()                                      # read soil temperature from the temperature sensor
        Smoist = ss.moisture_read()                                # read soil moisture level through capacitive touch pad

        # share data via serial
        print(("temp: " + str(Stemp) + "  moisture: " + str(Smoist)))
        time.sleep(1)
    ble.stop_advertising()

    # When connected via BLERadio
    while ble.connected:
      Stemp = ss.get_temp()                                      # read soil temperature from the temperature sensor
      Smoist = ss.moisture_read()                                # read soil moisture level through capacitive touch pad

      # share data via serial, and BLERadio (UART & Plotter)
      x = Stemp
      y = Smoist
      print("Broadcasting via BLEradio")
      print(("soil temp: " + str(x) + "  soil moisture: " + str(y)))
      uart_server.write("{},{}\n".format("soil temp: " + str(Stemp), " soil moisture: " + str(Smoist)))
      NeoPixelPattern()
      time.sleep(1)
