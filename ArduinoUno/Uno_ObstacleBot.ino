/*
 * This script creates an obstacle avoidance robot
 * 
 * Materials Schedule
 *   (1 each) Arduino Uno
 *   (1 each) DF Robot L298P Motor Shield v1.3
 *   (1 each) Adafruit two wheel alumuminum robot chassis 
 *   (1 each) Sparkfun Cerberus USB cable
 *   (1 each) HC-SR04 Ultrasound sensor and mounting bracket
 *   (1 each) 5V battery charger for a cell phone
 *   (8 each) 22 AWG female/male wires
 *   
 * Assembly  
 *   1. Two wheel alumuminum robot chassis
 *     a. Screw motors to lower chassis
 *     b. Screw upper chassis to lower chassis
 *     c. Screw HC-SR04 mounting bracket to upper chassis
 *     d. Insert HC-SR04 sensor to mounting bracket
 *     e. Velcro Arduino to upper chassis
 *     f. Insert 5V battery charger in gap between upper & lower chassis
 *   2. Arudino <-> L289P Shield connection
 *     a. Arduino Barrel Jack location facing you & on your right side
 *     b. L289P Shield Analog In 5 pin facing away & on your right side
 *     c. Press L289P Shield onto Arduino
 *   3. L289P Shield <-> Motor connections  
 *     a. M1- Shield Pin -> Right Motor via Black wire   
 *     b. M1+ Shield Pin -> Right Motor via Red wire
 *     c. M2+ Shield Pin -> Left Motor via Red wire
 *     d. M2- Shield Pin -> Left Motor via Black wire
 *   4. L289P Shield <-> HC-SR04 sensor connections    
 *     a. Digital Pin 13 -> Echo
 *     b. Digital Pin 10 -> Trig 
 *     c. Power Pin 5V  -> VCC
 *     d. Power Pin GND -> GND
 *   5. L289P Shield <-> Jumper Connections   
 *     a. PWM Pin M2
 *     b. PWM Pin E2
 *     c. PWM Pin E1
 *     d. PWM Pin M1
 *   6. Arduino Software Prep
 *     a. Arduino->Preferences->Check for Updates on Startup 
 *     b. Tools -> Manage Libraries -> Type -> Installed
 *     c. Tools -> Board -> Arduino/Genuino Uno
 *     d. Tools -> Port -> Arduino/Genuino Uno
 *     e. Sketch -> Verify/Compile
 *   7. Laptop <-> Arduino Uno connection  
 *     a. Attach Cerberus USB cable to laptop and arduino uno
 *     b. Arduino Software -> Sketch -> Verify/Compile
 *     c. Arduino Software -> Sketch -> Upload
 *     
 * Engineering    
 *   DroneBot Workshop http://dronebotworkshop.com
 *     DFRobot https://wiki.dfrobot.com/Arduino_Motor_Shield__L298N___SKU_DRI0009_
 *   
 *   ATS
     https://www.youtube.com/channel/UCDuWq2wFqeVII1KC7grySRg
     https://github.com/AnchorageBot   
 */

//--------Libraries--------       
#include <NewPing.h>      

//--------Global constants and variables--------

// L298P Shield Control Pins - Uses Phase Locked Loop (PLL) Speed Control
int E1 = 4; 
int M1 = 5; 
int M2 = 6; 
int E2 = 7;  

// HCSR04 Control Pins & Max sensor distance ~ 250 cm
#define TRIGGER_PIN  10  
#define ECHO_PIN     13  
#define MAX_DISTANCE 250 

// NewPing setup of pins and maximum distance
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); 

// Key variables baseline
boolean goesForward = false;
int distance = 100;

// Delay timers
int calibrationDelay = 2000;
int moveDelay = 200;
int rangeDelay = 100;
int pauseDelay = 50;
int turnDelay = 60;

//--------Setup--------

void setup()
{
  // Set L298P Shield Pins as Output
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  
  // Calibrate HCSR04 Sensor 
  delay(calibrationDelay);              
  distance = readPing();    
  delay(rangeDelay);               
  distance = readPing();
  delay(rangeDelay);
  distance = readPing();
  delay(rangeDelay);
  distance = readPing();
  delay(rangeDelay);  
}

//--------Main program--------

void loop()
{  
  int distanceRight = 0; 
  int distanceLeft = 0;
  delay(pauseDelay);

  distance = readPing();

    if (distance <= 20)
    {

      moveStop();
      delay(moveDelay);
      moveBackward();
      moveBackward();
      delay(moveDelay);      

      distanceRight = lookRight();
      delay(rangeDelay);
      distanceLeft = lookLeft();
      delay(rangeDelay);      

        if (distanceRight >= distanceLeft)
        {
          turnRight();
          turnRight();
          delay(moveDelay);
          moveStop();
          delay(moveDelay);

          moveForward;
        }
        else 
        {
          turnLeft();
          turnLeft();
          delay(moveDelay);
          moveStop();
          delay(moveDelay);

          moveForward();
        }
    }
    
    else
    {
      moveForward; 
    }
      
    moveForward(); 
}

//--------Functions--------

// Read Ultrasonic Sensor Ping Function 
int readPing()      
{
  delay(rangeDelay);                 // Wait 100ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  int cm = sonar.ping_cm();   //Send ping, get ping distance in centimeters (cm).
  if (cm==0)
  {
    cm=250;
  }
  return cm;
}

// Look Right Function
int lookRight()
{ 
  turnRight();
  delay(moveDelay);  
  int distance = readPing();
  delay(rangeDelay);  
  turnLeft();
  return distance;
}

// Look Left Function
int lookLeft()
{
  turnLeft();
  delay(moveDelay);
  int distance = readPing();
  delay(rangeDelay);
  turnRight();
  delay(moveDelay);  
  return distance;  
}

// Move Stop Function
void moveStop()       
{
  digitalWrite(M1, LOW);
  digitalWrite(M2, LOW);
  analogWrite(E1, 127);
  analogWrite(E2, 127);
  delay(turnDelay);
}

// Move Forward Function
void moveForward()    
{
  digitalWrite(M1, HIGH);
  digitalWrite(M2, HIGH);
  analogWrite(E1, 128);
  analogWrite(E2, 127);
  delay(turnDelay);
}

// Move Backward Function
void moveBackward()   
{
  digitalWrite(M1, HIGH);
  digitalWrite(M2, HIGH);
  analogWrite(E1, 127);
  analogWrite(E2, 128);
  delay(turnDelay);
}

// Turn Right Function
void turnRight()      
{
  digitalWrite(M1, HIGH);
  digitalWrite(M2, HIGH);
  analogWrite(E1, 127);
  analogWrite(E2, 127);
  delay(turnDelay);
}

// Turn Left Function
void turnLeft()       
{
  digitalWrite(M1, HIGH);
  digitalWrite(M2, HIGH);
  analogWrite(E1, 128);
  analogWrite(E2, 128);
  delay(turnDelay);
}
