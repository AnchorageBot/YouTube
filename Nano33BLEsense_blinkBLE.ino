/*

  This example creates a BLE peripheral that blinks an LED when connected to a central BLE device (iPad or iPhone)

  Materials Schedule
   (1 each) Arduino Nano 33 BLE Sense
     https://store.arduino.cc/usa/nano-33-ble-sense-with-headers
   (1 each) Sparkfun Cerberus USB Cable
     https://www.sparkfun.com/products/12016
       
  Assembly
   1.Update Arduino software
     a.Tools->Board->Boards Manager->Arduino nRF528x mbed Core
     c.Tools->Board->Arduino NANO 33 BLE
     d.Tools-Port->/dev/cu.usbmodem14101 (Adafruit NANO 33 BLE)
   2.Attach Cerberus USB Cable to Nano and Laptop
   3.Verify/compile & upload program to Nano
     a.Sketch->Verify/Compile
     b.Sketch->Upload
   4. Download BLE App onto iPad or iPhone
     a. nRF Connect or Bluefruit or Light Blue
     b. Scan for "Nano33ble" or "Arduino"      

  Engineering
   https://www.arduino.cc/en/Guide/NANO33BLESense
     revised 2019/08/17 by SM  
   https://github.com/sandeepmistry
     by Sandeep Mistry
   Arduino 
     File->Examples->ArduinoBLE->Peripheral->LED
   Modified
     https://www.youtube.com/channel/UCDuWq2wFqeVII1KC7grySRg
     https://github.com/AnchorageBot   
     September 2019 by ATS
*/

#include <ArduinoBLE.h>

BLEService ledService("19B10000-E8F2-537E-4F6C-D104768A1214"); // BLE LED Service

// BLE LED Switch Characteristic - custom 128-bit UUID, read and writable by central
BLEByteCharacteristic switchCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);

const int ledPin = LED_BUILTIN; // pin to use for the LED
int timerLED = 1000;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  // set LED pin to output mode
  pinMode(ledPin, OUTPUT);

  // begin initialization
  if (!BLE.begin()) {
    Serial.println("starting BLE failed!");

    while (1);
  }

  // set advertised local name and service UUID:
  BLE.setLocalName("Nano33ble");
  BLE.setAdvertisedService(ledService);

  // add the characteristic to the service
  ledService.addCharacteristic(switchCharacteristic);

  // add service
  BLE.addService(ledService);

  // set the initial value for the characeristic:
  switchCharacteristic.writeValue(0);

  // start advertising
  BLE.advertise();

  Serial.println("Nano33ble Peripheral");
}

void blink()  // Blink the onboard LED
{
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on 
  delay(timerLED);                       
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off 
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
