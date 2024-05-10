#include "carControl.hpp"

int pos = INITIAL_SERVO_POS;
int currentSpeed = STOP_SPEED;

void automaticMode(Servo ESC, Servo servo) {
  while(true) {
    if (Serial.available() > 0) {  // Check if there is data in the serial buffer
      char command = Serial.read();
      if (command == EXIT_MODE) {
        return;
      }
    }
    if (!reactToObstacle(ESC)){
      ESC.write(105);
    }  
  }
}

void manualMode(Servo ESC, Servo servo) {
  while(true) {
      if (Serial.available() > 0) {  // Check if there is data in the serial buffer
      char command = Serial.read();

      switch (command) {
        case TURN_LEFT_COMMAND:
          pos = turn(servo, pos, TURN_LEFT_COMMAND);
          break;

        case TURN_RIGHT_COMMAND:
          pos = turn(servo, pos, TURN_RIGHT_COMMAND);
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
        
        case EXIT_MODE:
          return;

        default:
          break;
      }
    }
  }
}

bool isObstacle(int distanceCm) {
  return distanceCm < 25 && distanceCm > 3;
}

bool reactToObstacle(Servo ESC) {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  int duration = pulseIn(ECHO_PIN, HIGH);
  int distanceCm = duration * 0.034 / 2;
  
  Serial.print("CM: ");
  Serial.print(distanceCm);
  Serial.print("\n");
  
  if (isObstacle(distanceCm)) {
    ESC.write(STOP_SPEED);
    return true;
  }

  return false;
}

int turn(Servo servo, int pos, char direction) {
  int newPos = pos;
  if (direction == TURN_LEFT_COMMAND) {
    newPos = max(MIN_SERVO_POS, pos-6);
  } 
  if (direction == TURN_RIGHT_COMMAND) {
    newPos = min(MAX_SERVO_POS, pos+6);
  }
  servo.write(newPos);
  return newPos;
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
                newSpeed = min(MAX_FORWARD_SPEED, currentSpeed+6);
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
                newSpeed = max(MIN_BACKWARD_SPEED, currentSpeed-6);
                break;
        }
    }
    
    ESC.write(newSpeed);
    delay(15);
    return newSpeed;
}

int stop(Servo ESC) {
    ESC.write(STOP_SPEED);
    return STOP_SPEED;
}
