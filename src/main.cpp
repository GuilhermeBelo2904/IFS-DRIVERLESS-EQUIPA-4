#include "carControl.hpp"

Servo myservo;  // create servo object to control a servo
Servo ESC;      // create servo object to control the ECS servo motor

int pos = INITIAL_SERVO_POS;
int currentSpeed = STOP_SPEED;

void setup() {
  ESC.attach(ESC_PIN);
  myservo.attach(SERVO_PIN); 
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  Serial.begin(ARDUINO_UNO_BAUD_RATE); 
}

void loop() {
  reactToObstacle(ESC);
  
  if (Serial.available() > 0) {  // check if there is data in the serial buffer
    char command = Serial.read();  
    
    switch (command){
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
        currentSpeed = stop(ESC, currentSpeed);
        break;      
      default:
        break;
    }
  }
}



// ------------------------Test Code------------------------
/*
// Sweep

 // create servo object to control a servo
// twelve servo objects can be created on most boards

// int pos = 0;    // variable to store the servo position



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
/*

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



SoftwareSerial espSerial(2, 3); // RX, TX

void setup() {
  Serial.begin(9600);   // Serial communication with PC
  espSerial.begin(9600); // Serial communication with ESP-01

  delay(1000); // Allow some time for the ESP-01 to initialize

  // Send AT command to check if the ESP-01 is responding
  espSerial.println("AT");
  delay(1000); // Give the ESP-01 time to respond
  
  if (espSerial.available()) {
    String response = espSerial.readString();
    Serial.print("Response to 'AT': ");
    Serial.println(response);
  } else {
    Serial.println("No response from ESP-01");
  }

  // Send AT+GMR command to get the firmware version
  espSerial.println("AT+GMR");
  delay(1000); // Wait for response
  
  if (espSerial.available()) {
    String response = espSerial.readString();
    Serial.print("Firmware version: ");
    Serial.println(response);
  }
}

void loop() {
  if (Serial.available() > 0) {  // check if there is data in the serial buffer
    char command = Serial.read();  

    if (command == 'F') {  // 'F' represents forward arrow key
      ESC.write(180);
      /*
      speedValue = min(1023, speedValue + 100);
      speedValue = map(speedValue, 0, 1023, 0, 180);
      ESC.write(speedValue);
      // ESC.write(180); 
    } else if (command == 'B') {  // 'B' represents backward arrow key
      speedValue = max(0, speedValue - 100);
      speedValue = map(speedValue, 0, 1023, 0, 180);
      ESC.write(speedValue);
      // ESC.write(0);    
    } else if (command == 'B') { 
        ESC.write(90);
    }
  }
}

/*
    if (command == 'L') {  // 'L' represents left arrow key
      pos = max(0, pos -5 5);
      myservo.write(pos);
    } else if (command == 'R') {  // 'R' represents right arrow key
      pos = min(180, pos + 5);
      myservo.write(pos); 
    } else if (command == 'F') {  // 'F' represents forward arrow key
      

      ESC.write(currentSpeed);
    } else if (command == 'B') {  // 'B' represents backward arrow key
      switch (currentSpeed) {
        case stopESC:
          currentSpeed = minBackwardSpeed;
          break;
        case minFowardSpeed:
          currentSpeed = stopESC;
          break;
        default:
          currentSpeed = max(minBackwardSpeed, currentSpeed--);
          break;
      }
      
      ESC.write(currentSpeed);
    } else if (command == 'S') {  // 'S' represents the space key
        currentSpeed = stopESC;  
        ESC.write(currentSpeed);
    }
  }

  /*
  Serial.print("Distance: ");
  Serial.print(distanceCm);
  Serial.print("\n");
  delay(1000);
  */
