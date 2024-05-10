#ifndef CARCONTROL_HPP
#define CARCONTROL_HPP

#include <Servo.h>
#include <Arduino.h>

#define ARDUINO_UNO_BAUD_RATE 9600

#define TURN_LEFT_COMMAND 'L'
#define TURN_RIGHT_COMMAND 'R'
#define FORWARD_COMMAND 'F'
#define BACKWARD_COMMAND 'B'
#define STOP_COMMAND 'S'

#define MIN_FORWARD_SPEED 99
#define MAX_FORWARD_SPEED 180
#define MIN_BACKWARD_SPEED 9
#define MAX_BACKWARD_SPEED 80
#define STOP_SPEED 90

#define INITIAL_SERVO_POS 90
#define MIN_SERVO_POS 50
#define MAX_SERVO_POS 180

#define ESC_PIN 8
#define SERVO_PIN 9
#define TRIG_PIN 11
#define ECHO_PIN 12

bool reactToObstacle(Servo ESC);
int turn(Servo servo, int pos, char direction);
int speedControl(Servo ESC, int currentSpeed, char command);
int stop(Servo ESC);

#endif
