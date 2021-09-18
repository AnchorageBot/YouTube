"""Sensor demo for Adafruit Feather Bluefruit Sense. Serial prints data from each of the sensors."""

# Script Source/Engineering
  # https://learn.adafruit.com/adafruit-feather-sense/circuitpython-sense-demo
  # https://www.youtube.com/profgallaugher
  # https://github.com/AnchorageBot/YouTube

# Hardware BOM (Bill of Materials)
  # Feather Bluefruit Sense https://www.adafruit.com/product/4516
  # USB C to Micro B Cable https://www.adafruit.com/product/3878

# Software
  # Mu Python Editor https://codewith.mu
  # CircuitPython v 6.3.0 https://circuitpython.org/board/feather_bluefruit_sense/
  # Libraries v 6.x bundle https://circuitpython.org/libraries
    # adafruit_apds9960
    # adafruit_bmp280.mpy
    # adafruit_bus_device
    # adafruit_lis3mdl.mpy
    # adafruit_lsm6ds
    # adafruit_register
    # adafruit_sht31d.mpy
    # neopixel.mpy

import time
import array
import math
import board
import audiobusio
import adafruit_apds9960.apds9960
import adafruit_bmp280
import adafruit_lis3mdl
import adafruit_lsm6ds.lsm6ds33
import adafruit_sht31d

i2c = board.I2C()

apds9960 = adafruit_apds9960.apds9960.APDS9960(i2c)
bmp280 = adafruit_bmp280.Adafruit_BMP280_I2C(i2c)
lis3mdl = adafruit_lis3mdl.LIS3MDL(i2c)
lsm6ds33 = adafruit_lsm6ds.lsm6ds33.LSM6DS33(i2c)
sht31d = adafruit_sht31d.SHT31D(i2c)
microphone = audiobusio.PDMIn(board.MICROPHONE_CLOCK, board.MICROPHONE_DATA,
                              sample_rate=16000, bit_depth=16)

def normalized_rms(values):
    minbuf = int(sum(values) / len(values))
    return int(math.sqrt(sum(float(sample - minbuf) *
                             (sample - minbuf) for sample in values) / len(values)))

apds9960.enable_proximity = True
apds9960.enable_color = True

# Set this to sea level pressure in hectoPascals at your location for accurate altitude reading.
bmp280.sea_level_pressure = 1013.25

while True:
    samples = array.array('H', [0] * 160)
    microphone.record(samples, len(samples))

    print("\nFeather Sense Sensor Demo")
    print("---------------------------------------------")
    print("Proximity:", apds9960.proximity)
    print("Red: {}, Green: {}, Blue: {}, Clear: {}".format(*apds9960.color_data))
    print("Temperature: {:.1f} C".format(bmp280.temperature))
    print("Barometric pressure:", bmp280.pressure)
    print("Altitude: {:.1f} m".format(bmp280.altitude))
    print("Magnetic: {:.3f} {:.3f} {:.3f} uTesla".format(*lis3mdl.magnetic))
    print("Acceleration: {:.2f} {:.2f} {:.2f} m/s^2".format(*lsm6ds33.acceleration))
    print("Gyro: {:.2f} {:.2f} {:.2f} dps".format(*lsm6ds33.gyro))
    print("Humidity: {:.1f} %".format(sht31d.relative_humidity))
    print("Sound level:", normalized_rms(samples))
    time.sleep(9)
