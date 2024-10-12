#include <Servo.h>

Servo ESC;
int speed = 0;
char state;

void setup() {
  Serial.begin(9600);
  Serial.println("Enter state (0 or 1):");
  ESC.attach(9, 1000, 2000);
  ESC.write(speed); 
}

void loop() {  
  if (Serial.available() > 0) {  
    state = Serial.read();
    
    if (state == '0'){
      speed = 0;
      ESC.write(speed);
      
    } else if (state == '1') {
      speed = 40;
      ESC.write(speed);
    }
  }
}
