*
 
  This script will use a Arduino Nano 33 BLE to share air temp, humidity, & pressure sensor data
  via BLE radio (functions as a BLE peripheral) or via serial cable

  Materials Schedule  
    Arduino Nano 33 BLE
      https://store.arduino.cc/usa/nano-33-ble
    Adafruit Bluefruit LE Connect App for Mobile
      https://learn.adafruit.com/bluefruit-le-connect  
    nRF Connect App for Mobile
      https://www.nordicsemi.com/Software-and-tools/Development-Tools/nRF-Connect-for-mobile
    LightBlue App for Mobile
      https://punchthrough.com/testing-bluetooth-low-energy-devices/

   Assembly
     1.Update Arduino software
       a.Tools->Board->Boards Manager->Arduino nRF528x mbed Core
       b.Tools->Board->Arduino NANO 33 BLE
       c.Tools-Port->/dev/cu.usbmodem14101 (Arduino NANO 33 BLE)
       d.Sketch->Include Library->Add .ZIP Library (HTS221, LPS22HB, and APDS9960 from Sandeep Mistry's github) 
         or 
         Tools -> Manage Libraries (HTS221, LPS22HB, and APDS9960)
     2.Attach Cerberus USB Cable to Nano and Laptop or Raspberry Pi
     3.Verify/compile & upload program to NANO 33 BLE
       a.Sketch->Verify/Compile
       b.Sketch->Upload   

   Engineering
     Arduino
       https://www.arduino.cc/en/Guide/NANO33BLESense
         revised 2019/08/17 by SM  
      
     Sandeep Mistry 
       https://github.com/arduino-libraries/Arduino_HTS221
         July 2019 
       https://github.com/arduino-libraries/Arduino_LPS22HB
         July 2019
       https://github.com/arduino-libraries/Arduino_APDS9960
         August 2019
  
      Monica Houston
        https://create.arduino.cc/projecthub/monica/getting-started-with-bluetooth-low-energy-ble-ab4c94
      
      Garry Stafford
        https://itnext.io/ble-and-gatt-for-iot-2ae658baafd5

      Leonardo Cavagnis
        https://github.com/leonardocavagnis/SmartThermostat_ArduinoBLE/blob/master/SmartThermostat_sketch/SmartThermostat_sketch.ino        
      
      Arduino BatteryMonitor example by OkDo
        https://www.okdo.com/project/get-started-with-arduino-nano-33-ble/
  
      Bluetooth low energy Advertising, a beginner's tutorial by Nordic Semi
        https://devzone.nordicsemi.com/nordic/short-range-guides/b/bluetooth-low-energy/posts/ble-advertising-a-beginners-tutorial
        
      ATS Code Repository and How-to Videos
        https://github.com/AnchorageBot/YouTube
        https://www.youtube.com/channel/UCDuWq2wFqeVII1KC7grySRg/featured
  
*/

// === Libraries ================================

#include <ArduinoBLE.h>
// BLE Library
// https://www.arduino.cc/en/Reference/ArduinoBLE
// https://github.com/arduino-libraries/ArduinoBLE

#include <Arduino_HTS221.h>
// air temp & humidty sensor library
// https://www.arduino.cc/en/Reference/ArduinoHTS221
// https://github.com/arduino-libraries/Arduino_HTS221  

#include <Arduino_LPS22HB.h>
// air pressure sensor library
// https://www.arduino.cc/en/Reference/ArduinoLPS22HB
// https://github.com/arduino-libraries/Arduino_LPS22HB

// === Gobal constants and variables ============

int sensorTime = 3000;               // sensor calibration & output delay, 60000 millisec = 60 sec

//BLEService greetingService("180C");                            // user defined BLE service

//BLEStringCharacteristic greetingCharacteristic("2A56",         // standard 16-bit Greeting characteristic UUID
//                                        BLERead, 13);          // remote clients can read 
//static const char* greeting = "Arduino Nano 33 BLE Sense";                                        


BLEService environmentService("181A");                         // standard Environmental Sensing BLE service

BLEIntCharacteristic tempCharacteristic("2A6E",                // standard 16-bit Temperature characteristic
                                        BLERead | BLENotify);  // remote clients can read and get updates 
BLEUnsignedIntCharacteristic humidCharacteristic("2A6F",       // unsigned 16-bit Humidity characteristic
                                        BLERead | BLENotify);  // remote clients can read and get updates 
BLEUnsignedIntCharacteristic pressCharacteristic("2A6D",       // unsigned 32-bit Pressure characteristic
                                        BLERead | BLENotify);  // remote clients can read and get updates                                                                                   

//=== Setup code here, runs once ================

void setup() {
  Serial.begin(9600);                                          // initialize serial communication
  while (!Serial);                                             // uncomment for laptop use & comment for wall wart use

  pinMode(LED_BUILTIN, OUTPUT);                                // initialize built-in LED pin

  if (!BLE.begin()) {                                          // initialize NINA B306 BLE radio
    Serial.println("BLE failure!");
    while (1);
  }

      if (!HTS.begin()) {                                      // initialize HTS221 sensor
        Serial.println("temp & humidity sensor failure!");
        while (1);
    }

    if (!BARO.begin()) {                                      // initialize LPS22HB sensor
        Serial.println("pressure sensor failure!");
        while (1);
    }

    BARO.readPressure();                                      // Avoid barometer sensor bug
    delay(sensorTime);                                        // https://forum.arduino.cc/index.php?topic=660360.0
  

  BLE.setLocalName("Nano33BLEsense");                           // Set name for connection
  
  //BLE.setAdvertisedService(greetingService);                  // Advertise greeting service
  //greetingService.addCharacteristic(greetingCharacteristic);  // Add characteristic to service
  //BLE.addService(greetingService);                            // Add service
  //greetingCharacteristic.setValue(greeting);                  // Set greeting string

  BLE.setAdvertisedService(environmentService);                 // Advertise environment service
  environmentService.addCharacteristic(tempCharacteristic);     // Add temperature characteristic
  environmentService.addCharacteristic(humidCharacteristic);    // Add humidity characteristic
  environmentService.addCharacteristic(pressCharacteristic);    // Add pressure characteristic  
  BLE.addService(environmentService);                           // Add environment service  

  BLE.advertise();                                              // Start advertising
  //Serial.print("Peripheral device MAC: ");
  //Serial.println(BLE.address());
  //Serial.println("Waiting for connections...");
}

//=== Main code, runs/loops repeatedly==========

void loop() {

  delay(sensorTime);                                          // sensor calibration & output delay

  //hts221();                                                 // uncomment for laptop use   
  float temperature = HTS.readTemperature();                  // read HTS221 temp & humidty sensor for BLE
  float humidity    = HTS.readHumidity();
  float tempF = (temperature*(1.8))+32;
  tempCharacteristic.writeValue(temperature);                 // advertise temperature (2A6E) via BLE
  humidCharacteristic.writeValue(humidity);                   // advertise humidity (2A6F) via BLE 
  
  // https://www.arduino.cc/en/Reference/ArduinoBLEBLECharacteristicwriteValue
  // https://www.arduino.cc/en/Reference/ArduinoBLEBLECharacteristicreadValue    
  // https://www.arduino.cc/en/Reference/ArduinoBLEBLEDescriptorread                  

  lps22HB();                                                 // uncomment for laptop use
  //float pressure = BARO.readPressure();                     // read LPS22HB pressure sensor for BLE
  //float psi = pressure/6.895;
  //float hg = pressure/3.386;
  //pressCharacteristic.writeValue(pressure);                 // Advertise pressure (2A6D) via BLE    

  //bleSerial();                                            // uncomment for laptop use
  BLEDevice central = BLE.central();                          // Wait for a BLE central to connect
  if (central) {                                              // if central connects
     digitalWrite(LED_BUILTIN, HIGH);                         // turn on the LED   
     while (central.connected()){}                            // keep looping while connected  
     digitalWrite(LED_BUILTIN, LOW);                          // when the central disconnects, turn off the LED                
  }

}

//===Sensor functions ===========================

void hts221() {                                               // print HTS221 temp & humidty data via serial terminal
  float temperature = HTS.readTemperature();                  // read HTS221 temp & humidty sensor
  float humidity    = HTS.readHumidity();
  float tempF = (temperature*(1.8))+32;
  Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.print(" °C  ");
  Serial.print(tempF);
  Serial.println(" °F");

  Serial.print("Humidity    = ");
  Serial.print(humidity);
  Serial.println(" %");
  Serial.println(); 
}

void lps22HB() {                                              // print LPS22HB pressure data via serial terminal
  float pressure = BARO.readPressure();                       // read LPS22HB pressure sensor 
  float psi = pressure/6.895;
  float hg = pressure/3.386;
  Serial.print("Pressure = ");                              
  Serial.print(pressure);
  Serial.print(" kPa  ");
  Serial.print(psi);
  Serial.print(" psi  ");
  Serial.print(hg);
  Serial.println(" inches of mercury");
  Serial.println();   
}  

//===BLE functions ==============================

void bleSerial() {
    BLEDevice central = BLE.central();                       // Wait for BLE central to connect
    if (central) {                                           // if central connects
    Serial.print("Connected to central MAC: ");
    Serial.println(central.address());                       // print central's address via serial terminal
    digitalWrite(LED_BUILTIN, HIGH);                         // turn on the LED

    while (central.connected()){}                            // keep looping while connected
    
    digitalWrite(LED_BUILTIN, LOW);                          // when the central disconnects, turn off the LED
    Serial.print("Disconnected from central MAC: ");
    Serial.println(central.address());
    Serial.println();     
  }
}
