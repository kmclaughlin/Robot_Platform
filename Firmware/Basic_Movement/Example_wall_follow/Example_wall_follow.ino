#include <Ultrasonic.h>

//Motor pins
#define L_MOTOR_1 7
#define L_MOTOR_2 8
#define L_MOTOR_ENABLE 5
#define R_MOTOR_1 9
#define R_MOTOR_2 11
#define R_MOTOR_ENABLE 6

Ultrasonic leftSensor(A3, A2, 10000UL);

void setup() {
  Serial.begin(9600);
  //setup left motor
  pinMode(L_MOTOR_1, OUTPUT);
  pinMode(L_MOTOR_2, OUTPUT);
  pinMode(L_MOTOR_ENABLE, OUTPUT);
  //setup right motor
  pinMode(R_MOTOR_1, OUTPUT);
  pinMode(R_MOTOR_2, OUTPUT);
  pinMode(R_MOTOR_ENABLE, OUTPUT);
}

void loop() {
  int leftWall = leftSensor.read();
  if(leftWall > 15) {
    driveLeftMotor(150);
    driveRightMotor(200);  
    Serial.println("left a bit");
  }
  else if(leftWall < 10){
    driveLeftMotor(200);
    driveRightMotor(150);
    Serial.println("right a bit");
  }
  else {
    driveLeftMotor(150);
    driveRightMotor(150);  
    Serial.println("straight");
  }
}

//MOTOR FUNCTIONS
void driveLeftMotor(int speed){
  analogWrite(L_MOTOR_ENABLE, abs(speed));
  if (speed > 0){
    digitalWrite(L_MOTOR_1, HIGH);
    digitalWrite(L_MOTOR_2, LOW);
  }
  else{
    digitalWrite(L_MOTOR_1, LOW);
    digitalWrite(L_MOTOR_2, HIGH);
  }
}

void driveRightMotor(int speed){
  analogWrite(R_MOTOR_ENABLE, abs(speed));
  if (speed > 0){
    digitalWrite(R_MOTOR_1, LOW);
    digitalWrite(R_MOTOR_2, HIGH);
  }
  else {
    digitalWrite(R_MOTOR_1, HIGH);
    digitalWrite(R_MOTOR_2, LOW);
  }
}