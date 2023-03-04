/*
  
Observe & report distances via ultrasound on serial monitor
Materials Schedule
  Arduino Uno (or Yun) - 1 each
   https://store.arduino.cc/usa/arduino-uno-rev3
  DF Robot Gravity I/O Shield - 1 each 
   https://www.dfrobot.com/product-1009.html
  HC-SR04 Ultrasonic Range Finder
   https://www.adafruit.com/product/4007
  A-B Cable - 1 each
   https://www.staples.com/usb+ab+cable/directory_usb+ab+cable 
  Wire Bundles - 4 female/female wires 
   https://www.adafruit.com/product/266
 
  Check Arduino-Laptop connection via Arduino IDE
   1.Tools->Board->Arduino Genuino Uno or Arduino Yun 
   2.Tools->Port->Arduino Genuino Uno or Arduino Yun
 
 Assembly
   1.Connect A-B cable to arduino and laptop and upload sketch    
   2.Connect aurduino and shield
   3.Connect HC-SR04 sensor to I/O shield digital pins 10 & 11 with (4) female/female wires
      Sensor (Trig) I/O Shield pin 11 (D)
      Sensor (Echo) I/O Shield pin 10 (D)      
      Sensor (+)    I/O Shield pin 10 (VCC) Voltage
      Sensor (-)    I/O Shield pin 10 (GND) Ground
      
   4.Open serial monitor to view sensor readings at 9600 baud   
  Engineering
  
    DroneBot Workshop 2017
     http://dronebotworkshop.com
     
    ATS
     https://www.youtube.com/channel/UCDuWq2wFqeVII1KC7grySRg
     https://github.com/AnchorageBot          
     03-2019 
  
*/

// === Libraries ==========================

// Check Arduino IDE -> Tools -> Manage Libraries -> Type -> Installed
   // Ensure that Adafruit Unified Sensor Library is installed

#include <Adafruit_Sensor.h>

// === Gobal constants and variables =======

// HC-SR04 sensor constants 
#define trigPin 11  // I/O shield D11
#define echoPin 10  //I/O shield D10

// HC-SR04 sensor variables
float duration, distance;

// === Setup code here, runs once =========================

void setup() {

  // Setup the serial monitor for data analysis & debugging
  Serial.begin (9600);  
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

// === Main code here, runs/loops repeatedly ==============

void loop() {
   
  // Pulse to the HC-SR04 Trigger Pin
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Measure the response from the HC-SR04 Echo Pin
 
  duration = pulseIn(echoPin, HIGH);
  
  // Determine distance from duration
  // Use 343 metres per second as speed of sound
  
  distance = (duration / 2) * 0.0343;
  
  // Send results to Serial Monitor

  Serial.print("Distance = ");
  if (distance >= 400 || distance <= 2) {
     Serial.println("Out of range");
  }
  else {
    Serial.print(distance);
    Serial.println(" cm");
    delay(500);
  }
  delay(500);
}
