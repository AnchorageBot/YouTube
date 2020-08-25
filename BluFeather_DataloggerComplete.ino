/*
 *   This sketch will print (serial monitor), log (SD card), and broadcast (BLE) data from a TSL2591 sensor, a SEN0193 sensor, a DHT22 sensor, 
 *   and a RTC/SD card shield/Adalogger Featherwing every 60 seconds via a Feather 32u4 BLE MCU, the Arduino IDE 1.8.10
 *   & Adafruit Bluefruit app
 *   
 *   This sketch must have lines carefully & selectively commented out in order to fit/meet the 28672 byte memory limitations of the 32u4 BLE MCU
 *     Current sketch uses 28612 bytes (99%) of program storage space and global variables use 1693 bytes of dynamic memory
 *
 *   TSL2591 Digital Light Sensor 
 *   https://learn.adafruit.com/adafruit-tsl2591
 *   SCL to I2C Clock
 *   SDA to I2C Data
 *   VCC to 3.3-5V DC
 *   GND to ground
 *   
 *   SEN0193
 *   https://www.dfrobot.com/product-1385.html
 *   A0 to (A)  
 *   VCC to (+)
 *   GND to (-)
 *   
 *   DHT22
 *   https://www.adafruit.com/product/393
 *   D9 to (OUT)
 *   VCC to (+)
 *   GND to (-)
 *   
 *   RTC/SD Card Shield/Adalogger Featherwing
 *   https://www.adafruit.com/product/2922
 *   
 *   Terminal Block Breakout
 *   https://www.adafruit.com/product/2926
 *   
 *   32u4 BLE (Bluefruit) Feather MCU                                
 *   https://www.adafruit.com/product/2829               
 *   
 *   Engineering 
 *     Development by Adafruit & DFrobot
 *     Modified by ATS
 *       https://www.youtube.com/channel/UCDuWq2wFqeVII1KC7grySRg
 *       https://github.com/AnchorageBot
 *   
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

//#if SOFTWARE_SERIAL_AVAILABLE        // Load library for multiple serial connections
  //#include <SoftwareSerial.h>
//#endif                               // Used to terminate a multiple line if command

// === Gobal constants and variables ============

int sensorTime = 60000;              // Calibration & output delay for all sensors, 60000 millisec = 60 sec

// Light sensor TSL2591 
Adafruit_TSL2591 tsl = Adafruit_TSL2591(2591);  // Store light values 

// Soil humidity sensor SEN0193
const int Air = 520;              // Adjust max Air value as neccessary (520 original)
const int Water = 260;            // Adjust min Water value as neccessary (260 original)
int phase = (Air - Water)/3;   
int Soil = 0;                     // Set initial sensor reading to 0 
String dry = "Thirsty ";                  // dry range: 430 to 520
String happy = "Happy ";                  // happy range: 350 to 430
String soaked = "Soaked ";                // soaked range: 260 to 350

// Air temperature & humidity sensor DHT22
#define DHTPIN A5                // DHT-22 sensor uses analog pin A5 to communicate data
#define DHTTYPE DHT22            // DHT 22 sensor type is AM2302
float hum;                       // Store humidity in percent
float tempC;                     // Store temperature in Celcius
float tempF;                     // Store temperature in Fahrenheit
DHT dht(DHTPIN, DHTTYPE);        // Initialize DHT sensor

// RTC/SD Card Shield / Adalogger
RTC_PCF8523 rtc;
char Days[7][12] = {"Sun", "Mon", "Tues", "Wed", "Thurs", "Fri", "Sat"};

#define cardSelect 10            // Adalogger uses pin 10 to communicate data with 32u4 pin 33 for ESP32      
File logfile;                    // Data object sensor data is written to

// BlueTooth (BLE) broadcasting/commo
String BROADCAST_NAME = "Berry32u4";
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
  
  // Changing the integration time gives timelines for low or bright light situtations
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

//=== Main code here, runs/loops repeatedly=====

void loop()
{
  pcf8523();
  tsl2591();
  sen0193();   
  dht22();   
  SDcard();
  BlueTooth();
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
  //Serial.print("IR:"); Serial.print(ir);  Serial.print("  ");
  Serial.print("Full:"); Serial.print(full); Serial.print("  ");
  //Serial.print("Vis:"); Serial.print(full - ir); Serial.print("  ");
  Serial.print("Lux:"); Serial.println(tsl.calculateLux(full, ir), 1);
  //Serial.println();
}

void sen0193()              // Soil moisture sensor function
{
 // read soil moisture sensor data
 Soil = analogRead(A0);
 
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
 //Serial.println(" "); 
}

void dht22()            // Air temp & humidity sensor function
{
    delay(sensorTime);  // Delay to stabilize sensor, optimize data output, minimize energy use 
   
    hum = dht.readHumidity();                   // Get Humidity value
    tempC= dht.readTemperature();               // Get Temperature value
    tempF= (tempC*(1.8))+32;
    
  // Send results to Serial Monitor
  
    Serial.print("Hum % "); Serial.print(hum);       //Serial.print("  ");
    
    Serial.print("Temp °C "); Serial.print(tempC);  //Serial.print("  ");
    
    //Serial.print("Temp °F "); Serial.print(tempF);  //Serial.print(" ");
    
    Serial.println(" ");                     
}

void SDcard()          // SD card function 
{
  logfile = SD.open("BluData.txt", FILE_WRITE);   // open and name file for sensor data to be saved to the SD card
    
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
  logfile.print(tempC);                           // write air temp value in C to SD card
  logfile.print(',');
  logfile.print("Temp F");
  logfile.print(',');    
  logfile.print(tempF);                          // write air temp value in F to SD card
  logfile.println("");                           
  
  logfile.close();                               //  close the sensor data file
}

void BlueTooth()
{
    ble.print(Soil);
    ble.print(",");
    ble.print(tempF);
    //ble.print(',');        
    //ble.print(hum);                            
    //ble.print(',');
    //ble.print(full); 
    //ble.print(',');    
    ble.println();
}    
