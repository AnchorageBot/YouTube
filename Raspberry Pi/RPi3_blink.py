# Python v 3.4.2
# This program will blink a red LED
#
# Project calculations
#
#    Controlling equation = Ohm's Law = R = (V)(I)
#    VF = Voltage Forward for LED = 1.7 V (volts)
#    IF = Current Forward for LED = 25 mA (milli-amps)
#    VO = Voltage Output for RPi = 5V
#    R = Resistance = (VO - VF)(IF) = (5 - 1.7)(25) = (3.3)(25) = 82.5
#
#  Materials List
#
#    Raspberry Pi 3B+ (RPi)
#    OSEP Red LED Module with onboard/integrated resistor
#    (3) Female/Male AWG 22 gauge wires
#    RPi (General Purpose Input/Output) GPIO pin layout quick reference
#
#  Assembly
#
#    Connect GND black wire to RPi GPIO pin 6
#    Connect PWR red wire to RPi GPIO pin 2
#    Connect S white wire to RPi GPIO pin 7

#   ATS
#   https://github.com/AnchorageBot

#
#  Libraries
import RPi.GPIO as GPIO
import time
#
#  Global constants and variables
Delay = 0.5 # time in seconds
#
#  Setup
GPIO.setmode(GPIO.BOARD)
GPIO.setup(7, GPIO.OUT) # Assign GPIO pin 7 to control LED
#
#  Main Loop
while True:
    GPIO.output(7, GPIO.HIGH) # Turn on LED
    time.sleep(Delay)
    GPIO.output(7, GPIO.LOW) # Turn off LED
    time.sleep(Delay)
