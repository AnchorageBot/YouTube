# This script uses a RPi Pico & BME280 to log temp, pressure, & humidity

# Ensure that the following CircuitPython Libraries are loaded on the Pico
    # adafruit_bme280.mpy
    # adafruit_bus_device

# Software
    # https://codewith.mu
    # https://circuitpython.org/board/raspberry_pi_pico/
    # https://circuitpython.org/libraries
    # https://github.com/adafruit/Adafruit_CircuitPython_BME280
    # https://github.com/adafruit/circuitpython/issues/4121

# Materials
    # Raspberry Pi Pico https://www.adafruit.com/product/4864
    # USB A to Micro B data cable https://www.adafruit.com/product/592
    # Sparkfun BME 280 https://www.sparkfun.com/products/13676

# Wiring
    # GND - Sensor - 4 pin side, top pin - GND - RPi Pico - away from reset, pin #3
    # 3.3 - Sensor - 4 pin side, pin # 2 - 3.3 - RPi Pico - away from reset, pin #5
    # SDA - Sensor - 4 pin side, pin # 3 - SDA - RPi Pico - close to reset, pin #1
    # SCL - Sensor - 4 pin side, pin # 4 - SCL - RPi Pico - close to reset, pin #2

import microcontroller
import board
import digitalio
import busio
import time
import adafruit_bme280

# Create library object using our Bus I2C port
#i2c = busio.I2C(board.SCL, board.SDA)
i2c = busio.I2C(board.GP1, board.GP0)
bme280 = adafruit_bme280.Adafruit_BME280_I2C(i2c)
#or with other sensor address
#bme280 = adafruit_bme280.Adafruit_BME280_I2C(i2c, address=0x76)

# OR create library object using our Bus SPI port
#spi = busio.SPI(board.SCK, board.MOSI, board.MISO)
#bme_cs = digitalio.DigitalInOut(board.D10)
#bme280 = adafruit_bme280.Adafruit_BME280_SPI(spi, bme_cs)

# change this to match the location's pressure (hPa) at sea level
bme280.sea_level_pressure = 1013.25

while True:
    print("\nTemperature: %0.1f C" % bme280.temperature)
    print("Humidity: %0.1f %%" % bme280.relative_humidity)
    print("Pressure: %0.1f hPa" % bme280.pressure)
    print("Altitude = %0.2f meters" % bme280.altitude)
    print((bme280.temperature,bme280.relative_humidity))
    time.sleep(2)
