#include "carControl.hpp"

Servo myservo;  // Create servo object to control a servo
Servo ESC;      // Create servo object to control the ECS servo motor

void setup() {
  ESC.attach(ESC_PIN);
  myservo.attach(SERVO_PIN); 
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  Serial.begin(ARDUINO_UNO_BAUD_RATE);
}

void loop() {
  ESC.write(STOP_SPEED);
  if (Serial.available() > 0){
    char mode = Serial.read();

    switch (mode) {
      case AUTOMATIC_MODE:
        automaticMode(ESC, myservo);
        break;

      case MANUAL_MODE:
        manualMode(ESC, myservo);
        break;

      default:
        break;
    }
  }
}


/*
void loop() {
  reactToObstacle(ESC);
  delay(100);
}
*/

