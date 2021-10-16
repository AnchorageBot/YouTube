""" This script will demonstrate the FBS' onboard NeoPixel with RGB colors & BLERadio """

# Script Source/Engineering
  # https://learn.adafruit.com/adafruit-feather-sense/circuitpython-on-feather-sense
  # https://learn.adafruit.com/adafruit-feather-rp2040-pico/built-in-neopixel-led
  # https://www.youtube.com/profgallaugher
  # https://github.com/AnchorageBot/YouTube

# BOM
  # Feather Bluefruit Sense https://www.adafruit.com/product/4516
  # USB C to Micro B Cable https://www.adafruit.com/product/3878

# Software
  # Mu Python Editor https://codewith.mu
  # CircuitPython v 7.x https://circuitpython.org/board/feather_bluefruit_sense/
  # Libraries v 7.x bundle https://circuitpython.org/libraries
    # neopixel.mpy
    # adafruit_ble
    # adafruit_bluefruit_connect    

# Import libraries 
import time
import board
import neopixel
from adafruit_ble import BLERadio
from adafruit_ble.advertising.standard import ProvideServicesAdvertisement
from adafruit_ble.services.nordic import UARTService

# Setup neopixel 
pixel = neopixel.NeoPixel(board.NEOPIXEL, 1)
pixel.brightness = 0.3
RED = (255,0,0)
GREEN = (0,255,0)
BLUE = (0, 0, 255)
NAVY = (0, 0, 128)
BLACK = (0,0,0)
FIRSTBLINK = 0.1
NEXTBLINK = 0.5

def NeoPixelPatternGood2Go():
    pixel.fill(RED)
    time.sleep(FIRSTBLINK)
    pixel.fill(BLACK)
    time.sleep(NEXTBLINK)    
    pixel.fill(GREEN)
    time.sleep(FIRSTBLINK)
    pixel.fill(BLACK)
    time.sleep(NEXTBLINK)    
    pixel.fill(BLUE)
    time.sleep(FIRSTBLINK)
    pixel.fill(BLACK)  
  
def NeoPixelPatternBLE():
    pixel.fill(BLUE)
    time.sleep(FIRSTBLINK)
    pixel.fill(BLACK)
    time.sleep(NEXTBLINK)    
    pixel.fill(NAVY)
    time.sleep(FIRSTBLINK)
    pixel.fill(BLACK)
    time.sleep(NEXTBLINK)         

TIMESLEEP = 3

# Setup the BLE radio
ble = BLERadio()
uart_server = UARTService()
advertisement = ProvideServicesAdvertisement(uart_server)

# Define the neopixel data reporting functions
def NeoPixelSerial_Report():
    print("AK_Berry5 online ")
    print("\n")
    print("Neopixel flashes Red, Green, & Blue when not connected to BLE")
    print("Neopixel flashes Blue & Navy when connected to BLE")
    print("\n") 
    
def NeoPixelBLE_Report():  
    uart_server.write("{}\n".format("AK_Berry5 online "))
    uart_server.write("{}\n".format("Neopixel is flashing Blue & Navy"))

# Microcontroller task loop
while True:
    # Advertise via BLE
    ble.start_advertising(advertisement)    
    
    # While FBS is not connected to Bluefruit LE Connect
    while not ble.connected:
        NeoPixelPatternGood2Go()        
        NeoPixelSerial_Report()
        #pass
        time.sleep(TIMESLEEP)
    ble.stop_advertising()

    # While FBS is connected to Bluefruit LE Connect
    while ble.connected:
        NeoPixelPatternBLE()
        NeoPixelSerial_Report()
        NeoPixelBLE_Report()
        time.sleep(TIMESLEEP)
