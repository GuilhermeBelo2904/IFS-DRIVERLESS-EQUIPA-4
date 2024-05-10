#include "carControl.hpp"

void sensorSequence() {
  // TODO: Implement sensor sequence
}

void demoSequence() {
  // TODO: Implement demo sequence
}

void ultrasonicSensorInit() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
}

bool isObstacle(int distanceCm) {
  return distanceCm < 10 && distanceCm > 3;
}

bool reactToObstacle(Servo ESC) {
  long duration = pulseIn(ECHO_PIN, HIGH);
  int distanceCm = duration * 0.0343 / 2;
  /*
  Serial.print("CM: ");
  Serial.print(distanceCm);
  Serial.print("\n");
  */
  
  return isObstacle(distanceCm);
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
  delay(15);
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
    delay(15);
    return STOP_SPEED;
}
