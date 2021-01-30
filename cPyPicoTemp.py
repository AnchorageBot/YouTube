# This script uses the RPi Pico's Analog to Digital Convertor to print & plot on board temperature data

# Electronics concepts used in the script

    # Analog to Digital Converter
        # An analogue-to-digital converter (ADC) measures some analogue signal and encodes it as a digital number 
        # The ADC on RP2040 measures voltages
        # https://en.wikipedia.org/wiki/Analog-to-digital_converter
        # https://datasheets.raspberrypi.org/pico/raspberry-pi-pico-python-sdk.pdf

# Coding concepts used in the script

    # while True means loop forever
        # The while statement takes an expression and executes the loop body.
            # while the expression evaluates to (boolean) "true". True always evaluates to
            # boolean "true" and thus executes the loop body indefinitely.
        #https://stackoverflow.com/questions/3754620/what-does-while-true-mean-in-python
    
    # Variables are symbolic names that reference or point (pointer) to an object.
        # Once an object is assigned to a variable, you can refer to the object by that name.
        # https://realpython.com/python-variables/

# Materials
  # Raspberry Pi Pico https://www.adafruit.com/product/4864
  # USB A to Micro B data cable https://www.adafruit.com/product/592

# Software
    # Mu Python Editor 
        # https://codewith.mu 
    # CircuitPython .UF2 file for the RPi Pico
        # https://circuitpython.org/board/raspberry_pi_pico/

import microcontroller
import time                                             

sensor_temp = microcontroller.cpu[0].temperature             
fahrenheit = (sensor_temp * (9/5)) + 32

while True: 
    print(fahrenheit)                   # print temperature in the serial window of Mu Editor
    print(sensor_temp)
    print((fahrenheit, sensor_temp))    # plot temperature in the plotter window of Mu Editor
    time.sleep(4)
