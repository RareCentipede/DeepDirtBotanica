#include <Arduino.h>
#include "A4988.h"

// Define pins
int Step = 3;  // GPIO3 in Arduino UNO --- Step of stepper motor driver
int Dire = 2;  // GPIO2 in Arduino UNO --- Direction of stepper motor driver
int Sleep = 4; // GPIO4 in Arduino UNO --- Control Sleep Mode on A4988
int MS1 = 7;   // GPIO7 in Arduino UNO --- MS1 for A4988
int MS2 = 6;   // GPIO6 in Arduino UNO --- MS2 for A4988
int MS3 = 5;   // GPIO5 in Arduino UNO --- MS3 for A4988

// Motor Specs
const int spr = 200;  // Steps per revolution
int RPM = 100;          // Motor Speed in RPM
int Microsteps = 1;   // Step size (1 for full steps, 2 for half steps, etc)

// Create stepper motor object
A4988 stepper(spr, Dire, Step, MS1, MS2, MS3);

void setup() {
  Serial.begin(9600);
  pinMode(Step, OUTPUT);
  pinMode(Dire, OUTPUT);
  pinMode(Sleep, OUTPUT);

  digitalWrite(Step, LOW);
  digitalWrite(Dire, LOW);
  
  // Initialize motor with RPM and microstepping setting
  stepper.begin(RPM, Microsteps);
  Serial.println("Enter direction (l or r):");
}

void loop() {
  digitalWrite(Sleep, HIGH);
  int steps = 90;
  
  if (Serial.available() > 0) {    
    // Read input from serial monitor
    char input = Serial.read();

    // Determine direction
    if ((input == 'l') || (input == 'L')) {
      stepper.rotate(-steps);
      
    } else if ((input == 'r') || (input == 'R')) {
      stepper.rotate(steps); 
    }
  }
  digitalWrite(Sleep, LOW);
}
