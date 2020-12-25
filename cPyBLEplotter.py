# CircuitPython Bluefruit LE Connect Plotter Example

# Adafruit bluetooth plotter tutorial
  # https://learn.adafruit.com/adafruit-circuit-playground-bluefruit/playground-bluetooth-plotter
  
# Dr Gallaugher's CPB Tutorials
    # https://www.youtube.com/playlist?list=PL9VJ9OpT-IPSsQUWqQcNrVJqy4LhBjPX2

# Materials
  # Circuit Playground Bluefruit https://www.adafruit.com/product/4333
  # USB A to Micro B data cable https://www.adafruit.com/product/592  

import time
import board
import analogio
import adafruit_thermistor
from adafruit_ble import BLERadio
from adafruit_ble.advertising.standard import ProvideServicesAdvertisement
from adafruit_ble.services.nordic import UARTService

ble = BLERadio()
uart_server = UARTService()
advertisement = ProvideServicesAdvertisement(uart_server)

thermistor = adafruit_thermistor.Thermistor(board.TEMPERATURE, 10000, 10000, 25, 3950)
light = analogio.AnalogIn(board.LIGHT)


def scale(value):
    """Scale the light sensor values from 0-65535 (AnalogIn range)
    to 0-50 (arbitrarily chosen to plot well with temperature)"""
    return value / 65535 * 50


while True:
    # Advertise when not connected.
    ble.start_advertising(advertisement)
    while not ble.connected:
        pass
    ble.stop_advertising()

    while ble.connected:
        print((scale(light.value), thermistor.temperature))
        uart_server.write("{},{}\n".format(scale(light.value), thermistor.temperature))
        time.sleep(0.1)
