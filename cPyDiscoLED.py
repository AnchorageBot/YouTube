# Make a neopixel disco using the Circuit Playground Bluefruit and Circuit Python

# Ensure CIRCUITPY Drive lib folder has the following items
    # adafruit_ble
    # adafruit_bluefruit_connect
    # adafruit_bus_device
    # adafruit_circuitplayground
    # adafruit_gizmo
    # adafruit_hid
    # adafruit_lis3dh.mpy
    # adafruit_thermistor.mpy
    # neopixel.mpy

import time
from adafruit_circuitplayground import cp
#from adafruit_circuitplayground.bluefruit import cpb

while True:
  cp.pixels.fill((255,0,0))
  #cpb.pixels.fill((255,0,0))
  time.sleep(0.2)
  cp.pixels.fill((255,128,0))
  #cpb.pixels.fill((255,128,0))
  time.sleep(0.2)
  cp.pixels.fill((255,255,0))
  #cpb.pixels.fill((255,255,0))
  time.sleep(0.2)
  cp.pixels.fill((255,255,128))
  #cpb.pixels.fill((255,255,128))
  time.sleep(0.2)
  cp.pixels.fill((255,255,255))
  #cpb.pixels.fill((255,255,255))
  time.sleep(0.2)
