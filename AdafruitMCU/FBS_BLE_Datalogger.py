# This script will read/share data from soil & air sensors using the FBS' serial, BLE, and onboard neopixel

# Script Source/Engineering
  # https://learn.adafruit.com/adafruit-stemma-soil-sensor-i2c-capacitive-moisture-sensor/python-circuitpython-test
  # https://learn.adafruit.com/adafruit-feather-sense
  # https://www.youtube.com/profgallaugher
  # https://github.com/AnchorageBot/YouTube

# Hardware Bill of Materials
  # Soil Sensor https://www.adafruit.com/product/4026
  # JST Cable https://www.adafruit.com/product/3955
  # Feather Bluefruit Sense https://www.adafruit.com/product/4516
  # USB C to Micro B Cable https://www.adafruit.com/product/3878
  # JST 2 Pin jumper cable https://www.adafruit.com/product/4714
  # Universal USB/DC/Lithium Charger https://www.adafruit.com/product/4755
  # 3.5mm / 1.1mm to 5.5mm / 2.1mm DC Jack Adapter https://www.adafruit.com/product/4287
  # Medium Solar panel - 6V 2W  https://www.adafruit.com/product/200
  # Round Solar Panel Skill Badge - 5V / 40mA https://www.adafruit.com/product/700
  # Lithium Ion Polymer Battery - 3.7v 500mAh https://www.adafruit.com/product/1578
  # Flanged Weatherproof Enclosure With PG-7 Cable Glands https://www.adafruit.com/product/3931

# Software
  # Mu Python Editor https://codewith.mu
  # CircuitPython v 7.0 https://circuitpython.org/board/feather_bluefruit_sense/
  # Libraries v 7.x bundle https://circuitpython.org/libraries
    # adafruit_ble
    # adafruit_ble_adafruit
    # adafruit_bluefruit_connect
    # adafruit_bus_device
    # adafruit_register
    # adafruit_apds9960
    # adafruit_lsm6ds
    # adafruit_seesaw.mpy
    # adafruit_bmp280.mpy
    # adafruit_lis3mdl.mpy
    # adafruit_sht31d.mpy
    # neopixel.mpy

# Wiring Pattern for Soil Sensor to FBS
  # Red   - 3.3V
  # Black - Ground
  # White - SCA
  # Green - SCL
  
 # URL for RPi_GetMCUdata.py script file to save MCU sensor data to a RPi
    # Run the RPi_GetMCUdata.py script on the RPi using the Mu IDE
    # https://github.com/AnchorageBot/YouTube/blob/master/RPi_getMCUdata.py

# Import libraries
import time
import board
import busio
from adafruit_ble import BLERadio
from adafruit_ble.advertising.standard import ProvideServicesAdvertisement
from adafruit_ble.services.nordic import UARTService
from adafruit_seesaw.seesaw import Seesaw
import adafruit_bmp280
import adafruit_sht31d
import adafruit_apds9960.apds9960
import neopixel

# Setup the BLE radio
ble = BLERadio()
uart_server = UARTService()
advertisement = ProvideServicesAdvertisement(uart_server)

# Setup I2C
i2c = board.I2C()
#i2cBUS = busio.I2C(board.SCL, board.SDA)
#i2c_bus = board.I2C()

# Setup soil sensors
ss = Seesaw(i2c, addr=0x36)

# Soil sensors global variables
soil_temp = ss.get_temp()
soil_moist = ss.moisture_read()

# Setup board (air) sensors
bmp280 = adafruit_bmp280.Adafruit_BMP280_I2C(i2c)
bmp280.sea_level_pressure = 1013.25                 # Set this to sea level pressure in hectoPascals at your location
sht31d = adafruit_sht31d.SHT31D(i2c)
RGBC = adafruit_apds9960.apds9960.APDS9960(i2c)
RGBC.enable_color = True
R,G,B,C = RGBC.color_data

# Setup the onboard neopixel, associated global variables
pixel = neopixel.NeoPixel(board.NEOPIXEL, 1)
pixel.brightness = 0.1

RED = (255,0,0)
GREEN = (0,255,0)
BLUE = (0, 0, 255)
BLACK = (0,0,0)
FIRSTBLINK = 0.5
NEXTBLINK = 0.75
TIMESLEEP = 2

# Neopixel color pattern function
def NeoPixelPattern(COLOR):
    pixel.fill(COLOR)
    time.sleep(FIRSTBLINK)
    pixel.fill(BLACK)
    time.sleep(NEXTBLINK)

# Soil sensor color pattern function
def SoilSensor_Blink():
    if soil_moist <= 800:                           # 600 - 800 (soil), 570 (water), 320 (air)
        # blink good to go neopixel pattern
        NeoPixelPattern(GREEN)
    else:
        # blink water plant neopixel pattern
        NeoPixelPattern(RED)

# Sensor data serial report function
def SensorSerial_Report():
    print("BerryFour")
    print("air temp: %0.1f C" % bmp280.temperature)
    print("air pressure: %0.1f hpa" % bmp280.pressure)
    print("altitude = %0.2f m" % bmp280.altitude)
    print("air humidity: {0}%".format(sht31d.relative_humidity))
    print("RGBC color {0} {1} {2} {3}".format(R,G,B,C))
    print("soil temp: C " + str(soil_temp))
    print("soil moisture:  " + str(soil_moist))
    print("\n")
    time.sleep(TIMESLEEP)

    # uncomment blink Serial neopixel pattern to check serial connection
    #NeoPixelPattern(GREEN)

def SensorBLE_Report():
    uart_server.write("{}\n".format("BerryFour bfe4"))
    uart_server.write("{}\n".format("air temp: %0.1f C" % bmp280.temperature))
    uart_server.write("{}\n".format("air pressure: %0.1f hpa" % bmp280.pressure))
    uart_server.write("{}\n".format("altitude = %0.2f m" % bmp280.altitude))
    uart_server.write("{}\n".format("air humidity: {0}%".format(sht31d.relative_humidity)))
    uart_server.write("{}\n".format("soil temp: C " + str(soil_temp)))
    uart_server.write("{}\n".format("soil moisture: " + str(soil_moist)))
    uart_server.write("{}\n".format(""))
    time.sleep(TIMESLEEP)

    # blink BLE Radio neopixel pattern
    NeoPixelPattern(BLUE)

# Microcontroller Task Loop

while True:

    # When not connected via BLERadio
    ble.start_advertising(advertisement)
    while not ble.connected:
        # share sensor data via serial
        SensorSerial_Report()

        # Blink soil sensor neopixel pattern
        SoilSensor_Blink()

    ble.stop_advertising()

    # When connected via BLERadio
    while ble.connected:
        # share sensor data via BLEradio
        SensorBLE_Report()
