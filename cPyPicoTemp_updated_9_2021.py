"""This updated (Sept 2021) script will print the RPi Pico on-board temperature sensor data"""

# Engineering
  # Adafruit
    # https://learn.adafruit.com/getting-started-with-raspberry-pi-pico-circuitpython/overview
  # ATS 
    # https://github.com/AnchorageBot/YouTube

# Hardware BOM
  # RPi Pico https://www.adafruit.com/product/4864
  # USB C to Micro B Cable https://www.adafruit.com/product/3879
  
# Software
  # Mu Editor
    # https://codewith.mu
  # CicruitPython for RPi Pico v 6.3
    # https://circuitpython.org/board/raspberry_pi_pico/
  # CicruitPython Libraries v 6.x
    # https://circuitpython.org/libraries
    
import microcontroller
import time

while True:
  print("On-board RPi Pico CPU Temp in C: " + str(microcontroller.cpu.temperature))
  time.sleep(2)   
