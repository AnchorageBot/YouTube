/*

  This script uses the Portenta as a BLE peripheral that blinks the onboard LED 
  when connected to a central BLE device (iPad, iPhone)

  Materials Schedule
   (1 each) Arduino Portenta
     https://store.arduino.cc/usa/portenta-h7

     Radio Module Murata 1DX dual WiFi 802.11b/g/n 65 Mbps and Bluetooth 5.1 BR/EDR/LE
     https://content.arduino.cc/assets/Arduino-Portenta-H7_Datasheet_Murata-1dx.pdf
     
   (1 each) Amazon Basics USB C to USB A Short Cable
     https://www.amazon.com/AmazonBasics-Type-C-USB-Male-Cable/dp/B01GGKYN0A


  Software Schedule
   (1 each) Arduino IDE
    https://www.arduino.cc/en/Main/software
  
   (1 each) Light Blue BLE Cell Phone App
     https://punchthrough.com/lightblue-features/
       
  Assembly
   1.Update Arduino software
     a.Tools->Board->Boards Manager->Arduino Mbed Enabled Boards->Update
   2.Attach USB Cable to both Portenta and Laptop
   3. Use Arduino IDE to Select Board and Port  
     a.Tools->Board->Arduino Mbed OS Boards (nRF52840/STM32H747)->Arduino Portenta H7 (M7 Core)
     b.Tools-Port->/dev/cu.usbmodem14101 (Arduino Portenta H7 (M7 Core))   
   4.Use Arduino IDE to Verify/compile & upload program to Portenta
     a.Sketch->Verify/Compile
     b.Sketch->Upload
   5. Download BLE App onto iPad or iPhone & Scan for BLE Peripheral
     a. nRF Connect or Bluefruit or Light Blue
     b. Scan for "Arduino" or "Portenta BLE"     

  Engineering
   Arduino 
     File->Examples->ArduinoBLE->Peripheral->LED  
     
     Portenta H7 Tutorials
       https://www.arduino.cc/pro/tutorials/portenta-h7
       
     Portenta H7 BLE Tutorial
       https://www.arduino.cc/pro/tutorials/portenta-h7/por-ard-ble
     
     Getting Started with Arduino Products
       https://www.arduino.cc/en/Guide/NANO33BLESensehttps://www.arduino.cc/en/Guide
     
   Sandeep Mistry's Github
       https://github.com/sandeepmistry
     
   BCMI Labs, Lenard George, Sebastian Hunkeler Github
       https://github.com/bcmi-labs/arduino-pro-content
     
   ATS, October 2020
       https://github.com/AnchorageBot/YouTube
       https://youtu.be/SN3pJCTnTL8
     
*/

#include <ArduinoBLE.h>
//https://www.arduino.cc/en/Reference/ArduinoBLE
//https://github.com/arduino-libraries/ArduinoBLE

BLEService ledService("19B10000-E8F2-537E-4F6C-D104768A1214"); // BLE LED Service

// BLE LED Switch Characteristic - custom 128-bit UUID, read and writable by central
BLEByteCharacteristic switchCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);

const int ledPin = LEDG; // pin to use for the onboard LED
int timerLED = 500;

void setup() {
  Serial.begin(9600);
  // comment out when using a wall connection in lieu of a computer connection
  while (!Serial);

  // boots the Portenta's M4 core
  //LL_RCC_ForceCM4Boot();
  
  // set LED pin to output mode
  pinMode(ledPin, OUTPUT);

  // begin initialization
  if (!BLE.begin()) {
    Serial.println("starting BLE failed!");

    while (1);
  }

  // set advertised local name and service UUID:
  BLE.setLocalName("Portenta BLE");
  BLE.setAdvertisedService(ledService);

  // add the characteristic to the service
  ledService.addCharacteristic(switchCharacteristic);

  // add service
  BLE.addService(ledService);

  // set the initial value for the characeristic:
  switchCharacteristic.writeValue(0);

  // start advertising
  BLE.advertise();

  Serial.println("Portenta BLE Peripheral");
}

void blink()  // Blink the onboard LED
{
  digitalWrite(ledPin, HIGH);   // turn the LED on 
  delay(timerLED);                       
  digitalWrite(ledPin, LOW);    // turn the LED off 
  delay(timerLED);                       
}

void loop() {
  // listen for BLE peripherals to connect:
  BLEDevice central = BLE.central();

  // if a central is connected to peripheral:
  if (central) {
    Serial.print("Connected to central: ");
    // print the central's MAC address:
    Serial.println(central.address());


    // while the central is still connected to peripheral:
    while (central.connected()) {
      blink();
    }

    // when the central disconnects, print it out:
    Serial.print(F("Disconnected from central: "));
    Serial.println(central.address());
  }
}
