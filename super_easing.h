#ifndef SUPER_EASING_H
#define SUPER_EASING_H

#include <Arduino.h>
#include <Servo.h> 

// ---- Easer class -----
class Easer {

  #define CUBIC 1
  #define QUADRATIC 2
  #define QUARTIC 3
  #define QUINTIC 4
  #define SINE 5
  #define CIRCULAR 6
  #define EXPONENTIAL 7
  #define ELASTIC 8
  #define OVERSHOOT 9
  #define BOUNCE 10

  Servo servo;          // the servo
  int pos = 1000;       // current servo position 
  int startPos;         // Where the movement is starting from
  int increment;        // increment to move for each interval
  unsigned long lastUpdate; // last update of position
  int prevDest;
  
  // ********  Easing option functions  ***********
  // Quadratic -------------------------------------------------------------------
  float easeInQuadratic(float x) { 
    return pow(x, 2); // Modeled after the parabola y = x^2
  }
  float easeOutQuadratic(float x) { // Ease out Quadratic
    return -(x * (x - 2)); // Modeled after the parabola y = -x^2 + 2x
  }
  float easeInOutQuadratic(float x) {
    // Modeled after the piecewise quadratic
    // y = (1/2)((2x)^2)             ; [0, 0.5)
    // y = -(1/2)((2x-1)*(2x-3) - 1) ; [0.5, 1]
    return (x < 0.5) ? (2 * pow(x, 2)) : ((-2 * pow(x, 2)) + (4 * x) - 1);
  }
  // -----------------------------------------------------------------------------
  // Cubic -----------------------------------------------------------------------
  float easeInCubic(float x) {
    return pow(x, 3); // Modeled after the cubic y = x^3
  }
  float easeOutCubic(float x) {
    return pow(x - 1, 3) + 1; // Modeled after the cubic y = (x - 1)^3 + 1
  }
  float easeInOutCubic(float x) { // Ease in and out Cubic
    return (x < 0.5) ? (4 * pow(x, 3)) : (0.5 * pow(((2 * x) - 2), 3) + 1);
    // Modeled after the piecewise cubic
    // y = (1/2)((2x)^3)       ; [0, 0.5)
    // y = (1/2)((2x-2)^3 + 2) ; [0.5, 1]
  }
  // ------------------------------------------------------------------------------
  // Quartic ----------------------------------------------------------------------
  float easeInQuartic(float x) {
    return pow(x, 4); // Modeled after the quartic x^4
  }
  float easeOutQuartic(float x) {
    return pow(x - 1, 3) * (1 - x) + 1; // Modeled after the quartic y = 1 - (x - 1)^4
  }
  float easeInOutQuartic(float x) {
    return (x < 0.5) ? (8 * pow(x, 4)) : (-8 * pow(x - 1, 4) + 1); 
    // Modeled after the piecewise quartic
    // y = (1/2)((2x)^4)        ; [0, 0.5)
    // y = -(1/2)((2x-2)^4 - 2) ; [0.5, 1]
  }
  // ------------------------------------------------------------------------------
  // Quintic ----------------------------------------------------------------------
  float easeInQuintic(float x) {
    return pow(x, 5); // Modeled after the quintic y = x^5
  }
  float easeOutQuintic(float x) {
    return pow(x - 1, 5) + 1; // Modeled after the quintic y = (x - 1)^5 + 1
  }
  float easeInOutQuintic(float x) {
    return (x < 0.5) ? (16 * pow(x, 5)) : (0.5 * pow((2 * x) - 2, 5) + 1);
    // Modeled after the piecewise quintic
    // y = (1/2)((2x)^5)       ; [0, 0.5)
    // y = (1/2)((2x-2)^5 + 2) ; [0.5, 1]
  }
  // ------------------------------------------------------------------------------
  // Sine wave easing; sin(p * PI/2) ----------------------------------------------
  float easeInSine(float x) {
    return sin((x - 1) * M_PI_2) + 1; // Modeled after quarter-cycle of sine wave
  }
  float easeOutSine(float x) {
    return sin(x * M_PI_2); // Modeled after quarter-cycle of sine wave (different phase)
  }
  float easeInOutSine(float x) {
    return 0.5 * (1 - cos(x * M_PI)); // Modeled after half sine wave
  }
  // ------------------------------------------------------------------------------
  // Circular easing; sqrt(1 - p^2) -----------------------------------------------
  float easeInCircular(float x) {
    return 1 - sqrt(1 - pow(x, 2)); // Modeled after shifted quadrant IV of unit circle
  }
  float easeOutCircular(float x) {
    return sqrt((2 - x) * x); // Modeled after shifted quadrant II of unit circle
  }
  float easeInOutCircular(float x) {
    return (x < 0.5) ? (0.5 * (1 - sqrt(1 - 4 * pow(x, 2)))) : (0.5 * (sqrt(-((2 * x) - 3) * ((2 * x) - 1)) + 1));
    // Modeled after the piecewise circular function
    // y = (1/2)(1 - sqrt(1 - 4x^2))           ; [0, 0.5)
    // y = (1/2)(sqrt(-(2x - 3)*(2x - 1)) + 1) ; [0.5, 1]
  }
  // ------------------------------------------------------------------------------
  // Exponential easing, base 2 ---------------------------------------------------
  float easeInExponential(float x) {
    return (x == 0.0) ? x : pow(2, 10 * (x - 1)); // Modeled after the exponential function y = 2^(10(x - 1))
  }
  float easeOutExponential(float x) {
    return (x == 1.0) ? x : 1 - pow(2, -10 * x); // Modeled after the exponential function y = -2^(-10x) + 1
  }
  float easeInOutExponential(float x) {
    if(x == 0.0 || x == 1.0) return x;
    
    return (x < 0.5) ? (0.5 * pow(2, (20 * x) - 10)) : (-0.5 * pow(2, (-20 * x) + 10) + 1);
    // Modeled after the piecewise exponential
    // y = (1/2)2^(10(2x - 1))         ; [0,0.5)
    // y = -(1/2)*2^(-10(2x - 1))) + 1 ; [0.5,1]
  }
  // ------------------------------------------------------------------------------
  // Elastic ----------------------------------------------------------------------
  float easeInElastic(float x) {
    return sin(13 * M_PI_2 * x) * pow(2, 10 * (x - 1)); // Modeled after the damped sine wave y = sin(13pi/2*x)*pow(2, 10 * (x - 1))
  }
  float easeOutElastic(float x) {
    return sin(-13 * M_PI_2 * (x + 1)) * pow(2, -10 * x) + 1; // Modeled after the damped sine wave y = sin(-13pi/2*(x + 1))*pow(2, -10x) + 1
  }
  float easeInOutElastic(float x) {
    return (x < 0.5) ? 
      (0.5 * sin(13 * M_PI_2 * (2 * x)) * pow(2, 10 * ((2 * x) - 1)))
      : (0.5 * (sin(-13 * M_PI_2 * ((2 * x - 1) + 1)) * pow(2, -10 * (2 * x - 1)) + 2));
      // Modeled after the piecewise exponentially-damped sine wave:
      // y = (1/2)*sin(13pi/2*(2*x))*pow(2, 10 * ((2*x) - 1))      ; [0,0.5)
      // y = (1/2)*(sin(-13pi/2*((2x-1)+1))*pow(2,-10(2*x-1)) + 2) ; [0.5, 1]
  }
  // ------------------------------------------------------------------------------
  // Overshoot --------------------------------------------------------------------
  float easeInBack(float x) {
    return pow(x, 3) - x * sin(x * M_PI); // Modeled after the overshooting cubic y = x^3-x*sin(x*pi)
  }
  float easeOutBack(float x) {
    return 1 - (pow(1 - x, 3) - (1 - x) * sin((1 - x) * M_PI)); // Modeled after overshooting cubic y = 1-((1-x)^3-(1-x)*sin((1-x)*pi))
  }
  float easeInOutBack(float x) {
    return (x < 0.5) ? 
      (0.5 * (pow(2 * x, 3) - 2 * x * sin(2 * x * M_PI)))
      : (0.5 * (1 - (pow((1 - (2 * x - 1)), 3) - (1 - (2 * x - 1)) * sin((1 - (2 * x - 1)) * M_PI))) + 0.5);
      // Modeled after the piecewise overshooting cubic function:
      // y = (1/2)*((2x)^3-(2x)*sin(2*x*pi))           ; [0, 0.5)
      // y = (1/2)*(1-((1-x)^3-(1-x)*sin((1-x)*pi))+1) ; [0.5, 1]
  }
  // ------------------------------------------------------------------------------
  // Bounce -----------------------------------------------------------------------
  float easeInBounce(float x) {
    return 1 - easeOutBounce(1 - x);
  }
  float easeOutBounce(float x) {
    if (x < 1 / 2.75) {
      return 7.5625 * pow(x, 2);
    }
    else if (x < 2 / 2.75) {
      return 7.5625 * pow(x - (1.5 / 2.75), 2) + 0.75;
    }
    else if (x < 2.5 / 2.75) {
      return 7.5625 * pow(x - (2.25 / 2.75), 2) + 0.9375;
    }
    else {
      return 7.5625 * pow(x - (2.625 / 2.75), 2) * x + 0.984375;
    }
  }
  float easeInOutBounce(float x) {
    return (x < 0.5) ? (0.5 * easeInBounce(x * 2)) : (0.5 * easeOutBounce(x * 2 - 1) + 0.5);
  }
  // ------------------------------------------------------------------------------
  
public: 
  int sMin; // Minimum servo rotation
  int sMax; // Max servo rotation
  int sMid; // Midpoint
  int dest;      // final destination of the servo
  float linear = 0;
  float lineUpdate = 0.005;
  int ease_type;  // Easing function to use
  int motion; // 0: out | 1: in | 2: in-out
  int  updateInterval;      // interval between updates

  Easer(int interval=5, int e_type=CUBIC, int m=0, int min=550, int max=2400, int mid=1500) {
    dest = sMid;
    updateInterval = interval;
    increment = 1;
    ease_type = e_type;

    motion = m;
    sMin = min;
    sMax = max;
    sMid = mid;
  }
  
  void Attach(int pin) {
    servo.attach(pin);
  }
  
  void Detach() {
    servo.detach();
  }
  
  void Update() {
    if((millis() - lastUpdate) > updateInterval) {
      lastUpdate = millis();
      //pos += increment;
      if(dest != prevDest){
        startPos = pos;
        prevDest = dest;
        linear = 0;
      }

      if(linear<1){
        linear+=lineUpdate;

        // Increasing *********************************************************
        if(startPos < dest) {
          // Check easing type  ------
          if (ease_type==CUBIC) {  // Cubic -----------------------
            switch (motion) {
              case 0:
                pos = (startPos + (int)(easeOutCubic(linear)*(dest-startPos)));
                break;
              case 1:
                pos = (startPos + (int)(easeInCubic(linear)*(dest-startPos)));
                break;
              case 2:
                pos = (startPos + (int)(easeInOutCubic(linear)*(dest-startPos)));
                break;
            }
          } else if (ease_type==QUADRATIC) {  // Quadratic ----------
            switch (motion) {
              case 0:
                pos = (startPos + (int)(easeOutQuadratic(linear)*(dest-startPos)));
                break;
              case 1:
                pos = (startPos + (int)(easeInQuadratic(linear)*(dest-startPos)));
                break;
              case 2:
                pos = (startPos + (int)(easeInOutQuadratic(linear)*(dest-startPos)));
                break;
            }
          } else if (ease_type==QUARTIC) {  // Quartic --------------
            switch (motion) {
              case 0:
                pos = (startPos + (int)(easeOutQuartic(linear)*(dest-startPos)));
                break;
              case 1:
                pos = (startPos + (int)(easeInQuartic(linear)*(dest-startPos)));
                break;
              case 2:
                pos = (startPos + (int)(easeInOutQuartic(linear)*(dest-startPos)));
                break;
            }
          } else if (ease_type==QUINTIC) {  // Quintic --------------
            switch (motion) {
              case 0:
                pos = (startPos + (int)(easeOutQuintic(linear)*(dest-startPos)));
                break;
              case 1:
                pos = (startPos + (int)(easeInQuintic(linear)*(dest-startPos)));
                break;
              case 2:
                pos = (startPos + (int)(easeInOutQuintic(linear)*(dest-startPos)));
                break;
            }
          } else if (ease_type==SINE) {  // Sine -----------------
            switch (motion) {
              case 0:
                pos = (startPos + (int)(easeOutSine(linear)*(dest-startPos)));
                break;
              case 1:
                pos = (startPos + (int)(easeInSine(linear)*(dest-startPos)));
                break;
              case 2:
                pos = (startPos + (int)(easeInOutSine(linear)*(dest-startPos)));
                break;
            }
          } else if (ease_type==CIRCULAR) {  // Circular -----------------
            switch (motion) {
              case 0:
                pos = (startPos + (int)(easeOutCircular(linear)*(dest-startPos)));
                break;
              case 1:
                pos = (startPos + (int)(easeInCircular(linear)*(dest-startPos)));
                break;
              case 2:
                pos = (startPos + (int)(easeInOutCircular(linear)*(dest-startPos)));
                break;
            }
          } else if (ease_type==EXPONENTIAL) {  // Exponential -----------------
            switch (motion) {
              case 0:
                pos = (startPos + (int)(easeOutExponential(linear)*(dest-startPos)));
                break;
              case 1:
                pos = (startPos + (int)(easeInExponential(linear)*(dest-startPos)));
                break;
              case 2:
                pos = (startPos + (int)(easeInOutExponential(linear)*(dest-startPos)));
                break;
            }
          } else if (ease_type==ELASTIC) {  // Elastic -----------------
            switch (motion) {
              case 0:
                pos = (startPos + (int)(easeOutElastic(linear)*(dest-startPos)));
                break;
              case 1:
                pos = (startPos + (int)(easeInElastic(linear)*(dest-startPos)));
                break;
              case 2:
                pos = (startPos + (int)(easeInOutElastic(linear)*(dest-startPos)));
                break;
            }
          } else if (ease_type==OVERSHOOT) {  // Overshoot -----------------
            switch (motion) {
              case 0:
                pos = (startPos + (int)(easeOutBack(linear)*(dest-startPos)));
                break;
              case 1:
                pos = (startPos + (int)(easeInBack(linear)*(dest-startPos)));
                break;
              case 2:
                pos = (startPos + (int)(easeInOutBack(linear)*(dest-startPos)));
                break;
            }
          } else if (ease_type==BOUNCE) {  // Bounce -----------------
            switch (motion) {
              case 0:
                pos = (startPos + (int)(easeOutBounce(linear)*(dest-startPos)));
                break;
              case 1:
                pos = (startPos + (int)(easeInBounce(linear)*(dest-startPos)));
                break;
              case 2:
                pos = (startPos + (int)(easeInOutBounce(linear)*(dest-startPos)));
                break;
            }
          }
          // For debugging 
          /*
          Serial.print("Start: ");
          Serial.print(startPos);
          Serial.print(" | + | Pos: ");
          Serial.print(pos);
          Serial.print(" | Dest: ");
          Serial.println(dest);
          */
        } else if(startPos > dest) { // Decreasing ******************************

          if (ease_type==CUBIC) {  // Cubic -----------------------
            switch (motion) {
              case 0:
                pos = (startPos - (int)(easeOutCubic(linear)*(startPos-dest)));
                break;
              case 1:
                pos = (startPos - (int)(easeInCubic(linear)*(startPos-dest)));
                break;
              case 2:
                pos = (startPos - (int)(easeInOutCubic(linear)*(startPos-dest)));
                break;
            }
          } else if (ease_type==QUADRATIC) {  // Quadratic ---------
            switch (motion) {
              case 0:
                pos = (startPos - (int)(easeOutQuadratic(linear)*(startPos-dest)));
                break;
              case 1:
                pos = (startPos - (int)(easeInQuadratic(linear)*(startPos-dest)));
                break;
              case 2:
                pos = (startPos - (int)(easeInOutQuadratic(linear)*(startPos-dest)));
                break;
            }
          } else if (ease_type==QUARTIC) {  // Quartic  -------------
            switch (motion) {
              case 0:
                pos = (startPos - (int)(easeOutQuartic(linear)*(startPos-dest)));
                break;
              case 1:
                pos = (startPos - (int)(easeInQuartic(linear)*(startPos-dest)));
                break;
              case 2:
                pos = (startPos - (int)(easeInOutQuartic(linear)*(startPos-dest)));
                break;
            }
          } else if (ease_type==QUINTIC) {  // Quintic  -------------
            switch (motion) {
              case 0:
                pos = (startPos - (int)(easeOutQuintic(linear)*(startPos-dest)));
                break;
              case 1:
                pos = (startPos - (int)(easeInQuintic(linear)*(startPos-dest)));
                break;
              case 2:
                pos = (startPos - (int)(easeInOutQuintic(linear)*(startPos-dest)));
                break;
            }
          } else if (ease_type==SINE) {  // Sine  ----------------
            switch (motion) {
              case 0:
                pos = (startPos - (int)(easeOutSine(linear)*(startPos-dest)));
                break;
              case 1:
                pos = (startPos - (int)(easeInSine(linear)*(startPos-dest)));
                break;
              case 2:
                pos = (startPos - (int)(easeInOutSine(linear)*(startPos-dest)));
                break;
            }
          } else if (ease_type==CIRCULAR) {  // Circular  ----------------
            switch (motion) {
              case 0:
                pos = (startPos - (int)(easeOutCircular(linear)*(startPos-dest)));
                break;
              case 1:
                pos = (startPos - (int)(easeInCircular(linear)*(startPos-dest)));
                break;
              case 2:
                pos = (startPos - (int)(easeInOutCircular(linear)*(startPos-dest)));
                break;
            }
          } else if (ease_type==EXPONENTIAL) {  // Exponential  ----------------
            switch (motion) {
              case 0:
                pos = (startPos - (int)(easeOutExponential(linear)*(startPos-dest)));
                break;
              case 1:
                pos = (startPos - (int)(easeInExponential(linear)*(startPos-dest)));
                break;
              case 2:
                pos = (startPos - (int)(easeInOutExponential(linear)*(startPos-dest)));
                break;
            }
          } else if (ease_type==ELASTIC) {  // Elastic  ----------------
            switch (motion) {
              case 0:
                pos = (startPos - (int)(easeOutElastic(linear)*(startPos-dest)));
                break;
              case 1:
                pos = (startPos - (int)(easeInElastic(linear)*(startPos-dest)));
                break;
              case 2:
                pos = (startPos - (int)(easeInOutElastic(linear)*(startPos-dest)));
                break;
            }
          } else if (ease_type==OVERSHOOT) {  // Overshoot  ----------------
            switch (motion) {
              case 0:
                pos = (startPos - (int)(easeOutBack(linear)*(startPos-dest)));
                break;
              case 1:
                pos = (startPos - (int)(easeInBack(linear)*(startPos-dest)));
                break;
              case 2:
                pos = (startPos - (int)(easeInOutBack(linear)*(startPos-dest)));
                break;
            }
          } else if (ease_type==BOUNCE) {  // Bounce  ----------------
            switch (motion) {
              case 0:
                pos = (startPos - (int)(easeOutBounce(linear)*(startPos-dest)));
                break;
              case 1:
                pos = (startPos - (int)(easeInBounce(linear)*(startPos-dest)));
                break;
              case 2:
                pos = (startPos - (int)(easeInOutBounce(linear)*(startPos-dest)));
                break;
            }
          } 
          // For debugging
          /*
          Serial.print("Start: ");
          Serial.print(startPos);
          Serial.print(" | - | Pos: ");
          Serial.print(pos);
          Serial.print(" | Dest: ");
          Serial.println(dest);
          */
        } else {
          //Serial.println("Already here.");
        }
        servo.writeMicroseconds(pos);
      } 
    }
  }
};

#endif
