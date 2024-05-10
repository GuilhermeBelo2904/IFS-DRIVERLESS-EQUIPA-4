#include "carControl.hpp"

Servo myservo;  // Create servo object to control a servo
Servo ESC;      // Create servo object to control the ECS servo motor

int pos = INITIAL_SERVO_POS;
int currentSpeed = STOP_SPEED;

void setup() {
  ESC.attach(ESC_PIN);
  myservo.attach(SERVO_PIN); 
  ultrasonicSensorInit();
  Serial.begin(ARDUINO_UNO_BAUD_RATE);
}

void loop() {
  if (reactToObstacle(ESC)) {
    currentSpeed = stop(ESC);
  }

  if (Serial.available() > 0) {  // Check if there is data in the serial buffer
    char command = Serial.read();

    switch (command) {
      case TURN_LEFT_COMMAND:
        pos = turn(myservo, pos, TURN_LEFT_COMMAND);
        break;

      case TURN_RIGHT_COMMAND:
        pos = turn(myservo, pos, TURN_RIGHT_COMMAND);
        break;

      case FORWARD_COMMAND:
        currentSpeed = speedControl(ESC, currentSpeed, FORWARD_COMMAND);
        break;

      case BACKWARD_COMMAND:
        currentSpeed = speedControl(ESC, currentSpeed, BACKWARD_COMMAND);
        break;

      case STOP_COMMAND:
        currentSpeed = stop(ESC);
        break;

      default:
        break;
    }
  }
}
