/* ***** Super Easer *********************************

  *** Calibrate the servo *****

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

  Find the min, max, and mid-points for a servo motor
  
  This example follows the Arduino input basics tutorial
  Example 5-Receiving and parsing several pieces of data
  https://forum.arduino.cc/t/serial-input-basics-updated/382007/3

***********************************************/

#include <super_easing.h>
// Variables for not using a delay()
// For a thorough explaination of this see: https://learn.adafruit.com/multi-tasking-the-arduino-part-1/ditch-the-delay
unsigned long lastGlobalUpdate;
long globalUpdateInterval = 5000;

const byte numChars = 32;
char receivedChars[numChars];  
char tempChars[numChars];        // temporary array for use when parsing

// variables to hold the parsed data
char servoPosition[numChars] = {0};
int servoValue = 0;

boolean newData = false;

// Initialize the Easer (one for each servo)
Easer my_servo(5, "cubic");
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
  Serial.println("This demo expects 2 pieces of data - text and an integer");
  Serial.println("Servo callibration options are: min, max, mid.");
  Serial.println("Enter data between < and > markers with a comma like this:");
  Serial.println("<min, 400>  ");
  Serial.println("Default min = 550 | Default max = 2400 | Default mid = 1500 ");
  Serial.println();
  
  my_servo.Attach(9);  // Attach the servo to pin 9 (Any pin capable of PWM can be used)
  // *** Notice the capital 'A' in "Attach" ***
} 

// Useing a global update variable to avoid using a delay()
// *** Using an Arduino delay() function will break the program, use update intervals
void loop() { 
  recvWithStartEndMarkers();
    if (newData == true) {
        strcpy(tempChars, receivedChars);
            // this temporary copy is necessary to protect the original data
            //   because strtok() used in parseData() replaces the commas with \0
        parseData();
        setValue();
        newData = false;
    }
  
  // You must call the servo Update() for it to move
  my_servo.Update();
  
}

//============

void recvWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;

    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();

        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }
        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}

//============

void parseData() {      // split the data into its parts

    char * strtokIndx; // this is used by strtok() as an index

    strtokIndx = strtok(tempChars,",");      // get the first part - the string
    strcpy(servoPosition, strtokIndx); // copy it to servoPosition
 
    strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
    servoValue = atoi(strtokIndx);     // convert this part to an integer
}

//============

void setValue() {

    if (strcmp(servoPosition,"min")==0) {
      Serial.print("setting servo min: ");
      Serial.println(servoValue);
      my_servo.sMin = servoValue;
      my_servo.dest = my_servo.sMin;  // Set the new dest
    } else if (strcmp(servoPosition,"max")==0) {
      Serial.print("setting servo max: ");
      Serial.println(servoValue);
      my_servo.sMax = servoValue;
      my_servo.dest = my_servo.sMax; // Set the new dest
    } else if (strcmp(servoPosition,"mid")==0) {
      Serial.print("setting servo mid: ");
      Serial.println(servoValue);
      my_servo.sMid = servoValue;
      my_servo.dest = my_servo.sMid;  // Set the new dest
    } else {

      Serial.print("servo position ");
      Serial.print(servoPosition); 
      Serial.println(" not recognized. ");
      Serial.println("please use min, max, or mid");
    }

}