/********************************
Observe & report temp & humidity
  
 Materials Schedule

  Arduino Uno (or Yun) - 1 each
   https://store.arduino.cc/usa/arduino-uno-rev3
  DF Robot Gravity I/O Shield - 1 each 
   https://www.dfrobot.com/product-1009.html
  DHT22 AM2302 Temperature and Humidity Sensor - 1 each
   https://www.adafruit.com/product/393
  A-B Cable - 1 each
   https://www.staples.com/usb+ab+cable/directory_usb+ab+cable 
  Wire Bundles - 3 female/female wires 
   https://www.adafruit.com/product/266

 Check Arduino-Laptop connection via Arduino IDE

   1.Tools->Board->Arduino Genuino Uno or Arduino Yun 
   2.Tools->Port->Arduino Genuino Uno or Arduino Yun
 
 Materials Assembly

   1.Connect A-B cable to arduino and laptop and upload sketch    
   2.Connect aurduino and shield
   3.Connect temp & humidty sensor to I/O shield digital pin 10 with (3) female/female wires

      Sensor (Out) I/O Shield pin 10 (D)
      Sensor (+)   I/O Shield pin 10 (VCC) Voltage
      Sensor (-)   I/O Shield pin 10 (GND) Ground
      
   4.Open serial monitor to view sensor readings at 9600 baud   

  Engineering

   DroneBot Workshop 2017
    https://dronebotworkshop.com/hc-sr04-ultrasonic-distance-sensor-arduino/
   
   ATS 
     https://www.youtube.com/channel/UCDuWq2wFqeVII1KC7grySRg
     https://github.com/AnchorageBot   
     2019-03
   
*******************************/

// === Libraries ==========================

// Check Arduino IDE -> Tools -> Manage Libraries -> Type -> Installed
   // Ensure that Adafruit Unified Sensor Library is installed
   // Ensure that Adafruit AM2320 Sensor Library is installed
   // Ensure that DHT Sensor Library is installed 

#include <DHT_U.h>
#include <Adafruit_Sensor.h> 
#include <DHT.h>; // Call DHT22 Library

// === Gobal constants and variables =======

// Temp & Humidity Sensor Constants
#define DHTPIN 10       // DHT-22 sensor & I/O shield D10
#define DHTTYPE DHT22   // DHT 22 sensor type is AM2302

// Temp & Humidity Sensor Variables
float hum;    // Stores humidity value in percent
float temp;   // Stores temperature value in Celcius

DHT dht(DHTPIN, DHTTYPE); // Initialize DHT sensor for 16mhz Arduino

// === Setup code here, runs once =========================

void setup() {

  // Setup the serial monitor for data analysis & debugging
  Serial.begin (9600);
  
  // Start the DHT sensor
  dht.begin();
}

// === Main code here, runs/loops repeatedly ==============

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
