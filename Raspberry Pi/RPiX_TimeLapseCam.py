# This script will make a timelapse camera using a Raspberry Pi Octocam Kit from Pimoroni

# Engineering: 
  # Pimoroni 
    # https://learn.pimoroni.com/article/assembling-octocam
    # https://github.com/pimoroni
   # Picamera
    # https://picamera.readthedocs.io/en/release-1.13/development.html
    # https://github.com/waveform80/picamera
  # ATS, April 2022
    # https://github.com/AnchorageBot

# Bill of Materials
  # Pimoroni Octocam Kit https://shop.pimoroni.com/products/octocam-pi-zero-w-project-kit?variant=41224005898
  
# Software
  # Mu IDE https://codewith.mu
  # Raspian https://www.raspberrypi.com/software/
  
import time
import picamera

# Set camera resolution
# 1920 x 1080 = ~ 1.1 mb per photo
camera = picamera.PiCamera()
camera.resolution = (1920, 1080)

# Turn on camera and detect light levels
camera.start_preview()
time.sleep(5)

# Photoloop that timestamps photos
# Photo name format img-timestamp.jpg
try:
  while True:
    ts=time.strftime("%Y-%m-%-%H%M%s", time.gmtime())
    camera.capture('img-'+ts+'.jpg')
    time.sleep(3600)
 
except KeyboardInterrupt:
  camera.stop_preview()
  sys.exit()
