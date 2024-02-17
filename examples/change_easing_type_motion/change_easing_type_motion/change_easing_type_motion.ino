/* ***** Super Easer *********************************

  *** Change easing type and motion demo *****

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
long globalUpdateInterval = 5000;

// Array of easing types
char easings[][32] = {"cubic", "quadratic", "quartic", "quintic", "sine"};
int type = 0;
int movement = 0;
// Initialize the Easer (one for each servo)
Easer my_servo(5, "cubic", 2);
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
  
  my_servo.Attach(9);  // Attach the servo to pin 9
  // *** Notice the capital 'A' in "Attach"
  // Any pin capable of PWM can be used
} 


// *** Using an Arduino delay() function will break the program, use update intervals
void loop() { 
  // Use a global update variable to avoid using a delay()
  if((millis() - lastGlobalUpdate) > globalUpdateInterval) {
    if(my_servo.dest == my_servo.sMax) {
      my_servo.dest = my_servo.sMin;
    } else {
      my_servo.dest =my_servo.sMax;
      // Loop through the easing types
      if(type < 4) {
        type += 1;
      } else {
        type = 0;
        if(movement < 2){
          movement += 1;
        } else {
          movement = 0;
        }
      }
      //Serial.println(easings[type]);
      strcpy(my_servo.ease_type, easings[type]);  // Assign the new easing type
      my_servo.motion = movement; // Assign the motion type (1: ease-in, 2: ease-out, 3: ease-in-out)

      
      Serial.print(my_servo.ease_type);
      Serial.print(" ");
      Serial.print(my_servo.motion);
      Serial.print(" ");
      if(movement == 0) {
        Serial.println("ease out");
      } else if (movement == 1) {
        Serial.println("ease in");
      } else {
        Serial.println("ease-in-out");
      }
    
    }
    lastGlobalUpdate = millis();
  }
  // You must call the servo Update() function for it to move
  my_servo.Update();

}