/*

  This script/sketch will use a Arduino Nano 33 BLE Sense to share air temp, humidity, & pressure sensor data
  via BLE radio (functions as a BLE peripheral) or via serial cable/termial using Arduino 1.8.13

  Sketch uses 309344 bytes (31%) of program storage space.
    Maximum is 983040 bytes.
  Global variables use 71792 bytes (27%) of dynamic memory, leaving 190352 bytes for local variables.
    Maximum is 262144 bytes.
  Sketch uses 309344 bytes (31%) of program storage space.
    Maximum is 983040 bytes.
  Global variables use 71792 bytes (27%) of dynamic memory, leaving 190352 bytes for local variables.
    Maximum is 262144 bytes.

  Materials Schedule
    Hardware
      Arduino Nano 33 BLE Sense
      https://store.arduino.cc/usa/nano-33-ble-sense-with-headers

    Software
      Arduino IDE
        https://www.arduino.cc/en/main/software
      Adafruit Bluefruit LE Connect App for Mobile
        https://learn.adafruit.com/bluefruit-le-connect
      nRF Connect App for Mobile
        https://www.nordicsemi.com/Software-and-tools/Development-Tools/nRF-Connect-for-mobile
      LightBlue App for Mobile
        https://punchthrough.com/testing-bluetooth-low-energy-devices/
      Wireless Gecko App
        https://apps.apple.com/us/app/wireless-gecko/id1315784335

   Assembly
     1.Update Arduino software
       a.Tools->Board->Boards Manager->Arduino nRF528x mbed Core
       b.Tools->Board->Arduino NANO 33 BLE
       c.Tools-Port->/dev/cu.usbmodem14101 (Arduino NANO 33 BLE)
       d.Sketch->Include Library->Add .ZIP Library (HTS221, LPS22HB, and APDS9960 from Sandeep Mistry's github)
         or
         Tools -> Manage Libraries (HTS221, LPS22HB, and APDS9960)
     2.Attach Cerberus USB Cable to Nano and Laptop or Raspberry Pi
     3.Verify/compile & upload program to NANO 33 BLE Sense
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

      Klaus K
       Arduino Forum - Nano 33 IoT and BLE Sense connections
       https://forum.arduino.cc/index.php?topic=706375.0

      Garry Stafford
        https://itnext.io/ble-and-gatt-for-iot-2ae658baafd5
        https://github.com/garystafford/iot-ble-demo/blob/master/combo_sensor_ble/combo_sensor_ble.ino

      Bluetooth low energy Advertising, a beginner's tutorial by Nordic Semi
        https://devzone.nordicsemi.com/nordic/short-range-guides/b/bluetooth-low-energy/posts/ble-advertising-a-beginners-tutorial

      Norwegian Creations
        Using millis() instead of delay
        https://www.norwegiancreations.com/2017/09/arduino-tutorial-using-millis-instead-of-delay/

      ATS Code Repository and How-to Videos
        https://github.com/AnchorageBot/YouTube
        https://www.youtube.com/channel/UCDuWq2wFqeVII1KC7grySRg/featured
        October 2020

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


BLEService environmentService("181A");                         // standard Environmental Sensing BLE service
// https://www.arduino.cc/en/Reference/ArduinoBLEBLEServiceBLEService

BLEIntCharacteristic tempCharacteristic("2A6E",                // standard 16-bit Temperature characteristic
                                        BLERead | BLENotify);  // remote clients can read and get updates
BLEUnsignedIntCharacteristic humidCharacteristic("2A6F",       // unsigned 16-bit Humidity characteristic
                                        BLERead | BLENotify);  // remote clients can read and get updates
BLEUnsignedIntCharacteristic pressCharacteristic("2A6D",       // unsigned 32-bit Pressure characteristic
                                        BLERead | BLENotify);  // remote clients can read and get updates
// https://www.arduino.cc/en/Reference/ArduinoBLEBLECharacteristicBLECharacteristic

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

  BLE.setAdvertisedService(environmentService);                 // Advertise environment service
  environmentService.addCharacteristic(tempCharacteristic);     // Add temperature characteristic
  environmentService.addCharacteristic(humidCharacteristic);    // Add humidity characteristic
  environmentService.addCharacteristic(pressCharacteristic);    // Add pressure characteristic
  BLE.addService(environmentService);                           // Add environment service

  //BLE.advertise();                                              // Start advertising BLE peripheral
                                                                  // PeripheralBLE() function handles this task

  // set initial values for the characteristics
  tempCharacteristic.writeValue( 0 );
  humidCharacteristic.writeValue( 0 );
  pressCharacteristic.writeValue( 0 );
}

//=== Main code, runs/loops repeatedly==========

void loop() {
                                 // Either
  //delay(sensorTime);                                        // crude sensor calibration & output delay timer
                                 // Or
  nonBlockingTimer();                                         // refined sensor calibration & output delay timer

                                 // Either
  hts221serial();                                             // temp & humidity data via serial
  lps22HBserial();                                            // pressure data via serial
                                 // Or
  //PeripheralSerial();                                       // BLE Peripheral status via serial
  //CentralSerial();                                          // BLE Central status via serial

                                 // All
  PeripheralBLE();                                            // BLE Peripheral advertising
  CentralBLE();                                               // BLE Central connection
                                                              //   func provides temp & humidity data via BLE radio
                                                              //   func provides pressure data via BLE radio
}

//===Timer function ==============================

void nonBlockingTimer() {                                    // code runs while “waiting" for event
  unsigned long time_now = 0;
  int period = 1000;
  if(millis() >= time_now + period){                         // ensures that the loop runs as often as we want, regardless of the execution time
        time_now += period;
        //Serial.println("Hello");                           // uncomment to test if function works
  }
}

//===Serial functions ===========================

void hts221serial() {                                         // print HTS221 temp & humidty data via serial terminal
  float temperature = HTS.readTemperature();                  // read standard 16-bit temp sensor
  float humidity    = HTS.readHumidity();                     // read unsigned 16-bit humidity sensor
  float tempF = (temperature*(1.8))+32;                       // float vs uint16_t, https://os.mbed.com/handbook/C-Data-Types
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

void lps22HBserial() {                                        // print LPS22HB pressure data via serial terminal
  float pressure = BARO.readPressure();                       // read LPS22HB pressure sensor
  float psi = pressure/6.895;                                 // uint_32_t vs float https://os.mbed.com/handbook/C-Data-Types
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

void PeripheralSerial() {
    Serial.print("Peripheral device MAC: ");
    Serial.println(BLE.address());
    Serial.println("Waiting for connections...");
}

void CentralSerial() {
    BLEDevice central = BLE.central();                       // Wait for a BLE central to connect
    if (central) {                                           // if central connects
    Serial.print("Connected to central MAC: ");
    Serial.println(central.address());                       // print central's address via serial terminal
    digitalWrite(LED_BUILTIN, HIGH);                         // turn on the LED

    while (central.connected()){                             // keep looping while connected
      nonBlockingTimer();}
    digitalWrite(LED_BUILTIN, LOW);                          // when the central disconnects, turn off the LED
    Serial.print("Disconnected from central MAC: ");
    Serial.println(central.address());
    Serial.println();
  }
}

//===BLE functions ==============================

void hts221ble() {                                            // HTS221 temp & humidty data via BLE radio
  float temperature = HTS.readTemperature();                  // read HTS221 temp sensor
  float humidity    = HTS.readHumidity();                     // read HTS221 humidty sensor
  float tempF = (temperature*(1.8))+32;                       // uint16_t vs float https://os.mbed.com/handbook/C-Data-Types
  nonBlockingTimer();

  int previousTemperature = 0;
   if (temperature != previousTemperature) {                  // If temperature reading has changed
        tempCharacteristic.writeValue(temperature);           // advertise temperature (2A6E) via BLE
                                                              // https://www.arduino.cc/en/Reference/ArduinoBLEBLECharacteristicwriteValue
        previousTemperature = temperature;    }               // Save value

  unsigned int previousHumidity = 0;
   if (humidity != previousHumidity) {                       // If humidity reading has changed
        humidCharacteristic.writeValue(humidity);            // advertise humidity (2A6F) via BLE
        previousHumidity = humidity;    }                    // Save value
}

void lps22HBble() {                                           // LPS22HB pressure data via BLE radio
    float pressure = BARO.readPressure();                     // read LPS22HB pressure sensor
    float psi = pressure/6.895;                               // uint_32_t vs float https://os.mbed.com/handbook/C-Data-Types
    float hg = pressure/3.386;
    nonBlockingTimer();

   unsigned int previousPressure = 0;
   if (pressure != previousPressure) {                       // If pressure reading has changed
        pressCharacteristic.writeValue(pressure);            // advertise pressure (2A6D) via BLE
        previousPressure = pressure;    }                    // Save value
}

void PeripheralBLE() {
    BLE.advertise();                                          // Start advertising BLE peripheral
}

void CentralBLE() {
  BLEDevice central = BLE.central();                          // Wait for a BLE central to connect
  if (central) {                                              // if central connects
     digitalWrite(LED_BUILTIN, HIGH);                         // turn on the LED
     while (central.connected()) {                            // keep looping while connected
       nonBlockingTimer();
       hts221ble();
       lps22HBble();
       }
     digitalWrite(LED_BUILTIN, LOW);                          // when the central disconnects, turn off the LED
  }
}
