# Read/Print Thermistor Values via Serial and Blink LED using a CircuitPlayground Bluefruit and Circuit Python

# Dr Gallaugher's CPB Tutorials
    # https://www.youtube.com/playlist?list=PL9VJ9OpT-IPSsQUWqQcNrVJqy4LhBjPX2

# Adafruit CPB temperature tutorial
  # https://learn.adafruit.com/adafruit-circuit-playground-bluefruit/playground-temperature
  
# Adafruit CircuitPython libraries
    # https://learn.adafruit.com/welcome-to-circuitpython/circuitpython-libraries
    # https://circuitpython.org/libraries
    # https://circuitpython.readthedocs.io/projects/thermistor/en/latest/
    # https://circuitpython.readthedocs.io/projects/thermistor/en/latest/api.html#implementation-notes
   
# Materials
  # Circuit Playground Bluefruit https://www.adafruit.com/product/4333
  # USB A to Micro B data cable https://www.adafruit.com/product/592

# Software
    # Mu Python Editor https://codewith.mu

import time
import board
import adafruit_thermistor
import digitalio

pin = board.TEMPERATURE
resistor = 10000
resistance = 10000
nominal_temp = 25
b_coefficient = 3950

thermistor = adafruit_thermistor.Thermistor(
    pin, resistor, resistance, nominal_temp, b_coefficient
)

led = digitalio.DigitalInOut(board.D13)
led.direction = digitalio.Direction.OUTPUT

# print the temperature in C and F to the serial console every second
while True:
    celsius = thermistor.temperature
    fahrenheit = (celsius * 9 / 5) + 32
    print("== Temperature ==\n{} *C\n{} *F\n".format(celsius, fahrenheit))
    #time.sleep(1)
    led.value = True
    time.sleep(0.5)
    led.value = False
    time.sleep(0.5)
