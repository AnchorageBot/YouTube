# This script displays sensor and input data on the CLUE display and prints sensor data via serial
# Script source code
    # https://docs.circuitpython.org/projects/clue/en/latest/
    # https://docs.circuitpython.org/projects/clue/en/latest/api.html
    # https://github.com/adafruit/Adafruit_CircuitPython_CLUE
    # CLUE CircuitPython Tutorial: https://learn.adafruit.com/adafruit-clue/circuitpython

# Modified by ATS, April, 2022, https://github.com/AnchorageBot

# IDE: Mu version 1.0.3, https://codewith.mu
# Hardware: CLUE, https://www.adafruit.com/clue
# CircuitPython version 7.2.5, https://circuitpython.org/board/clue_nrf52840_express/
# CircuitPython Libraries 7.x, https://circuitpython.org/libraries
    # adafruit_apds9960
    # adafruit_bmp280.mpy
    # adafruit_bus_device
    # adafruit_clue.mpy
    # adafruit_display_shapes
    # adafruit_display_text
    # adafruit_lis3mdl.mpy
    # adafruit_lsm6ds
    # adafruit_register
    # adafruit_sht31d.mpy
    # adafruit_slideshow.mpy
    # neopixel.mpy

# URL for RPi_GetMCUdata.py script file to save CLUE sensor data to a RPi
    # Run the RPi_GetMCUdata.py script on the RPi using the Mu IDE
    # https://github.com/AnchorageBot/YouTube/blob/master/RPi_getMCUdata.py

from adafruit_clue import clue

clue.sea_level_pressure = 1020

#clue_data = clue.simple_text_display(title="CLUE Sensor Data!", title_scale=2, text_scale = 2)
clue_data = clue.simple_text_display(text_scale = 2)

while True:
    clue_data[0].text = "Accel: {:.2f} {:.2f} {:.2f}".format(*clue.acceleration)
    clue_data[1].text = "Gyro: {:.2f} {:.2f} {:.2f}".format(*clue.gyro)
    clue_data[2].text = "Mag: {:.3f} {:.3f} {:.3f}".format(*clue.magnetic)
    clue_data[3].text = "Pressure: {:.3f}hPa".format(clue.pressure)
    clue_data[4].text = "Altitude: {:.1f}m".format(clue.altitude)
    clue_data[5].text = "Temperature: {:.1f}C".format(clue.temperature)
    clue_data[6].text = "Humidity: {:.1f}%".format(clue.humidity)
    clue_data[7].text = "RGB: {} {} {} {}".format(*clue.color)
    #clue_data[8].text = "Proximity: {}".format(clue.proximity)
    #clue_data[9].text = "Gesture: {}".format(clue.gesture)
    #clue_data[10].text = "Button A: {}".format(clue.button_a)
    #clue_data[11].text = "Button B: {}".format(clue.button_b)
    #clue_data[12].text = "Touch 0: {}".format(clue.touch_0)
    #clue_data[13].text = "Touch 1: {}".format(clue.touch_1)
    #clue_data[14].text = "Touch 2: {}".format(clue.touch_2)
    clue_data.show()

    print("Accel: {:.2f} {:.2f} {:.2f} m/s^2".format(*clue.acceleration))
    print("Gyro: {:.2f} {:.2f} {:.2f} dps".format(*clue.gyro))
    print("Mag: {:.3f} {:.3f} {:.3f} uTesla".format(*clue.magnetic))
    print("Pressure: {:.3f} 0 0 hPa".format(clue.pressure))
    print("Altitude: {:.1f} 0 0 m".format(clue.altitude))
    print("Temperature: {:.1f} 0 0 C".format(clue.temperature))
    print("Humidity: {:.1f} 0 0 %".format(clue.humidity))
    #print("Proximity: {}".format(clue.proximity))
    #print("Gesture: {}".format(clue.gesture))
    print("ColorRGB_DTG: {} {} {} {}".format(*clue.color))
    print("--------------------------------")
