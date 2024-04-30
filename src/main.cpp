#include <Servo.h>
#include <Arduino.h>

Servo myservo;  // create servo object to control a servo
Servo ESC;      // create servo object to control the ECS servo motor
int pos = 90;   // variable to store the servo position, start at 90 degrees (middle)
bool isMoving = false;  // variable to check if the car is moving or not

void setup() {
  ESC.attach(8, 1000, 2000);
  myservo.attach(9);   // attach the servo on pin 9 to the servo object
  Serial.begin(9600);  // start serial communication
}

void loop() {
  if (Serial.available() > 0) {  // check if there is data in the serial buffer
    char command = Serial.read();  
    
    if (command == 'L') {  // 'L' represents left arrow key
      pos = max(0, pos - 1);  
      myservo.write(pos);  
    } else if (command == 'R') {  // 'R' represents right arrow key
      pos = min(180, pos);
      myservo.write(pos);  
    } else if (command == 'F') {  // 'F' represents forward arrow key
      if (isMoving) {
          ESC.write(90); 
        }
      ESC.write(100);  
      isMoving = true; 
    } else if (command == 'B') {  // 'B' represents backward arrow key
      if (isMoving) {
        ESC.write(90);  
      }
      ESC.write(0);  
      isMoving = true; 
    } else if (command == 'S') {  // 'S' represents the space key
      ESC.write(90);  
      isMoving = false;
    }
  }
}



// ------------------------Test Code------------------------
// Sweep
/*
Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}

// ECS Test
Servo ESC;  // create servo object to control the ESC

void setup() {
  ESC.attach(8, 1000, 2000);  // (pin, min pulse width, max pulse width in microseconds)
}

void loop() {
  // Move the ESC to a low position
  ESC.write(0);  // Send the signal to the ESC to move to position 0
  delay(2000);   // Wait for 2 seconds to hold this position

  // Move the ESC to a middle position
  ESC.write(90);  // Send the signal to the ESC to move to position 90
  delay(2000);    // Wait for 2 seconds to hold this position

  // Move the ESC to a high position
  ESC.write(180);  // Send the signal to the ESC to move to position 180
  delay(2000);     // Wait for 2 seconds to hold this position
}
*/
