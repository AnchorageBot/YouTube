""" This script will read/share data from soil & air sensors using the FBS' serial, BLE, and onboard neopixel"""

# Script Source/Engineering
  # https://learn.adafruit.com/adafruit-stemma-soil-sensor-i2c-capacitive-moisture-sensor/python-circuitpython-test
  # https://www.youtube.com/profgallaugher
  # https://github.com/AnchorageBot/YouTube

# Hardware Bill of Materials
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
    # adafruit_bmp280.mpy
    # neopixel.mpy       

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
import adafruit_bmp280
import neopixel

# Setup the BLE radio
ble = BLERadio()
uart_server = UARTService()
advertisement = ProvideServicesAdvertisement(uart_server)

# Setup I2C
i2c = board.I2C()
i2c_bus = board.I2C()

# Setup Soil Sensor
ss = Seesaw(i2c_bus, addr=0x36)

# Setup atmospheric sensors
bmp280 = adafruit_bmp280.Adafruit_BMP280_I2C(i2c)
bmp280.sea_level_pressure = 1013.25         # Set this to sea level pressure in hectoPascals at your location

# Setup the onboard neopixel & define neopixel blink pattern functions
pixel = neopixel.NeoPixel(board.NEOPIXEL, 1)
pixel.brightness = 0.1
RED = (255,0,0)
GREEN = (0,255,0)
BLUE = (0, 0, 255)
BLACK = (0,0,0)
FIRSTBLINK = 0.5
NEXTBLINK = 0.75

def NeoPixelPatternGood2Go():
    pixel.fill(GREEN)
    time.sleep(FIRSTBLINK)
    pixel.fill(BLACK)
    time.sleep(NEXTBLINK)

def NeoPixelPatternWaterPlant():
    pixel.fill(RED)
    time.sleep(FIRSTBLINK)
    pixel.fill(BLACK)
    time.sleep(NEXTBLINK)

def NeoPixelPatternBLE():
    pixel.fill(BLUE)
    time.sleep(FIRSTBLINK)
    pixel.fill(BLACK)
    time.sleep(NEXTBLINK)

TIMESLEEP = 2

# Define the sensor data reporting functions
def SensorSerial_Report():
        print("BerryFour MCU")
        print(("soil temp: " + str(Stemp) + "  soil moisture: " + str(Smoist)))
        print("\n")
        print("air temp: {:.1f} C".format(bmp280.temperature))
        print("air pressure:", bmp280.pressure)
        print("altitude: {:.1f} m".format(bmp280.altitude))
        print("\n")

def SensorBLE_Report():
    uart_server.write("{}\n {},{}\n".format("BerryFourMCU", "soil temp: " + str(Stemp), " soil moist: " + str(Smoist)))
    uart_server.write("{},{}\n".format("air temp: " + str(bmp280.temperature), " air pressure: " + str(bmp280.pressure)))

# Microcontroller Task Loop

while True:

    # When not connected via BLERadio
    ble.start_advertising(advertisement)
    while not ble.connected:
        Stemp = ss.get_temp()           # read soil temperature from the temperature sensor
        Smoist = ss.moisture_read()     # read soil moisture level through capacitive touch pad
        if Smoist >= 800:
          # share data via serial
          SensorSerial_Report()

          # blink good to go neopixel pattern
          NeoPixelPatternGood2Go()
          time.sleep(TIMESLEEP)

        else:
          # share data via serial
          SensorSerial_Report()

          # blink water plant neopixel pattern
          NeoPixelPatternWaterPlant()
          time.sleep(TIMESLEEP)

    ble.stop_advertising()

    # When connected via BLERadio
    while ble.connected:
      Stemp = ss.get_temp()             # read soil temperature from the temperature sensor
      Smoist = ss.moisture_read()       # read soil moisture level through capacitive touch pad

      # share data via serial and BLEradio
      SensorSerial_Report()
      SensorBLE_Report()

      # blink BLE Radio neopixel pattern
      NeoPixelPatternBLE()
      time.sleep(TIMESLEEP)
