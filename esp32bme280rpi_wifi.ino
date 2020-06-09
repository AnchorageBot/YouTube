/*

This script uses a ESP32 Feather to read humidity, pressure, temperature, & altitude from the BME280 sensor over I2C and broadcast data via Wifi to a Raspberry Pi 4

Hardware connections:
  BME280 -> ESP32 Feather
  GND -> GND
  3.3 -> 3.3
  SDA -> A4
  SCL -> A5

BME280 Breakout Board Hardware
    Nathan Seidle
    SparkFun Electronics
    Date: March 9th, 2018
    License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license)
    https://www.sparkfun.com/products/13676 
    https://github.com/sparkfun/SparkFun_BME280_Arduino_Library
  
Adafruit ESP32 Feather Huzzah Hardware
    Lady Ada
    https://learn.adafruit.com/adafruit-huzzah32-esp32-feather?view=all  

WiFi Webserver Code
    Peter Dalmaris
    https://github.com/futureshocked/ESP32-For-Busy-People-1/blob/master/10-060_Web_server/10-060_Web_server.ino
  
Raspberry 4 Hardware & Code
    https://www.adafruit.com/product/4564

    Update RPi Commands
      sudo apt-get update
      sudo apt-get upgrade
      sudo reboot

    Wifi Connection Commands for RPi4, MacBook, and ESP32
      VNC (RPi4 to MacBook connection)
        VNC Server->Options->Security
          Encryption->Prefer On
          Authentication->VNC Password
      VNC (MacBook to RPi4 connection)
        Finder->Command K
          Connect to server->vnc://xxx.xxx.xxx.xxx
          Screen sharing requires a password->password
      Terminal (RPi4 to ESP32 Feather connection)
        curl http://xxx.xxx.xxx.xxx >> data.txt
        cat data.txt
      
Engineering fusion
    Anchorage Tech Solutions June 2020
    https://www.youtube.com/channel/UCDuWq2wFqeVII1KC7grySRg/featured?view_as=subscriber
    https://github.com/AnchorageBot

*/

// === Libraries ================================
#include <Wire.h>                 // Load I2/TWC library
#include "SparkFunBME280.h"
#include <WiFi.h>

// === Gobal constants and variables ============
BME280 mySensor;

const int led_gpio = 2;

const char* ssid     = "xxxx";
const char* password = "xxxx";
WiFiServer server(80);

//=== Setup code here, runs once ================

void setup()
{
  Serial.begin(115200);
  Serial.println("Reading basic values from BME280");

  //Begin communication with BME280 over I2C
  Wire.begin();  
  if (mySensor.beginI2C() == false) 
  {
    Serial.println("The sensor did not respond. Please check wiring.");
    while(1); //Freeze
  }

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("...waiting to connect...");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

int value = 0;

//=== Main code here, runs/loops repeatedly=====
void loop()
{
  BME280();
  
  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Refresh: 5");
            client.println();
            client.println("<!DOCTYPE HTML>");
            client.println("<html>");

            // the content of the HTTP response follows the header:
            client.print("<p>Click <a href=\"/H\">here</a> to turn the LED on pin ");
            client.print(led_gpio);
            client.print(" on.</p>");
            client.print("<p>Click <a href=\"/L\">here</a> to turn the LED on pin ");
            client.print(led_gpio);
            client.print(" off.</p>");
            client.print("<hl>");
            client.print("<p>Temperature: ");
            client.print(mySensor.readTempF());
            client.print(" &deg; F </p>");
            client.print("<p>Humidity: ");
            client.print(mySensor.readFloatHumidity());
            client.println(" % R.H. </p>");
            client.println("</html>");
            client.print("<p>Pressure: ");
            client.print(mySensor.readFloatPressure());
            client.println(" Pa</p>");
            client.println("</html>");
            client.print("<p>Altitude: ");
            client.print(mySensor.readFloatAltitudeFeet());
            client.println(" ft</p> ");
            client.println("</html>");            

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /H")) {
          digitalWrite(led_gpio, HIGH);               // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(led_gpio, LOW);                // GET /L turns the LED off
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}

//========= Functions ===========================
void BME280()
{
  Serial.print("Humidity: ");
  Serial.print(mySensor.readFloatHumidity(), 0);

  Serial.print(" Pressure: ");
  Serial.print(mySensor.readFloatPressure(), 0);

  Serial.print(" Alt: ");
  //Serial.print(mySensor.readFloatAltitudeMeters(), 1);
  Serial.print(mySensor.readFloatAltitudeFeet(), 1);

  Serial.print(" Temp: ");
  //Serial.print(mySensor.readTempC(), 2);
  Serial.print(mySensor.readTempF(), 2);

  Serial.println();

  delay(5000);
}  
