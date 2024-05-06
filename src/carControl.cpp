#include "carControl.hpp"

bool isObstacle(int distanceCm) {
  return distanceCm < 10;
}

void reactToObstacle(Servo ESC) {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH);
  int distanceCm = duration * 0.034 / 2;

  if (isObstacle(distanceCm)) {
    ESC.write(90);
  }
}

int turn(Servo servo, char direction) {
  if (direction == TURN_LEFT_COMMAND) {
    for (size_t i = 0; i < 6; i++) {
        int pos = max(0, pos - 1);  
        servo.write(pos);
        return pos;  
    } 
  } 
  if (direction == TURN_RIGHT_COMMAND) {
    for (size_t i = 0; i < 6; i++) {
        int pos = min(180, pos + 1);  
        servo.write(pos);
        return pos;  
    } 
  }
}

int speedControl(Servo ESC, int currentSpeed, char command) {
    int newSpeed = currentSpeed;
    if (command == FORWARD_COMMAND) {
        switch (currentSpeed) {
            case STOP_SPEED:
                newSpeed = MIN_FORWARD_SPEED;
                break;
            case MIN_BACKWARD_SPEED:
                newSpeed = STOP_SPEED;
                break;
            default:
                newSpeed = min(MAX_FORWARD_SPEED, currentSpeed++);
                break;
        }
    }
    if (command == BACKWARD_COMMAND) {
        switch (currentSpeed) {
            case STOP_SPEED:
                newSpeed = MIN_BACKWARD_SPEED;
                break;
            case MIN_FORWARD_SPEED:
                newSpeed = STOP_SPEED;
                break;
            default:
                newSpeed = max(MIN_BACKWARD_SPEED, currentSpeed--);
                break;
        }
    }
    
    ESC.write(newSpeed);
    return newSpeed;
}

int stop(Servo ESC, int currentSpeed) {
    ESC.write(STOP_SPEED);
    return STOP_SPEED;
}