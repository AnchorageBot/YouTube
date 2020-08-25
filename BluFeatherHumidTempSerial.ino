/***
  Sample air temperature and humdity

  Materials Schedule
   (1 each) Adafruit Feather 32u4 Bluefruit LE with stacking headers
     https://learn.adafruit.com/adafruit-feather-32u4-bluefruit-le?view=all#overview
   (1 each) Sparkfun Cerberus USB Cable
     https://www.sparkfun.com/products/12016
   (1 each) DHT22 AM2302 Temperature and Humidity Sensor
     https://www.adafruit.com/product/393
   (3 each) 28AWG female/female jumper wires 
     https://www.adafruit.com/product/266    
       
  Assembly
   1.Update Arduino software
     a.Arduino->Preferences->Additional Boards URL->https://adafruit.github.io/arduino-board-index/package_adafruit_index.json
     b.Tools->Boards Manager->Contributed->Adafruit AVR Boards
     c.Tools->Board->Adafruit Feather 32u4
     d.Tools->Port->/dev/cu.usbmodem1D11201 (Adafruit Feather 32u4)
     e.Sketch->Include Library->Manage Libraries->Adafruit Unified Sensor Library
     f.Sketch->Include Library->Manage Libraries->Adafruit AM2320 Sensor Library
     g.Sketch->Include Library->Manage Libraries->DHT Sensor Library
   2.Connect temp & humidty sensor to Feather with (3) female/female wires
     a.Sensor (Out) Feather pin 10 (D)
     b.Sensor (+)   Feather (VCC) Voltage
     c.Sensor (-)   Feather (GND) Ground  
   3.Attach Cerberus USB Cable to Feather and Laptop
   4.Verify/compile & upload program to Feather
     a.Sketch->Verify/Compile
     b.Sketch->Upload  
     
  Engineering
   Adafruit
     https://learn.adafruit.com/adafruit-io-basics-temperature-and-humidity?view=all
   
   ATS
     https://www.youtube.com/channel/UCDuWq2wFqeVII1KC7grySRg?view_as=subscriber
     modified August 2019
  
***/

// === Libraries ================================

#include <Adafruit_Sensor.h>
#include <DHT_U.h> 
#include <DHT.h>; // Call DHT22 Library

// === Gobal constants and variables ============

// Temp & Humidity Sensor Constants
#define DHTPIN 10       // DHT-22 sensor & Feather Pin 
#define DHTTYPE DHT22   // DHT 22 sensor type is AM2302

// Temp & Humidity Sensor Variables
float hum;    // Stores humidity value in percent
float temp;   // Stores temperature value in Celcius

DHT dht(DHTPIN, DHTTYPE); // Initialize DHT sensor for Feather

//=== Setup code here, runs once ================

void setup() 
{
  // Setup the serial monitor for data analysis & debugging
  Serial.begin (9600);
  
  // Start the DHT sensor
  dht.begin();
}

//=== Main code here, runs/loops repeatedly=====

void loop() 
{
  delay(2000);  // Delay so DHT-22 sensor can stabalize
   
    hum = dht.readHumidity();  // Get Humidity value
    temp= dht.readTemperature();  // Get Temperature value
    
  // Send results to Serial Monitor
  
    Serial.print("Humid: ");
    Serial.print(hum);
    Serial.print(" %, Temp: ");
    Serial.print(temp);
    Serial.print(" C, ");
  
  Serial.println(" ");                     
}
