/* 
  
 This sketch provides the current date and time using Arduino IDE 1.8.10
 Materials Schedule
   (1 each) Arduino Nano 33 IoT
   (1 each) Adafruit Real Time Clock (RTC) PCF8523
   (1 each) Coin cell lithium battery type CR1220
   (1 each) Sparkfun Cerberus USB cable 
   (4 each) 22 AWG Wires
 Assembly 
 
  Wire up the Nano IoT 33 pins to the PCF8523 pins    (Connected via I2C and Wire lib)
                       A4      ->     SDA
                       A5      ->     SCL
                       GND     ->     GND
                       3V3     ->     VCC
  Connect Cerberus Cable to Laptop and Arduino Nano
  Check for Arduino Libraries using Arduino IDE
   Tools  -> Manage Libraries
    Check for presence of/install RTClib by Adafruit
  Execute Adruino Commands using Arduino IDE
   File   -> Save
   Sketch -> Verify Compile
  Insert coin cell battery into the PCF8523 with the + side facing out
  Execute Arduino Commands
   Sketch -> Upload
   Tools  -> Serial Monitor (verify setting/adjust to 57600 baud)  
 Engineering
  Adafruit 
    https://learn.adafruit.com/adafruit-pcf8523-real-time-clock?view=all#rtc-with-arduino
  ATS 
    https://www.youtube.com/channel/UCDuWq2wFqeVII1KC7grySRg
    https://github.com/AnchorageBot
    12/2019        
Reference
  Unix Time
   https://en.wikipedia.org/wiki/Unix_time         
*/

#include "RTClib.h"

RTC_PCF8523 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup () {

  while (!Serial) {
    delay(1);  // for Leonardo/Micro/Zero
  }

  Serial.begin(57600);
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (! rtc.initialized()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
     //  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 11, 3, 0, 0));
  }
}

void loop () {
    DateTime now = rtc.now();

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

    Serial.print(" since midnight 1/1/1970 = "); // Start of Unix time 
    Serial.print(now.unixtime());
    Serial.print("s = ");
    Serial.print(now.unixtime() / 86400L);
    Serial.println("d");

    Serial.println();
    delay(3000);
}
