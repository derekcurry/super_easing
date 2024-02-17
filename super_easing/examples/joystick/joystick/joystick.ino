/* ***** Super Easer *********************************

  *** Joystick demo *****

  Servo easing library without using an Arduino delay 

  You can control:
  - the speed of movement
  - Max, Min, Mid points of the servo
  - 30 different easing options (10 types, 3 motions for each type)

  Febuary 2024
  by Derek Curry
  Released under the GPLv3 license (Do anything you like except distribute closed source versions)

  * Based on the Arduino easing functions by T-K-233: 
  * https://github.com/T-K-233/Arduino-Servo-Easing-Demo
  * And easing equations by Andrey Sitnik and Ivan Solovev
  * https://easings.net/ 

  ***** easing type options ******
  - Cubic: "cubic"
  - Quadratic:"quadratic"
  - Quartic: "quartic"
  - Quintic:"quintic"
  - Sine: "sine"
  - Circular: "circular"
  - Exponential: "exponential"
  - Elastic: "elastic"
  - Overshoot: "overshoot"
  - Bounce: "bounce"

  ***** easing motion options ******
  ease-out:    0 
  ease-in:     1
  ease-in-out: 2

***********************************************/

#include <super_easing.h>
// Variables for not using a delay()
// For a thorough explaination of this see: https://learn.adafruit.com/multi-tasking-the-arduino-part-1/ditch-the-delay
unsigned long lastGlobalUpdate;
long globalUpdateInterval = 5;

// This code assumes that you are using a switch-based joystick
// Joystick pins 
#define RIGHT_PIN 2
#define LEFT_PIN 3
#define UP_PIN 4
#define DOWN_PIN 5

// Direction variables
int left;
int right;
int up;
int down;

// Initialize the Easer (one for each servo)
Easer my_servo_1(5, "cubic", 0);
Easer my_servo_2(5,"quadratic", 1);
/*****************************************************************
    Easer class vairables:
      (interval, type-of-easing, easing-motion, min-servo-position, max-servo-position, servo-midpoint)
    interval is required (controls speed), all other variables are optional
    The lower the speed-interval number, the faster the movement
    The exact min, max, and midpoint can vary from servo to servo
    The default easing type is: cubic if no variable is given
    The default easing motion is: ease-out if no variable is given
*******************************************************************/

void setup() { 
  Serial.begin(115200);
  
  my_servo_1.Attach(12);  // Attach the servo to pin 9  ***Any pin capable of PWM can be used
  my_servo_2.Attach(11);
  //*** Notice the capital 'A' in "Attach"

  // Joystick pins
  pinMode(LEFT_PIN, INPUT_PULLUP);
  pinMode(RIGHT_PIN, INPUT_PULLUP);
  pinMode(UP_PIN, INPUT_PULLUP);
  pinMode(DOWN_PIN, INPUT_PULLUP);
} 
 
// *** Using an Arduino delay() function will break the program, use update intervals
void loop() { 
  
  // Use a global update variable to avoid using a delay()
  if ((millis() - lastGlobalUpdate) >= globalUpdateInterval) {
    lastGlobalUpdate = millis();
    //Serial.println("Still Running....");
    
    left = digitalRead(LEFT_PIN); 
    right = digitalRead(RIGHT_PIN);
    up = digitalRead(UP_PIN);
    down = digitalRead(DOWN_PIN);

    /* 
      Change the dest of the servo depending on the joystick
      Servos move to the midpoint if no direction is pressed
    */ 
    // ---- Left & Right----
    if((left==1)&&(right==1)) {
      // Go to center
      Serial.print(" center ");
      my_servo_1.dest = my_servo_1.sMid;
    } else {
      if(left==0){
        Serial.print(" left ");
        my_servo_1.dest = my_servo_1.sMax;
      } else {
        Serial.print(" right ");
        my_servo_1.dest = my_servo_1.sMin;
      }
    }
    // ---- Up & Down----
    if((up==1)&&(down==1)){
      // Go to the middle
      Serial.print(" middle ");
      my_servo_2.dest = my_servo_2.sMid;
    } else {
      if(up==0){
        Serial.print(" up ");
        my_servo_2.dest = my_servo_2.sMax;
      } else {
        Serial.print(" down ");
        my_servo_2.dest = my_servo_2.sMin;
      }
    }
    Serial.println();
  } // end of global timer loop

  // You must update each servo for them to move
  my_servo_1.Update();
  my_servo_2.Update();

}