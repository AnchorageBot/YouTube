/*
 *   This sketch will print (serial monitor), log (SD card), and broadcast (BLE) data 
 *   from a TSL2591 sensor, a SEN0193 sensor, a DHT22(AM2302) sensor, a LED, and a RTC/SD 
 *   card/shield/Adalogger Featherwing every 60 seconds via a 32u4 BLE Feather MCU, 
 *   the Arduino IDE 1.8.13, & Adafruit Bluefruit iPhone app
 *   
 *   32u4 BLE MCU 28672 bytes = 32KB of flash     
 *     Sketch uses 28670 bytes (99%) of program storage space. Maximum is 28672 bytes.
 *     Global variables use 1707 bytes of dynamic memory
 *
 *   Arcade Clear LED Mini
 *     https://www.adafruit.com/product/3429
 *     A1 to (+) white wire
 *     GND to (-) blue wire
 *
 *   TSL2591 Digital Light Sensor 
 *     https://learn.adafruit.com/adafruit-tsl2591
 *     SCL to I2C Clock
 *     SDA to I2C Data
 *     VCC to 3.3-5V DC
 *     GND to ground
 *   
 *   SEN0193
 *     https://www.dfrobot.com/product-1385.html
 *     A0 to (A)  
 *     VCC to (+)
 *     GND to (-)
 *   
 *   DHT22
 *     https://www.adafruit.com/product/393
 *     A5 to (OUT)
 *     VCC to (+)
 *     GND to (-)
 *   
 *   RTC/SD Card Shield/Adalogger Featherwing
 *     https://www.adafruit.com/product/2922
 *   
 *   Terminal Block Breakout
 *     https://www.adafruit.com/product/2926
 *   
 *   32u4 BLE (Bluefruit) Feather MCU                                
 *     https://www.adafruit.com/product/2829               
 *   
 *   Arduino Board Manager URLs for MacBook 
 *     https://www.adafruit.com/package_adafruit_index.json
 *     http://arduino.esp8266.com/stable/package_esp8266com_index.json
 *     https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
 *   
 *   Engineering 
 *     Adafruit & DFrobot
 *       https://learn.adafruit.com/bluefruit-feather-robot/code
 *       
 *     ATS, Oct 2020
 *       https://www.youtube.com/channel/UCDuWq2wFqeVII1KC7grySRg
 *       https://github.com/AnchorageBot
 */

// === Libraries ================================

#include <SPI.h>                     // Load Serial Peripheral Interface (SPI) library 
//#include <Wire.h>                    // Load I2/TWC library

#include <Adafruit_Sensor.h>         // Load Adafruit sensors library

#include "Adafruit_TSL2591.h"        // Load TSL2591 library

#include <DHT.h>;                    // Load DHT22 libraries
#include <DHT_U.h> 

#include "RTClib.h"                  // Load PCF 8523 RTC library
#include <SD.h>                      // Load SD card library

#include <Adafruit_BLE.h>            // Load Adafruit bluetooth libraries
#include <Adafruit_BluefruitLE_SPI.h>
#include "Adafruit_BluefruitLE_UART.h"

// === Gobal constants and variables ============

String Plant = "Avo";              // "Avo", "Iris", "HydraW", "HydraE"

int sensorTime = 30000;               // Calibration & output delay for all sensors, 60000 millisec = 60 sec

int arcadeLED = A1;                   // assign pin to arcade LED for blinky function
int blinkySpeed = 500;                // assign blinky function speed to arcade LED

// Light sensor TSL2591 
Adafruit_TSL2591 tsl = Adafruit_TSL2591(2591);  // Store light values 

// Soil humidity sensor SEN0193
const int Air = 520;              // Adjust Air value as neccessary (520 original)
const int Water = 260;            // Adjust Water value as neccessary (260 original)
int phase = (Air - Water)/3;   
int Soil = 0;                     // Set initial sensor reading to 0 
String dry = "Thirsty ";          // dry range: 430 to 520
String happy = "Happy ";          // happy range: 350 to 430
String soaked = "Soaked ";        // soaked range: 260 to 350

// Air temperature & humidity sensor DHT22 (AM2302)
#define DHTPIN A5                // DHT-22 sensor uses analog pin A5 to communicate data for 32u4, pin 
#define DHTTYPE DHT22            // DHT 22 sensor type (AM2302)
float hum;                       // Store humidity in percent
float tempC;                     // Store temperature in Celcius
float tempF;                     // Store temperature in Fahrenheit
DHT dht(DHTPIN, DHTTYPE);        // Initialize DHT sensor

// RTC/SD Card Shield / Adalogger
RTC_PCF8523 rtc;
char Days[7][12] = {"Sun", "Mon", "Tues", "Wed", "Thurs", "Fri", "Sat"};

#define cardSelect 10            // Adalogger uses pin 10 to communicate data with 32u4, pin 33 for ESP32      
File logfile;                    // Data object sensor data is written to

// BlueTooth (BLE) broadcasting/commo
String BROADCAST_NAME = Plant;  
String BROADCAST_CMD = String("AT+GAPDEVNAME=" + BROADCAST_NAME);
#define BLUEFRUIT_SPI_CS 8
#define BLUEFRUIT_SPI_IRQ 7
#define BLUEFRUIT_SPI_RST 4 
Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);
uint8_t readPacket(Adafruit_BLE *ble, uint16_t timeout);
float parsefloat(uint8_t *buffer);
void printHex(const uint8_t * data, const uint32_t numBytes);
extern uint8_t packetbuffer[];
char buf[60];

//===Configure Light sensor TSL2591 ============

void config2591(void)
{
  // Change the gain to adapt to brighter/dimmer light situations
  //tsl.setGain(TSL2591_GAIN_LOW);    // 1x gain (bright light)
  tsl.setGain(TSL2591_GAIN_MED);      // 25x gain
  //tsl.setGain(TSL2591_GAIN_HIGH);   // 428x gain
  
  // Changing the integration time allows for use in low or bright light situtations
  //tsl.setTiming(TSL2591_INTEGRATIONTIME_100MS);  // shortest integration time (bright light)
  tsl.setTiming(TSL2591_INTEGRATIONTIME_300MS);
  // tsl.setTiming(TSL2591_INTEGRATIONTIME_600MS);  // longest integration time (dim light)

  /* Display the gain and integration time for reference sake */  
  Serial.println(F("------------------------------------"));
  Serial.print  (F("Gain:         "));
  tsl2591Gain_t gain = tsl.getGain();
  switch(gain)
  {
    //case TSL2591_GAIN_LOW:
      //Serial.println(F("1x (Low)"));
      //break;
    case TSL2591_GAIN_MED:
      Serial.println(F("25x (Med)"));
      break;
    //case TSL2591_GAIN_HIGH:
      //Serial.println(F("428x (High)"));
      //break;
    //case TSL2591_GAIN_MAX:
      //Serial.println(F("9876x (Max)"));
      //break;
  }
  Serial.print  (F("Timing:       "));
  Serial.print((tsl.getTiming() + 1) * 100, DEC); 
  Serial.println(F(" ms"));
  Serial.println(F("------------------------------------"));
  Serial.println(F(""));
}

//=== Setup code here, runs once ================

void setup() 
{
  Serial.begin (9600);                                  // Setup the serial monitor for data analysis & debugging

  pinMode(arcadeLED, OUTPUT);                           // initialize digital pin led as an output
  
  if (! rtc.begin()) {                                  // Initialize the RTC 
    Serial.println("RTC MIA");
    while (1);
  }

 if (! rtc.initialized()) {
    Serial.println("RTC KIA");
     rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));    // line sets the RTC to the date & time this sketch was compiled
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));      // line sets the RTC with an explicit date & time, for example Jan 21, 2014 at 3am:
  }  

pinMode(10, OUTPUT);                                    // Adalogger reserves/uses 10 as an output  
  if (! SD.begin()) {                                   // Initialize the SD card (secure digital card)
    Serial.println("SD MIA");
    while (1);
  }  
                                 
  config2591();                                        // Configure TSL2591 sensor

  dht.begin();                                         // Start DHT22 sensor

  ble.begin();                                        //  Set up bluetooth
  ble.echo(false);                                    //  Turn off echo
  ble.verbose(false);
  BROADCAST_CMD.toCharArray(buf, 60);
  ble.sendCommandCheckOK(buf);
  delay(500);
  ble.setMode(BLUEFRUIT_MODE_DATA);                   //  Set to data mode
  delay(500);  
}

//=== Main code, runs/loops repeatedly==========

void loop()
{
  pcf8523();
  tsl2591();
  sen0193();   
  dht22();   
  SDcard();
  BlueTooth();
  blinky();
  blinky();
  blinky();
}

//===Sensor functions ===========================

void pcf8523()                  // RTC (real time clock) function 
{
    DateTime now = rtc.now();                          
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(Days[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
}

void tsl2591()               // Light sensor function
{
  // Read 32 bits with top 16 bits IR, bottom 16 bits full spectrum for math & comparisons
  uint32_t lum = tsl.getFullLuminosity();
  uint16_t ir, full;
  ir = lum >> 16;
  full = lum & 0xFFFF;
  //Serial.print(F("[ ")); Serial.print(millis()); Serial.print(F(" ms ] "));
  //Serial.print("IR:"); Serial.println(ir);
  //Serial.print("Full:"); Serial.println(full);
  //Serial.print("Vis:"); Serial.println(full - ir);
  Serial.print("Lux:"); Serial.println(tsl.calculateLux(full, ir), 1);
  //Serial.println();
}

void sen0193()              // Soil moisture sensor function
{
 // read soil moisture sensor data
 Soil = analogRead(A0);
 Serial.println(Plant);
 
 // report soil moisture sensor values 
 String drySensor = dry + Soil;
 String happySensor = happy + Soil;
 String soakedSensor = soaked + Soil;
 
 if(Soil > Water && Soil < (Water + phase))
 {
   Serial.println(soakedSensor);
 }
 else if(Soil > (Water + phase) && Soil < (Air - phase))
 {
   Serial.println(happySensor);
 }
 else if(Soil < Air && Soil > (Air - phase))
 {
   Serial.println(drySensor);
 } 
}

void dht22()            // Air temp & humidity sensor function
{
    delay(sensorTime);  // Delay to stabilize sensor, optimize data output, minimize energy use 
   
    hum = dht.readHumidity();                   // Get Humidity value
    tempC= dht.readTemperature();               // Get Temperature value in C
    //tempF= (tempC*(1.8))+32;
    
  // Send results to Serial Monitor
    Serial.print("Hum % "); Serial.println(hum);      //Serial.print("  ");
    
    Serial.print("Temp °C "); Serial.println(tempC);  //Serial.print("  ");
    
    //Serial.print("Temp °F "); Serial.print(tempF);  //Serial.print(" ");                   
}

void SDcard()          // SD card function 
{
  logfile = SD.open("Plant.txt", FILE_WRITE);   // open and name file for sensor data to be saved to the SD card
  
  //logfile.print(Plant);
  //logfile.print(',');
    
  DateTime now = rtc.now();                       // connect to RTC 
  logfile.print(now.year(), DEC);                 // write RTC data to SD card
  logfile.print(',');
  logfile.print(now.month(), DEC);
  logfile.print(',');
  logfile.print(now.day(), DEC);
  logfile.print(',');
  logfile.print(Days[now.dayOfTheWeek()]);
  logfile.print(',');
  logfile.print(now.hour(), DEC);
  logfile.print(':');
  logfile.print(now.minute(), DEC);
  logfile.print(':');
  logfile.print(now.second(), DEC);
  logfile.print(',');  

  uint32_t lum = tsl.getFullLuminosity();        // connect to light sensor 
  uint16_t ir, full;
  ir = lum >> 16;
  full = lum & 0xFFFF;                              
  logfile.print("IR");                           
  logfile.print(','); 
  logfile.print(ir);                             // write light data to SD card
  logfile.print(','); 
  logfile.print("Full"); 
  logfile.print(','); 
  logfile.print(full); 
  logfile.print(','); 
  logfile.print("Vis"); 
  logfile.print(','); 
  logfile.print(full - ir); 
  logfile.print(','); 
  logfile.print("Lux"); 
  logfile.print(','); 
  logfile.print(tsl.calculateLux(full, ir), 1);  
  logfile.print(',');  
  
  Soil = analogRead(A0);                         // connect to soil moisture sensor
  logfile.print("Soil");
  logfile.print(','); 
  logfile.print(Soil);                           // write soil moisture data to SD card
  logfile.print(',');   

  hum = dht.readHumidity();                      // connect to air temp and humidity sensor
  tempC= dht.readTemperature();                   
  tempF= (tempC*(1.8))+32;
  logfile.print("Hum %");
  logfile.print(',');                        
  logfile.print(hum);                            // write air humidity value to SD card
  logfile.print(',');   
  logfile.print("Temp C");
  logfile.print(','); 
  logfile.print(tempC);                         // write air temp value in C to SD card
  logfile.print(',');
  //logfile.print("Temp F");
  //logfile.print(',');    
  //logfile.print(tempF);                      // write air temp value in F to SD card
  logfile.println("");                           
  
  logfile.close();                            //  close the sensor data file
}

void BlueTooth()
{
    ble.println(Plant); 
    ble.println();  
    ble.println(Soil);
    //ble.println();         
    ble.println(hum);                            
    //ble.println();
    ble.println(tempF);
    ble.println();           
}    

void blinky()
{
   Soil = analogRead(A0);
   //Serial.println(Plant);

     if(Soil < Air && Soil > (Air - phase))
     {
       digitalWrite(arcadeLED, HIGH);   // Voltage HIGH, LED on
       delay(blinkySpeed);              // wait 
       digitalWrite(arcadeLED, LOW);    // Voltage LOW, LED off
       delay(blinkySpeed); 
       //Serial.println("thirsty!");
     }
     else
     {
       Serial.println("ok!");    
     }
}
