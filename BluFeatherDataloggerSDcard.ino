/*
 * This sketch will log (SD card) and print (serial monitor) data from the PT550, the SEN0193 sensor, the DHT22 sensor and the RTC shield
 * every 6 seconds using Arduino IDE 1.8.10
 
   Materials Schedule
   (1 each) Adafruit Feather 32u4 Bluefruit LE with stacking headers
     https://learn.adafruit.com/adafruit-feather-32u4-bluefruit-le?view=all#overview
   (1 each) Adafruit Adalogger Feather Wing
     https://www.adafruit.com/product/2922
   (1 each) DF Robot PT550 Analog Ambient Light Sensor
    https://www.dfrobot.com/product-1004.html
   (1 each) DF Robot SEN0193 Capacitive Soil Moisture Sensor
    https://www.dfrobot.com/product-1385.html    
   (1 each) DHT22 AM2302 Temperature and Humidity Sensor
     https://www.adafruit.com/product/393
   (1 each) Sparkfun Cerberus USB Cable
     https://www.sparkfun.com/products/12016  
   (6 each) 28AWG male/male jumper wires 
     https://www.adafruit.com/product/266
   (1 each) Half-size breadboard
     https://www.adafruit.com/product/64   

  Assembly
   1.Update Arduino software
     a.Arduino->Preferences->Additional Boards URL->https://adafruit.github.io/arduino-board-index/package_adafruit_index.json
     b.Tools->Boards Manager->Contributed->Adafruit AVR Boards
     c.Tools->Board->Adafruit Feather 32u4
     d.Tools->Port->/dev/cu.usbmodem1D11201 (Adafruit Feather 32u4)
   2.Connect light sensor to Feather with (3) male/male wires
     a.Sensor (Out) Feather pin 1 (A)
     b.Sensor (+)   Feather (VCC) Voltage
     c.Sensor (-)   Feather (GND) Ground      
   3.Connect soil humidty sensor to Feather with (3) male/male wires
     a.Sensor (Out) Feather pin 0 (A)
     b.Sensor (+)   Feather (VCC) Voltage
     c.Sensor (-)   Feather (GND) Ground       
   4.Connect temp & humidty sensor to Feather with (3) male/male wires and (1) ten ohm resistor
     a.Sensor (Out) Feather pin 9 (D)
     b.Sensor (+)   Feather (VCC) Voltage
     c.Sensor (-)   Feather (GND) Ground     
   5.Connect adalogger feather wing to  the feather by stacking the two boards
     a.Run PCF 8523 tutorial and install battery with only the feather and the adalogger if not already done
     b.Wing (Shield) uses the following pins
       ** MOSI - pin 11
       ** MISO - pin 12
       ** CLK - pin 13
       ** CS - pin 10 
   6.Attach Cerberus USB Cable to Feather and Laptop
   7.Verify/compile & upload program to Feather
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
   DFrobot - Sen0193
     https://www.dfrobot.com/product-1385.html  
   Adafruit - DHT22 sensor
     https://learn.adafruit.com/adafruit-io-basics-temperature-and-humidity?view=all       
   Paul McWhorter Lesson 21
     http://www.toptechboy.com/arduino/arduino-lesson-21-log-sensor-data-to-an-sd-card/    
   ATS
     https://www.youtube.com/channel/UCDuWq2wFqeVII1KC7grySRg?view_as=subscriber
     modified December 2019     
 
 */

// === Libraries ================================

#include <SPI.h>    // Load Serial Peripheral Interface (SPI) library 
#include <SD.h>     // Load SD card library
#include "RTClib.h" // Load PCF 8523 RTC library
#include <Adafruit_Sensor.h>
#include <DHT_U.h> 
#include <DHT.h>; // Call DHT22 Library

// === Gobal constants and variables ============

int sensorTime = 6000; // delay for sensor

// Adalogger Feather Wing (RTC and SD card)
RTC_PCF8523 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

#define cardSelect 10 // Adafruit Feather Wing uses 10
File logfile;  //Data object sensor data is written to

// Light sensor
int val;  // Stores light values using an illumination range : 1 Lux to 6000 Lux

// Soil humidity sensor
const int AirValue = 520;   // Adjust max AirValue as neccessary
const int WaterValue = 260;  // Adjust min WaterValue as neccessary
int intervals = (AirValue - WaterValue)/3;   
int soilMoistureValue = 0; // Feather Analog pin 0

String dry = "Plant needs water, soil sensor value is: "; // dry range is from 430 to 520
String happy = "Plant has enough water, soil sensor value is: "; // happy range is from 350 to 430
String soaked = "Plant has too much water, soil sensor value is: "; // soaked range is from 260 to 350

// Air temperature and humidity sensor
#define DHTPIN 9       // DHT-22 sensor & Feather Pin 9
#define DHTTYPE DHT22   // DHT 22 sensor type is AM2302
float hum;    // Stores humidity value in percent
float temp;   // Stores temperature value in Celcius
float tempF;  // Stores temperature value in Fahrenheit
DHT dht(DHTPIN, DHTTYPE); // Initialize DHT sensor

//=== Setup code here, runs once ================

void setup() 
{

  while (!Serial) {
    delay(1);  // for Leonardo/Micro/Zero
  }
  
  // Setup the serial monitor for data analysis & debugging
  Serial.begin (57600);
  
  if (! rtc.begin()) {                                  // Initialize the RTC (real time clock)
    Serial.println("Couldn't find RTC");
    while (1);
  }

 if (! rtc.initialized()) {
    Serial.println("RTC is NOT running!");
     rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));     // line sets the RTC to the date & time this sketch was compiled
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));      // line sets the RTC with an explicit date & time, for example Jan 21, 2014 at 3am:
  }  

pinMode(10, OUTPUT);                                    // Must declare 10 an output and reserve it for the Adafruit Feather Wing
  if (! SD.begin()) {                                   // Initialize the SD card (secure digital card)
    Serial.println("Couldn't find SD card");
    while (1);
  }  

  dht.begin();    // Start the DHT sensor
    
}

//=== Main code here, runs/loops repeatedly=====

void loop()
{
  pcf8523();
  pt550();
  sen0193();   
  dht22();   
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
    //delay(sensorTime);                             // comment out when SDcard function is in use
}

void pt550()
{
      //int val;
      val=analogRead(1);                                //connect to the light sensor
      Serial.print("Light intensity in Lux: ");
      Serial.println(val,DEC);                          //print the value to serial
      Serial.println(" ");       
      //delay(sensorTime);                              // comment out when SDcard function is in use
}

void sen0193() // soil moisture sensor
{

  // operate soil moisture sensor 
 soilMoistureValue = analogRead(A0);
 
 // report soil moisture sensor values 
 String drySensor = dry + soilMoistureValue;
 String happySensor = happy + soilMoistureValue;
 String soakedSensor = soaked + soilMoistureValue;
 
 if(soilMoistureValue > WaterValue && soilMoistureValue < (WaterValue + intervals))
 {
   Serial.println(soakedSensor);
 }
 
 else if(soilMoistureValue > (WaterValue + intervals) && soilMoistureValue < (AirValue - intervals))
 {
   Serial.println(happySensor);
 }
 
 else if(soilMoistureValue < AirValue && soilMoistureValue > (AirValue - intervals))
 {
   Serial.println(drySensor);
 }

 Serial.println(" "); 
 //delay(sensorTime);  // comment out when SD card is in use
}

void dht22() // dht22 air temp & humidity sensor
{
    delay(sensorTime);  // Delay to stabilize DHT-22 sensor, optimize data output, minimize energy use 
   
    hum = dht.readHumidity();  // Get Humidity value
    temp= dht.readTemperature();  // Get Temperature value
    tempF= (temp*(1.8))+32;
    
  // Send results to Serial Monitor
  
    Serial.print("Air Humidity: ");
    Serial.print(hum);
    Serial.print(" %, Air Temp: ");
    Serial.print(temp);
    Serial.print(" °C, ");
    Serial.print(tempF);
    Serial.println(" °F");
  
  Serial.println(" ");                     
}

void SDcard()
{
  logfile = SD.open("BluData.txt", FILE_WRITE);   // open and name the file for the sensor data to be saved to the SD card
    
  DateTime now = rtc.now();                       // connect to the RTC 
  logfile.print(now.year(), DEC);                 // write RTC data to the SD card
  logfile.print(',');
  logfile.print(now.month(), DEC);
  logfile.print(',');
  logfile.print(now.day(), DEC);
  logfile.print(" ");
  logfile.print(daysOfTheWeek[now.dayOfTheWeek()]);
  logfile.print(" ");
  logfile.print(" ");
  logfile.print(now.hour(), DEC);
  logfile.print(',');
  logfile.print(now.minute(), DEC);
  logfile.print(',');
  logfile.print(now.second(), DEC);
  logfile.print(',');  

  int val;
  val=analogRead(1);                              // connect to the light sensor 
  logfile.print(val);                             // write temperature data to the SD card
  logfile.print(',');  
  
  soilMoistureValue = analogRead(A0);
  logfile.print(soilMoistureValue);               // write soil moisture data to the SD card
  logfile.print(',');   

  delay(sensorTime);
  hum = dht.readHumidity();                      // connect to the air temp and humidity sensor
  temp= dht.readTemperature();                   
  tempF= (temp*(1.8))+32;                        
  logfile.print(hum);                            // write air humidity value to the SD card
  logfile.print(',');    
  logfile.print(temp);                           // write air temp value in C to the SD card
  logfile.print(',');    
  logfile.print(tempF);                          // write air temp value in F to the SD card
  
  logfile.println("");                            // new line
  //delay(sensorTime);
  
  logfile.close();                                //  close the sensor data file
}
