#include <Arduino.h>
#include "A4988.h"
#include <Servo.h>

// stepper
// --- pins 
int Step = 3;  // GPIO3 in Arduino UNO --- Step of stepper motor driver
int Dire = 2;  // GPIO2 in Arduino UNO --- Direction of stepper motor driver
int Sleep = 4; // GPIO4 in Arduino UNO --- Control Sleep Mode on A4988
int MS1 = 7;   // GPIO7 in Arduino UNO --- MS1 for A4988
int MS2 = 6;   // GPIO6 in Arduino UNO --- MS2 for A4988
int MS3 = 5;   // GPIO5 in Arduino UNO --- MS3 for A4988

// --- motor specs
const int spr = 200;  // Steps per revolution
int RPM = 100;          // Motor Speed in RPM
int Microsteps = 1;   // Step size (1 for full steps, 2 for half steps, etc)

A4988 stepper(spr, Dire, Step, MS1, MS2, MS3);

// brushless
Servo motor1;
Servo motor2;
int speed;
char input;

void setup() {
  Serial.begin(9600);
  Serial.println("Enter comand (r/l/s):");

  // stepper
  pinMode(Step, OUTPUT);
  pinMode(Dire, OUTPUT);
  pinMode(Sleep, OUTPUT);

  digitalWrite(Step, LOW);
  digitalWrite(Dire, LOW);
  stepper.begin(RPM, Microsteps);

  // brushless
  motor1.attach(9, 1000, 2000);
  motor1.write(speed);
  motor2.attach(10, 1000, 2000);
  motor2.write(speed);
}

void loop() {
  digitalWrite(Sleep, HIGH);
  int steps = 30;
  
  if (Serial.available() > 0) {    
    char input = Serial.read();

    if ((input == 'l') || (input == 'L')) {
      speed = 0;
      motor1.write(speed);
      motor2.write(speed);
      stepper.rotate(-steps);
      
    } else if ((input == 'r') || (input == 'R')) {
      speed = 0;
      motor1.write(speed);
      motor2.write(speed);
      stepper.rotate(steps); 
    
    } else if ((input == 's') || (input == 'S')) {
      speed = 100;
      motor1.write(speed);
      motor2.write(speed); 
    }
  }
  digitalWrite(Sleep, LOW);
}
