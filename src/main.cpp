#include <Servo.h>
#include <Arduino.h>

Servo myservo;  // create servo object to control a servo
int pos = 90;   // variable to store the servo position, start at 90 degrees (middle)

void setup() {
  myservo.attach(9);   // attach the servo on pin 9 to the servo object
  Serial.begin(9600);  // start serial communication
}

void loop() {
  if (Serial.available() > 0) {  // check if there is data in the serial buffer
    char command = Serial.read();  // read the command from the serial buffer
    
    if (command == 'L') {  // 'L' represents left arrow key
      pos = max(0, pos - 1);  // decrement position but not below 0
      myservo.write(pos);  // move servo
    } else if (command == 'R') {  // 'R' represents right arrow key
      pos = min(180, pos + 1);  // increment position but not above 180
      myservo.write(pos);  // move servo
    }
  }
}
