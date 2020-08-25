/*
  This sketch uses onboard sensors from a Arduino Nano 33 BLE Sense to read air temp (HTS221), humidity (HTS221), pressure (LPS22HB), and RGB color (APDS9960) on an adjustable time interval using Arduino IDE 1.8.10
  
  Materials Schedule
   (1 each) Arduino Nano 33 BLE Sense
     https://store.arduino.cc/usa/nano-33-ble-sense-with-headers
   (1 each) Sparkfun Cerberus USB Cable
     https://www.sparkfun.com/products/12016
   (1 each) Half-size breadboard
     https://www.adafruit.com/product/64        
       
  Assembly
   1.Update Arduino software
     a.Tools->Board->Boards Manager->Arduino nRF528x mbed Core
     c.Tools->Board->Arduino NANO 33 BLE
     d.Tools-Port->/dev/cu.usbmodem14101 (Arduino NANO 33 BLE)
     e.Sketch->Include Library->Add .ZIP Library (HTS221, LPS22HB, and APDS9960 from Sandeep Mistry's github) 
        or 
       Tools -> Manage Libraries (HTS221, LPS22HB, and APDS9960)
   2.Attach Cerberus USB Cable to Nano and Laptop or Raspberry Pi
   3.Verify/compile & upload program to NANO 33 BLE
     a.Sketch->Verify/Compile
     b.Sketch->Upload 

  Engineering
   Arduino
    https://www.arduino.cc/en/Guide/NANO33BLESense
    revised 2019/08/17 by SM  
   Sandeep Mistry 
    https://github.com/arduino-libraries/Arduino_HTS221
    July 2019 
    https://github.com/arduino-libraries/Arduino_LPS22HB
    July 2019 
    https://github.com/arduino-libraries/Arduino_APDS9960
    August 2019 
   ATS
     https://github.com/AnchorageBot
     modified january 2020
   
*/

#include <Arduino_HTS221.h>
#include <Arduino_LPS22HB.h>
#include <Arduino_APDS9960.h>

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!HTS.begin()) {
    Serial.println("Failed to initialize humidity and temperature sensor!");
    while (1);
  }

  if (!BARO.begin()) {
    Serial.println("Failed to initialize pressure sensor!");
    while (1);
  }  

  if (!APDS.begin()) {
    Serial.println("Error initializing APDS9960 sensor.");
  }
}

void loop() {
  // read the HTS221 temp & humidty sensor values
  float temperature = HTS.readTemperature();
  float humidity    = HTS.readHumidity();
  float tempF = (temperature*(1.8))+32;

  // print the HTS221 temp & humidty sensor values via serial terminal
  Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.print(" °C  ");
  Serial.print(tempF);
  Serial.println(" °F");

  Serial.print("Humidity    = ");
  Serial.print(humidity);
  Serial.println(" %");

  // print an empty line
  Serial.println();

  // read the LPS22HB pressure sensor value
  float pressure = BARO.readPressure();
  float psi = pressure/6.895;
  float hg = pressure/3.386;

  // print the LPS22HB pressure sensor value via serial terminal
  Serial.print("Pressure = ");
  Serial.print(pressure);
  Serial.print(" kPa  ");
  Serial.print(psi);
  Serial.print(" psi  ");
  Serial.print(hg);
  Serial.println(" inches of mercury");
  
  // print an empty line
  Serial.println();

  // check if a color reading is available
  if (APDS.colorAvailable()) {
    int r, g, b;

  // read the APDS9960 color sensor
  APDS.readColor(r, g, b);

  // print the APDS9960 color sensor values via serial terminal
  Serial.println("Color Sensor Values -> 255 maximum");
  Serial.print("Red = ");
  Serial.println(r);
  Serial.print("Green = ");
  Serial.println(g);
  Serial.print("Blue = ");
  Serial.println(b);
  Serial.println();
  }

  // wait 10 seconds to print again
  delay(10000);
}
