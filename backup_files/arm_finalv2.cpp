/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald

 modified for the ESP32 on March 2017
 by John Bennett

 see http://www.arduino.cc/en/Tutorial/Sweep for a description of the original code

 * Different servos require different pulse widths to vary servo angle, but the range is
 * an approximately 500-2500 microsecond pulse every 20ms (50Hz). In general, hobbyist servos
 * sweep 180 degrees, so the lowest number in the published range for a particular servo
 * represents an angle of 0 degrees, the middle of the range represents 90 degrees, and the top
 * of the range represents 180 degrees. So for example, if the range is 1000us to 2000us,
 * 1000us would equal an angle of 0, 1500us would equal 90 degrees, and 2000us would equal 1800
 * degrees.
 *
 * Circuit: (using an ESP32 Thing from Sparkfun)
 * Servo motors have three wires: power, ground, and signal. The power wire is typically red,
 * the ground wire is typically black or brown, and the signal wire is typically yellow,
 * orange or white. Since the ESP32 can supply limited current at only 3.3V, and servos draw
 * considerable power, we will connect servo power to the VBat pin of the ESP32 (located
 * near the USB connector). THIS IS ONLY APPROPRIATE FOR SMALL SERVOS.
 *
 * We could also connect servo power to a separate external
 * power source (as long as we connect all of the grounds (ESP32, servo, and external power).
 * In this example, we just connect ESP32 ground to servo ground. The servo signal pins
 * connect to any available GPIO pins on the ESP32 (in this example, we use pin 18.
 *
 * In this example, we assume a Tower Pro MG995 large servo connected to an external power source.
 * The published min and max for this servo is 1000 and 2000, respectively, so the defaults are fine.
 * These values actually drive the servos a little past 0 and 180, so
 * if you are particular, adjust the min and max values to match your needs.
 */

#include <ESP32Servo.h>
#include <Wire.h> // Only needed for Arduino 1.6.5 and earlier
#include <MFRC522.h>

// create four servo objects
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
// Published values for SG90 servos; adjust if needed
int minUs = 500;
int maxUs = 3500;

int grabForce = 50;

// These are all GPIO pins on the ESP32
// Recommended pins include 2,4,12-19,21-23,25-27,32-33
int servo1Pin = 26; // base
int servo2Pin = 25; // j1
int servo3Pin = 19; // j2 -NOT WORKING
int servo4Pin = 33; // wrist
int servo5Pin = 32; // gripper

int pos = 0; // position in degrees
ESP32PWM pwm;

void zero()
{
  // BASE
  servo2.write(0); // j1 - 26
  servo3.write(0); // j2 - 32
  servo4.write(0); // wrist - 33
  servo5.write(0); // grabber - 33
  delay(1000);
  servo1.write(0); // base - 25
}

void left()
{
  // BASE
  servo2.write(0); // j1 - 26
  servo3.write(0); // j2 - 32
  servo4.write(0); // wrist - 33
  servo5.write(0); // grabber - 33
  delay(1000);
  servo1.write(0); // base - 25

  delay(5000);

  servo1.write(90);
  delay(2000);

  // arm down to lift
  for (pos = 0; pos <= 48; pos += 1)
  { // move motor slowly
    servo2.write(pos);
    servo3.write(0);
    delay(50);
  }

  servo5.write(grabForce); // grabbed dustbin
  delay(2000);

  // arm move up

  for (pos = 48; pos >= 20; pos -= 1)
  { // move motor slowly
    servo2.write(pos);
    servo3.write(0);
    delay(50);
  }

  delay(2000);

  // base move over tank
  servo1.write(180);
  delay(2000);

  servo4.write(120); // unload kachra
  delay(2000);
  servo4.write(0); // normal dustbin orientation
  delay(2000);

  servo1.write(90);
  delay(2000);

  // arm down
  for (pos = 0; pos <= 60; pos += 1)
  { // move motor slowly
    servo2.write(pos);
    servo3.write(0);
    delay(50);
  }
  /*   servo2.write(65);
    delay(2000);
    servo3.write(30); // MOTOR NOT WORKING
     */
  delay(2000);

  servo5.write(0); // removed dustbin
  delay(5000);

  // return all except base
  servo2.write(0); // j1 - 26
  servo3.write(0); // j2 - 32
  servo4.write(0); // wrist - 33
  servo5.write(0); // grabber - 33
  delay(5000);
}

void right()
{
  // BASE
  servo2.write(0); // j1 - 26
  servo3.write(0); // j2 - 32
  servo4.write(0); // wrist - 33
  servo5.write(0); // grabber - 33
  delay(1000);
  servo1.write(0); // base - 25

  delay(5000);

  servo1.write(180);
  delay(2000);

  // arm down to lift
  for (pos = 0; pos <= 65; pos += 1)
  { // move motor slowly
    servo2.write(pos);
    servo3.write(0);
    delay(50);
  }

  servo5.write(grabForce); // grabbed dustbin
  delay(2000);

  // arm move up
  for (pos = 60; pos >= 0; pos -= 1)
  { // move motor slowly
    servo2.write(pos);
    servo3.write(0);
    delay(50);
  }

  delay(2000);

  // base move over tank
  servo1.write(0);
  delay(2000);

  servo4.write(120); // unload kachra
  delay(2000);
  servo4.write(0); // normal dustbin orientation
  delay(2000);

  servo1.write(180);
  delay(2000);

  // arm down
  for (pos = 0; pos <= 65; pos += 1)
  { // move motor slowly
    servo2.write(pos);
    servo3.write(0);
    delay(50);
  }
  /*   servo2.write(65);
    delay(2000);
    servo3.write(30); // MOTOR NOT WORKING
     */
  delay(2000);

  servo5.write(0); // removed dustbin
  delay(5000);

  // return all except base
  servo2.write(0); // j1 - 26
  servo3.write(0); // j2 - 32
  servo4.write(0); // wrist - 33
  servo5.write(0); // grabber - 33
  delay(5000);
}

void setup()
{
  // Allow allocation of all timers
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  Serial.begin(115200);
  servo1.setPeriodHertz(50); // Standard 50hz servo
  servo2.setPeriodHertz(50); // Standard 50hz servo
  servo3.setPeriodHertz(50); // Standard 50hz servo
  servo4.setPeriodHertz(50); // Standard 50hz servo
  servo4.setPeriodHertz(50); // servo5.setPeriodHertz(50);      // Standard 50hz servo
}

void loop()
{
  servo1.attach(servo1Pin, minUs, maxUs); // BASE
  servo2.attach(servo2Pin, minUs, maxUs); //
  // pwm.attachPin(27, 10000);//10khz
  servo3.attach(servo3Pin, minUs, maxUs);
  servo4.attach(servo4Pin, minUs, maxUs);
  servo5.attach(servo5Pin, minUs, maxUs);

  //zero();
  // BASE
   left();
}
