# super_easing
A comprehensive servo easing library for Arduino

This library assumes you are not using an Arduino delay() function (see examples)

  You can control:
  - The speed of movement
  - Max, Min, Mid points of the servo
  - Switch between 30 different easing options (10 types, 3 motions for each type)

Easing type options:
  - Cubic
  - Quadratic
  - Quartic
  - Quintic
  - Sine
  - Circular
  - Exponential
  - Elastic
  - Overshoot
  - Bounce

Easing motion options for each type:
  - ease-out
  - ease-in
  - ease-in-out

This library was developed specifically for animatronics to change the speed and switch between different types of easing to create more realistic movements, but may be useful for any situation that requires easing.

Based on the Arduino easing functions by T-K-233: 
  * https://github.com/T-K-233/Arduino-Servo-Easing-Demo

And easing equations by Andrey Sitnik and Ivan Solovev:
  * https://easings.net/ 
