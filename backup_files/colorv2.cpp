
#include <ESP32Servo.h>
#include <Wire.h>        // Only needed for Arduino 1.6.5 and earlier
//#include "SSD1306Wire.h" // legacy: #include "SSD1306.h"
#include <MFRC522.h>

// Define color sensor pins
#define S0 32
#define S1 33
#define sensorOut 4
#define S2 25
#define S3 26

// Variables for Color Pulse Width Measurements
int redPW = 0;
int greenPW = 0;
int bluePW = 0;

int pinkcount = 0;
int greencount = 0;
int orangecount = 0;

// Function to read Red Pulse Widths
int getRedPW()
{
  // Set sensor to read Red only
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  // Define integer to represent Pulse Width
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);
  // Return the value
  return PW;
}

// Function to read Green Pulse Widths
int getGreenPW()
{
  // Set sensor to read Green only
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  // Define integer to represent Pulse Width
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);
  // Return the value
  return PW;
}

// Function to read Blue Pulse Widths
int getBluePW()
{
  // Set sensor to read Blue only
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  // Define integer to represent Pulse Width
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);
  // Return the value
  return PW;
}

void setup()
{
  // Set S0 - S3 as outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);

  // Set Pulse Width scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  // Set Sensor output as input
  pinMode(sensorOut, INPUT);

  // Setup Serial Monitor
  Serial.begin(115200);
}

void loop()
{
  // Read Red Pulse Width
  redPW = getRedPW();
  // Delay to stabilize sensor
  delay(250);

  // Read Green Pulse Width
  greenPW = getGreenPW();
  // Delay to stabilize sensor
  delay(250);

  // Read Blue Pulse Width
  bluePW = getBluePW();
  // Delay to stabilize sensor
  delay(250);

  Serial.println("R:"+(String)redPW+", G:"+(String)greenPW+", B:"+(String)bluePW);
/* 
  if ((redPW >= 91 && redPW <= 115) && (greenPW >= 170 && greenPW <= 215) && (bluePW >= 125 && bluePW <= 145))
  {
    pinkcount++;
    Serial.println("WAIT! Estimating Color: PINK");
  }

  else if ((redPW >= 105 && redPW <= 140) && (greenPW >= 127 && greenPW <= 150) && (bluePW >= 140 && bluePW <= 165))
  {
    greencount++;
    Serial.println("WAIT! Estimating Color: GREEN");
  }

    else if ((redPW >= 95 && redPW <= 125) && (greenPW >= 158 && greenPW <= 195) && (bluePW >= 145 && bluePW <= 170))
  {
    orangecount++;
    Serial.println("WAIT! Estimating Color:ORANGE");
  }
  else
  {
    Serial.println("Sensing sheets");
  }

  if (pinkcount>=3)
  {
    Serial.println("\n***PINK Detected***");
    pinkcount = 0;
  }

  if (greencount>=3)
  {
    Serial.println("\n***GREEN Detected***");
    greencount = 0;
  }

    if (orangecount>=3)
  {
    Serial.println("\n***ORANGE Detected***");
    orangecount = 0;
  } */
}
