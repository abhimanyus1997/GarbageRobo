#include <Arduino.h>
#include <BluetoothSerial.h>
// For a connection via I2C using the Arduino Wire include:
#include <Wire.h>        // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306Wire.h" // legacy: #include "SSD1306.h"
#include <MFRC522.h>

#define ledPIN 2

//motor pins
int in1 = 12; // Motor A connections
int in2 = 13;
int in3 = 14; // Motor B connections
int in4 = 27;
//laser pin
int laser = 5;

//ULTRASONIC SENSOR
const int trigPin = 4;
const int echoPin = 2;
//define sound speed in cm/uS
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701
long duration;
float distanceCm,dist_cm;
float distanceInch;


//BT DATA
BluetoothSerial SerialBT;
byte BTData;
/* Check if Bluetooth configurations are enabled in the SDK */
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

// Optionally include custom images
//#include "images.h"

// Initialize the OLED display using Arduino Wire:
SSD1306Wire display(0x3c, SDA, SCL); // ADDRESS, SDA, SCL  -  SDA and SCL usually populate automatically based on your board's pins_arduino.h e.g. https://github.com/esp8266/Arduino/blob/master/variants/nodemcu/pins_arduino.h

/* #define DEMO_DURATION 3000
typedef void (*Demo)(void);

int demoMode = 0;
 */

int counter = 1;

void blink_lsr()
{
  for (size_t i = 0; i < 5; i++)
  {
    digitalWrite(laser, HIGH);
    delay(100);
    digitalWrite(laser, LOW);
    delay(100);
  }
}

int ultrasound()
{
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  distanceCm = duration * SOUND_SPEED/2;
  
  // Convert to inches
  distanceInch = distanceCm * CM_TO_INCH;
  
  // Prints the distance in the Serial Monitor
/*   Serial.print("Distance (cm): ");
  Serial.println(distanceCm);
  Serial.print("Distance (inch): ");
  Serial.println(distanceInch); */
  return distanceCm;
  
  delay(1000);
}

void motorRun()
{
  if (SerialBT.available())
  {
    BTData = SerialBT.read();
    Serial.write(BTData);
  }
  char Data = (char)BTData;

  if (Data == 'w')
  {
    // Now turn FWD motors
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    digitalWrite(laser, HIGH);
  }

  else if (Data == 's')
  {
    // Now turn FWD motors
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    digitalWrite(laser, LOW);
  }

  else if (Data == 'd')
  {
    // Now right motors
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    blink_lsr();
  }
  else if (Data == 'D')
  {
    // Now xtreme right motors
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  }

  else if (Data == 'a')
  {
    // Now left motors
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    blink_lsr();
  }
  else if (Data == 'A')
  {
    // Now xtreme left motors
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }

  else
  {
    // Now stop motors
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  }
}

void setup()
{
  pinMode(ledPIN, OUTPUT);
  Serial.begin(9600);
  SerialBT.begin();
  Serial.println();
  Serial.println();

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  pinMode(laser, OUTPUT);

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);  // Sets the echoPin as an Input

  // Turn off motors - Initial state
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  digitalWrite(laser, LOW);

  // Initialising the UI will init the display too.
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
}

void loop()
{

  motorRun();
  dist_cm = ultrasound();
  Serial.println(String(dist_cm));

  // clear the display
  display.clear();
  // draw the current demo method
  // demos[demoMode]();

  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_RIGHT);
  display.drawString(15, 2, "NW");
  display.drawString(120, 2, "NE");
  display.drawString(15, 50, "SW");
  display.drawString(120, 50, "SE");
  display.drawString(80, 25, "Obstacle at: " + String(dist_cm)+" cm");
  // write the buffer to the display
  display.display();
  counter++;
  //delay(10);
}
