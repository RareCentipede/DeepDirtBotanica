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

  // Start with the motor in sleep mode
  Serial.println("Enter direction (Left or Right):");
}

void loop() {
  int steps = 90;
  
  if (Serial.available() > 0) {
    // Wake up the motor
    digitalWrite(Sleep, HIGH);
    
    // Read input from serial monitor
    String input = Serial.readString();
    input.trim();  // Remove any leading/trailing whitespace

    // Determine direction
    if (input.equalsIgnoreCase("Left")) {
      stepper.rotate(-steps);
      
    } else if (input.equalsIgnoreCase("Right")) {
      stepper.rotate(steps);
      
    } else {
      Serial.println("Invalid input. Enter 'Left' or 'Right'.");
    }

    // Put motor back to sleep after movement
    digitalWrite(Sleep, LOW);
  }
}
