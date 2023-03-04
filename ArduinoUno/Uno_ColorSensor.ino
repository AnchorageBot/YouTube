/***************************************************
  Observe and report an object's visible color spectrum via a TCS3200 light-to-frequency converter
  Materials Schedule
  Arduino Uno - 1 each
   https://store.arduino.cc/usa/arduino-uno-rev3
  DF Robot Gravity I/O Shield - 1 each
   https://www.dfrobot.com/product-1009.html
  DF Robot Color Sensor - 1 each
   https://www.dfrobot.com/product-540.html
  A-B Cable - 1 each
   https://www.staples.com/usb+ab+cable/directory_usb+ab+cable
  Wire Bundles - 7 female/female wires
   https://www.adafruit.com/product/266
  Assembly
   1.Connect aurduino and shield
   2.Connect color sensor to I/O shield digital pins 4, 5, 6, 7, 8 and VCC and GND with (7) female/female wires
      (D)  Digital  D4    Green   S0
      (D)  Digital  D5    Black   S1
      (D)  Digital  D6    Red     S2
      (D)  Digital  D7    White   S3
      (D)  Digital  D8    Yellow  OUT
      (+)  Voltage  VCC   Red     VCC
      (-)  Ground   GND   Black   GND
   3.Connect A-B cable to arduino and laptop and upload sketch
   4.Open serial monitor to view sensor readings at 9600 baud
  Sensor specifications (Texas Advanced Optoelectronic Solutions TCS3200)
    Max output frequency = 600 kHz (1 kHz = 0.001 MHz, 600 kHz = 0.6 MHz)
    Max data acquisition rate = 1 datapoint/microsecond (1,000 microseconds = 1 millisecond)
  Sensor power settings
    Clear:   S2 High  S3 Low
    Red:     S2 Low   S3 Low
    Green:   S2 High  S3 High 
    Blue:    S2 Low   S3 High
   RGB Model
    Clear:  Red 255  Green 255  Blue 255  Clear 0  Hex FFFFFF  https://convertingcolors.com/rgb-color-255_255_255.html
    Red:    Red 255  Green   0  Blue   0  Clear 0  Hex FF0000  https://convertingcolors.com/rgb-color-255_0_0.html
    Green:  Red   0  Green 255  Blue   0  Clear 0  Hex 00FF00  https://convertingcolors.com/rgb-color-0_255_0.html
    Blue:   Red   0  Green   0  Blue 255  Clear 0  Hex 0000FF  https://convertingcolors.com/rgb-color-0_0_255.html
  Web safe color palette 
    Hexadecimal #00 #33 #66 #99 #CC  #FF
    Decimal       0  51 102 153 204  255  
  Color wavelengths (nanometers = nm)
    Red:    640 nm
    Green:  524 nm
    Blue:   470 nm      
  
  Engineering References
    Dejan Nedelkovski
     https://howtomechatronics.com/tutorials/arduino/arduino-color-sensing-tutorial-tcs230-tcs3200-color-sensor/
    Paul McWhorter (Lessons 13, 14a, 14b, 15, 31, and 32)
     http://www.toptechboy.com/arduino-lessons/
    DF Robot
     https://www.dfrobot.com/wiki/index.php/TCS3200_Color_Sensor_(SKU:SEN0101)
    Wiki - Color Difference
     https://en.wikipedia.org/wiki/Color_difference
    Wiki - RGB Model 
     https://en.wikipedia.org/wiki/RGB_color_model  
     
    ATS
      https://www.youtube.com/channel/UCDuWq2wFqeVII1KC7grySRg
      https://github.com/AnchorageBot   
      September 2019  
    
**************************************************/

//=== Libraries =====================================

#include "Math.h" // https://www.arduino.cc/en/math/h
#include "string.h" // https://www.arduino.cc/en/Reference/StringLibrary

//=== Global constants and variables ==================

// Arduino language reference (functions, variables, & structure)
// https://www.arduino.cc/reference/en/

// TCS3200 light->frequency converter to i/o shield wiring assignments
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

// Sensor frequency range = 0 to 600 kHz, pulse width up to 102,400 microseconds
// byte = range of 0 to 255
// int = 16 bit = 2 byte value = range of -32,768 to 32,767
// unsigned int = 32 bit = 4 bytes = 4,294,967,295
unsigned int redFreq = 0;  //
unsigned int greenFreq = 0;  //
unsigned int blueFreq = 0;  //  for Blue photodiodes
unsigned int sensorArray[] = {redFreq, greenFreq, blueFreq};

// Mapping sets for Frequency to RGB Model
// Command Syntax - map(value, fromLow, fromHigh, toLow, toHigh)
// value = redFreq, greenFreq, or blueFreq
int fromLowFreq = 0;
int fromHighFreq = 1000; // try 1000 for bright environment, 10000 for shady environment
int toLowRGB = 0; 
int toHighRGB = 255; // max RGB value

//  Mapping data:  RGBvalue <-> ColorDesignation
int RGBspectrumValues[7][3] = {{0, 0, 0}, {255, 0, 0}, {255, 255, 0}, {0, 255, 5}, {128, 128, 128}, {0, 5, 255}, {255, 255, 255}};
String SpectrumColorDesignation[7] = {"black", "red", "yellow", "green", "grey", "blue", "white"};

int RGBgreenValues[4][3] = {{50, 205, 50}, {0, 255, 0}, {34, 139, 34}, {0, 128, 0}};
String GreenColorDesignation[4] = {"limeGreen", "lime", "forestGreen", "green"};

int RGByellowValues[4][3] = {{250, 250, 210}, {255, 225, 224}, {255, 255, 0}, {255, 215, 0}};
String YellowColorDesignation[4] = {"goldenrodYellow", "light yellow", "yellow", "gold"};

int RGBblueValues[4][3] = {{132, 112, 255}, {0, 0, 205}, {65, 105, 255}, {0, 0, 205}};
String BlueColorDesignation[4] = {"light blue", "medium blue", "royal blue", "gold"};

// Chronometer delay in milliseconds
int delayTimer1 = 1000; 
int delayTimer2 = 500;

//=== Setup code, runs once =========================

void setup()
{

  // TCS3200 light->frequency converter
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  // Set frequency-scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  // Open serial monitor to view sensor readings at 9600 baud
  Serial.begin(9600);

}

//=== Main code, loops endlessly ====================

void loop()
{

  sensorReading();
  amplify();
  printSensorData();

}

//=== Breakout of functions used in void loop ===========================

void sensorReading()
{
  // Turn on Red filtered photodiodes
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  // Read sensor output frequency
  redFreq = pulseIn(sensorOut, LOW); // width of pulse in microseconds
  // Map the RGB Model to the Frequency
  redFreq = map(redFreq, fromLowFreq, fromHighFreq, toLowRGB, toHighRGB);

  // Turn on Green filtered photodiodes
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  // Read sensor output frequency
  greenFreq = pulseIn(sensorOut, LOW); // width of pulse in microseconds
  // Map the RGB Model to the Frequency
  greenFreq = map(greenFreq, fromLowFreq, fromHighFreq, toLowRGB, toHighRGB);

  // Turn on Blue filtered photodiodes
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  // Read sensor output frequency
  blueFreq = pulseIn(sensorOut, LOW); // width of pulse in microseconds
  // Map the RGB Model to the Frequency
  blueFreq = map(blueFreq, fromLowFreq, fromHighFreq, toLowRGB, toHighRGB);
}

void amplify()
{
    if (redFreq > greenFreq && redFreq > blueFreq)
    {
      Serial.println("Sensor sees more Red");     
      delay(delayTimer1);
    }  
    else if (greenFreq > redFreq && greenFreq > blueFreq)
    {
      Serial.println("Sensor sees more Green");
      delay(delayTimer1);
    }
    else if (blueFreq > redFreq && blueFreq > greenFreq)
    {
      Serial.println("Sensor sees more Blue");
      delay(delayTimer1);
    }
}

void printSensorData()
{
  // Print sensor readings
  Serial.print("R = ");
  Serial.print(redFreq);
  Serial.print(" ");
  Serial.print("G = ");
  Serial.print(greenFreq);
  Serial.print(" ");
  Serial.print("B = ");
  Serial.print(sensorArray[2]);
  Serial.print(" ");
  Serial.print("\n\n");
  delay(delayTimer2);
}
