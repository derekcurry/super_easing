/* ***** Super Easer *********************************

  *** change speed demo *****

  Servo easing library without using an Arduino delay 

  You can control:
  - the speed of movement
  - Max, Min, Mid points of the servo
  - 30 different easing options (10 types, 3 motions for each type)

  Febuary 2024 / Updated November 2024
  by Derek Curry
  Released under the GPLv3 license (Do anything you like except distribute closed source versions)

  * Based on the Arduino easing functions by T-K-233: 
  * https://github.com/T-K-233/Arduino-Servo-Easing-Demo
  * And easing equations by Andrey Sitnik and Ivan Solovev
  * https://easings.net/ 

  ***** easing type options ******
  - CUBIC
  - QUADRATIC
  - QUARTIC
  - QUINTIC
  - SINE
  - CIRCULAR
  - EXPONENTIAL
  - ELASTIC
  - OVERSHOOT
  - BOUNCE

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

// Variable for the servo speed:
int servo_speed = 1;
// Initialize the Easer (one for each servo)
Easer my_servo(servo_speed, CUBIC, 2);

void setup() { 
  Serial.begin(115200);
  
  my_servo.Attach(9);  // Attach the servo to pin 9
  // *** Notice the capital 'A' in "Attach"
  // Any pin capable of PWM can be used
  
} 
 
 
void loop() { 
  // Use a global update variable to avoid using a delay()
  if((millis() - lastGlobalUpdate) > globalUpdateInterval) {
    if(my_servo.dest == my_servo.sMax) {
      my_servo.dest = my_servo.sMin;
      // slow the servo down by increasing the update interval --> reset at 20
      if(servo_speed < 20){
        servo_speed += 1;
      } else {
        servo_speed = 1;
      }
      my_servo.updateInterval = servo_speed;
      Serial.println(servo_speed);
    } else {
      my_servo.dest = my_servo.sMax;
      // slow the servo down by increasing the update interval --> reset at 20
      if(servo_speed < 20){
        servo_speed += 1;
      } else {
        servo_speed = 1;
      }
      my_servo.updateInterval = servo_speed;
      Serial.println(my_servo.updateInterval);
    }
    lastGlobalUpdate = millis();
    
  }
  // You must update the servo for it to move
  my_servo.Update();

}
