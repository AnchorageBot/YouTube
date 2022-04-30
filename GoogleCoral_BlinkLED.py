# This script will blink an external LED using a Google Coral Dev Board (Coral)

# Engineering
  # Google 
    # https://coral.ai/docs/dev-board/get-started/
    # https://coral.ai/examples/
  # ATS, 2019, https://github.com/AnchorageBot

# Bill of Materials
  # Coral (1 ea) https://coral.ai/products/dev-board/
  # MicroSD Card (1 ea) https://www.adafruit.com/product/2693
  # USB A to USB C Cable (1 ea) for Laptop Data connection
  # USB A to USB C Cable (1 ea ) for Phone Charger Power connection
  # 2-3 A / 5 V Phone Charger (1 ea)
  # OSEPP LED Module (1 ea) https://www.digikey.com/en/products/detail/osepp-electronics-ltd/LEDWH-01/11198626
  # Female/Female Jumper Wires (3 ea or 1 package) https://www.adafruit.com/product/266
  
# Software
  # Mendel, Debian Linux, https://coral.ai/software/
  # Atom Text Editor, https://atom.io
  
# Wiring Connections
  # Coral GPIO Pin 1 = Power for LED Module
  # Coral GPIO Pin 6 = Ground for LED Module 
  # Coral GPIO Pin 18 = Signal for LED Module
  # Coral USB C Port = Data for Laptop
  # Coral USB C Power Port = Power from 2-3 A / 5 V Phone Charger
  
from periphery import GPIO
import time

gpio = GPIO(138,"out")

gpio.write(True)
time.sleep(1)

gpio.write(False)
time.sleep(1)

gpio.write(True)
time.sleep(1)

gpio.close()

# To turn off the Coral use the following command in the terminal prior to powering down
# sudo shutdown now
