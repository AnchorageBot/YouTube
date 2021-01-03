/* This sketch will allow a Adafruit Bluefruit Sense to communicate with a RPi 0 or RPi 3B+
 * & transmit temp, pressure, and altitude data (BMP280 sensor) without using the Arduino IDE
 *  
 * Materials Schedule
 *  Adafruit Bluefruit Sense
 *    https://www.adafruit.com/product/4516
 *  USB A to Micro B Cable 
 *    https://www.adafruit.com/product/592 
 *  RPi Zero
 *    https://www.adafruit.com/product/3400 
 *
 *Engineering 
 *  Programming the Raspberry Pi, 2nd Edition, by Simon Monk
 *    Location 1704 of 2697
 *  Adafruit Bluefruit Sense Tutorial
 *    https://learn.adafruit.com/adafruit-feather-sense/pinouts
 *      Blue LED is located on pin D4
 *      NeoPixel is located on pin D8 
 *      Red LED is located on pin D13
 *  ATS YouTube & Github tutorials
 *    https://www.youtube.com/channel/UCDuWq2wFqeVII1KC7grySRg/videos
 *    https://github.com/AnchorageBot/YouTube
 */ 

// Prep for temperature, barometric pressure, and altitude
#include <Adafruit_BMP280.h>
Adafruit_BMP280 bmp280;     
float temperature, pressure, altitude;

// Prep for LED
const int ledPin = 4;
// const int ledPin = 13;

 void setup()
 {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  bmp280.begin();  
 }

 void loop() // void loop(void)
 {  
  
  temperature = bmp280.readTemperature();
  pressure = bmp280.readPressure();
  altitude = bmp280.readAltitude(1013.25);

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");
  Serial.print("Barometric pressure: ");
  Serial.print(pressure);
  Serial.println(" Pa");
  Serial.print("Altitude: ");
  Serial.print(altitude);
  Serial.println(" m");
  delay(1000);  

  // Listen for RPi query
  if (Serial.available())
  {
    flash(Serial.read() - '0');  
  }
  delay(1000);
}    

  // Allow RPi to blink Bluefeather LED X5
 void flash(int n) 
{
  for (int i = 0; i < n; i++)
  {
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
    delay(500);
  }  
} 
