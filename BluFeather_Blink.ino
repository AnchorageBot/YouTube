/***
  Blink - Turns an onboard LED on and off repeatedly.

  Materials Schedule
   (1) Adafruit Feather 32u4 Bluefruit LE with stacking headers
     https://learn.adafruit.com/adafruit-feather-32u4-bluefruit-le?view=all#overview
   (1) Sparkfun Cerberus USB Cable
     https://www.sparkfun.com/products/12016
       
  Assembly
   1.Update Arduino software
     a.Arduino->Preferences->Additional Boards URL->https://adafruit.github.io/arduino-board-index/package_adafruit_index.json
     b.Tools->Boards Manager->Contributed->Adafruit AVR Boards
     c.Tools->Board->Adafruit Feather 32u4
     d.Tools-Port->/dev/cu.usbmodem1D11201 (Adafruit Feather 32u4)
   2.Attach Cerberus USB Cable to Feather and Laptop
   3.Verify/compile & upload program to Feather
     a.Sketch->Verify/Compile
     b.Sketch->Upload  
     
  Engineering
   Arduino  
     http://www.arduino.cc/en/Tutorial/Blink
     modified 8 May 2014 by Scott Fitzgerald
     modified 2 Sep 2016 by Arturo Guadalupi
     modified 8 Sep 2016 by Colby Newman
   ATS
     https://www.youtube.com/channel/UCDuWq2wFqeVII1KC7grySRg
     https://github.com/AnchorageBot
     modified August 2019
  
***/

// === Gobal constants and variables ============

 long BlinkTime = 250;           // milliseconds of on/off time

//=== Setup code here, runs once ================

void setup() {

  pinMode(LED_BUILTIN, OUTPUT); // use onboard LED for blinking
}

//=== Main code here, runs/loops repeatedly=====

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on 
  delay(BlinkTime);                       
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off 
  delay(BlinkTime);                       
}
