/*
   
  This script will use a Arduino Nano 33 BLE as BLE peripheral with a simple Hello World 
  advertising/greeting service that can be viewed on a mobile phone

  Arduino Nano 33 BLE
    https://store.arduino.cc/usa/nano-33-ble

  nRF Connect App for Mobile
    https://www.nordicsemi.com/Software-and-tools/Development-Tools/nRF-Connect-for-mobile

  Adafruit Bluefruit LE Connect App for Mobile
    https://learn.adafruit.com/bluefruit-le-connect

  LightBlue App for Mobile
    https://punchthrough.com/testing-bluetooth-low-energy-devices/
  
  Adapted from Arduino BatteryMonitor example by OkDo
    https://www.okdo.com/project/get-started-with-arduino-nano-33-ble/

  Bluetooth low energy Advertising, a beginner's tutorial by Nordic Semi
    https://devzone.nordicsemi.com/nordic/short-range-guides/b/bluetooth-low-energy/posts/ble-advertising-a-beginners-tutorial

  ATS Code Repository and How-to Videos
       https://www.youtube.com/channel/UCDuWq2wFqeVII1KC7grySRg
       https://github.com/AnchorageBot
  
*/

#include <ArduinoBLE.h>

static const char* greeting = "Hello World!";

BLEService greetingService("180C");  // User defined service

BLEStringCharacteristic greetingCharacteristic("2A56",  // standard 16-bit characteristic UUID
    BLERead, 13); // remote clients will only be able to read this

void setup() {
  Serial.begin(9600);    // initialize serial communication
  while (!Serial);

  pinMode(LED_BUILTIN, OUTPUT); // initialize the built-in LED pin

  if (!BLE.begin()) {   // initialize BLE
    Serial.println("starting BLE failed!");
    while (1);
  }

  BLE.setLocalName("Nano33BLE");  // Set name for connection
  BLE.setAdvertisedService(greetingService); // Advertise service
  greetingService.addCharacteristic(greetingCharacteristic); // Add characteristic to service
  BLE.addService(greetingService); // Add service
  greetingCharacteristic.setValue(greeting); // Set greeting string

  BLE.advertise();  // Start advertising
  Serial.print("Peripheral device MAC: ");
  Serial.println(BLE.address());
  Serial.println("Waiting for connections...");
}

void loop() {
  BLEDevice central = BLE.central();  // Wait for a BLE central to connect

  // if a central is connected to the peripheral:
  if (central) {
    Serial.print("Connected to central MAC: ");
    // print the central's BT address:
    Serial.println(central.address());
    // turn on the LED to indicate the connection:
    digitalWrite(LED_BUILTIN, HIGH);

    while (central.connected()){} // keep looping while connected
    
    // when the central disconnects, turn off the LED:
    digitalWrite(LED_BUILTIN, LOW);
    Serial.print("Disconnected from central MAC: ");
    Serial.println(central.address());
  }
}
