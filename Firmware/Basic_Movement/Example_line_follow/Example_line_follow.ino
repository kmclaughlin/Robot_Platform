//Motor pins
#define L_MOTOR_1 7
#define L_MOTOR_2 8
#define L_MOTOR_ENABLE 5
#define R_MOTOR_1 9
#define R_MOTOR_2 11
#define R_MOTOR_ENABLE 6

#define IR_SENSOR A0

#define NORMAL 500

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
  //IR sensor
  pinMode(IR_SENSOR, INPUT);
}

void loop() {
  int reading = analogRead(IR_SENSOR);
  Serial.println(reading);
  if (reading > NORMAL){
    driveLeftMotor(200);
    driveRightMotor(130);
    Serial.println("Right a bit");
  } else if (reading < NORMAL) {
    driveLeftMotor(130);
    driveRightMotor(200);
    Serial.println("Left a bit");
  } else {
    driveLeftMotor(200);
    driveRightMotor(200);
    Serial.println("Straight");
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