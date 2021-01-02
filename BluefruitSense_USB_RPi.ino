/* This sketch will allow a Adafruit Bluefruit Sense to communicate with a RPi 0 or RPi 3B+
 *  without using the Arduino IDE
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
 */ 

 const int ledPin = 4;
 // const int ledPin = 13;

 void setup()
 {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
 }

 void loop()
 {
  Serial.println("Hello Pi");
  if (Serial.available())
  {
    flash(Serial.read() - '0');
  }
  delay(1000);
 }

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
