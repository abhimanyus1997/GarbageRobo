#include <Arduino.h>
#include <BluetoothSerial.h>
#include<SPI.h>
#include<MFRC522.h>

#define ledPIN 2

int in1 = 12; // Motor A connections
int in2 = 13;
int in3 = 14; // Motor B connections
int in4 = 27;

BluetoothSerial SerialBT;
byte BTData;

/* Check if Bluetooth configurations are enabled in the SDK */
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

void setup()
{
  pinMode(ledPIN, OUTPUT);
  Serial.begin(9600);
  SerialBT.begin();
  //Serial.println("Bluetooth Started! Ready to pair...");

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  // Turn off motors - Initial state
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void loop()
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
  }

  else if (Data == 's')
  {
    // Now turn FWD motors
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }

  else if (Data == 'd')
  {
    // Now right motors
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
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
