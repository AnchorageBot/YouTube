/*
 * This sketch will log (SD card) and print (serial monitor) data from the PT550 sensor and the RTC shield every 6 seconds
 using Arduino IDE 1.8.10
 
   Materials Schedule
   (1 each) Adafruit Feather 32u4 Bluefruit LE with stacking headers
     https://learn.adafruit.com/adafruit-feather-32u4-bluefruit-le?view=all#overview
   (1 each) Adafruit Adalogger Feather Wing
     https://www.adafruit.com/product/2922
   (1 each) DF Robot PT550 Analog Ambient Light Sensor
    https://www.dfrobot.com/product-1004.html
   (1 each) Sparkfun Cerberus USB Cable
     https://www.sparkfun.com/products/12016  
   (3 each) 28AWG male/male jumper wires 
     https://www.adafruit.com/product/266
   (1 each) Adafruit Terminal Block Breakout Feather Wing
     https://learn.adafruit.com/adafruit-terminal-block-prototyping-breakout-featherwing/overview  

  Assembly
   1.Update Arduino software
     a.Arduino->Preferences->Additional Boards URL->https://adafruit.github.io/arduino-board-index/package_adafruit_index.json
     b.Tools->Boards Manager->Contributed->Adafruit AVR Boards
     c.Tools->Board->Adafruit Feather 32u4
     d.Tools->Port->/dev/cu.usbmodem1D11201 (Adafruit Feather 32u4)
     e.Tools->Programmer->"ArduinoISP"    
   2.Connect adalogger feather wing to the feather by stacking the two boards
     a.Run PCF 8523 tutorial and install battery with only the feather and the adalogger if not already done
     b.Wing (Shield) uses the following pins
       ** CS - pin 10      
       ** MOSI - pin 11
       ** MISO - pin 12
       ** CLK - pin 13
   3.Connect light sensor to Feather with (3) male/male wires
     a.Sensor (Out) Feather pin 1 (A)
     b.Sensor (+)   Feather (VCC) Voltage
     c.Sensor (-)   Feather (GND) Ground     
   4.Attach Cerberus USB Cable to Feather and Laptop
   5.Verify/compile & upload program to Feather
     a.Sketch->Verify/Compile
     b.Sketch->Upload     

  Engineering
   Adafruit - Adalogger Feather Wing
     https://learn.adafruit.com/adafruit-adalogger-featherwing/overview     
   Arduino
     SD Card Code Examples preloaded in the Arduino IDE
       File -> Examples -> SD
       File -> Examples -> SD -> Datalogger
     Functions, Variables, and Structure Code Dictionary
       https://www.arduino.cc/reference/en/#functions   
   DFrobot - PT550 sensor
     https://www.dfrobot.com/product-1004.html
   Paul McWhorter Lesson 21
     http://www.toptechboy.com/arduino/arduino-lesson-21-log-sensor-data-to-an-sd-card/    
   ATS
     https://www.youtube.com/channel/UCDuWq2wFqeVII1KC7grySRg?view_as=subscriber
     modified December 2019     
 
 */

// === Libraries ================================

#include <SPI.h>                                         // Load Serial Peripheral Interface (SPI) library 
#include <SD.h>                                          // Load SD card library
#include <RTClib.h>                                      // Load PCF 8523 RTC library

// === Gobal constants and variables ============

int sensorTime = 6000;                                   // delay for sensors

// Adalogger Feather Wing (RTC and SD card)
RTC_PCF8523 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

#define cardSelect 4                                    // 4, Adafruit Feather Wing uses 10
File logfile;                                           // Make a data object for the sensor data to be written to

//=== Setup code here, runs once ================

void setup() 
{

  while (!Serial) {
    delay(1);  // for Leonardo/Micro/Zero
  }
  

  Serial.begin (57600);                                 // Setup the serial monitor for data analysis & debugging, match baud rate with serial monitor setting
  
  if (! rtc.begin()) {                                  // Initialize the RTC (real time clock)
    Serial.println("Couldn't find RTC");
    while (1);
  }

 if (! rtc.initialized()) {
    Serial.println("RTC is NOT running!");
     rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));    // line sets the RTC to the date & time this sketch was compiled
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));      // line sets the RTC with an explicit date & time, for example Jan 21, 2014 at 3am:
  }  

pinMode(10, OUTPUT);                                    // Reserve pin 10 for the Adafruit Feather Wing
  if (! SD.begin()) {                                   // Initialize the SD card (secure digital card)
    Serial.println("Couldn't find SD card");
    while (1);
  }  
}

//=== Main code here, runs/loops repeatedly=====

void loop()
{
  pcf8523();                                           // comment out when datalogger is connected to power and disconected from computer
  pt550();                                             // comment out when datalogger is connected to power and disconected from computer
  SDcard();  
}

//===Sensor functions ===========================

void pcf8523() 
{
    DateTime now = rtc.now();                          // connect to the RTC 
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
    Serial.println();
}

void pt550()
{
      int val;
      val=analogRead(1);                                //  connect to the light sensor
      Serial.print("Light intensity in Lux: ");
      Serial.println(val,DEC);                          //  print the value to serial, DEC = decimal in base 10
      Serial.println(" ");       
}

void SDcard()
{
  logfile = SD.open("BluData.txt", FILE_WRITE);        // open and name the file for the sensor data to be saved to the SD card
    
  DateTime now = rtc.now();                            // connect to the RTC 
  logfile.print(now.year(), DEC);                      // write RTC data to the SD card
  logfile.print(',');
  logfile.print(now.month(), DEC);
  logfile.print(',');
  logfile.print(now.day(), DEC);
  logfile.print(',');
  logfile.print(daysOfTheWeek[now.dayOfTheWeek()]);
  logfile.print(',');
  logfile.print(now.hour(), DEC);
  logfile.print(',');
  logfile.print(now.minute(), DEC);
  logfile.print(',');
  logfile.print(now.second(), DEC);
  logfile.print(',');  

  int val;
  val=analogRead(1);                                 // connect to the light sensor 
  logfile.print(val, DEC);                           // write temperature data to the SD card
  logfile.println("");                               // new line

  delay(sensorTime);
  
  logfile.close();                                   //  close the sensor data file
}
