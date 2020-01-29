#include <Encoder.h>

//Motor pins
#define L_MOTOR_1 11
#define L_MOTOR_2 9
#define L_MOTOR_ENABLE 6
#define R_MOTOR_1 8
#define R_MOTOR_2 7
#define R_MOTOR_ENABLE 5

//encoders
// NOTE don't read from these!
// use the encoder store values below
Encoder leftEncoder(3, 4);
Encoder rightEncoder(2, 10);

volatile long leftEncoderStore = 0, 
  rightEncoderStore = 0;
volatile int rightMotorSpeed = 0,
  leftMotorSpeed = 0;
bool motorControlFlag = false;

// The motor speed is controlled in an ISR at the bottom of
// the file. You can ignore it if you want

void setup() {
  /*------------------------------------------------------------*/
  /*              Interrupt stuff - You can ignore              */
  /*------------------------------------------------------------*/
  /**/  OCR0A = 0xAF; // set the compare register A for timer0
  /**/  TIMSK0 |= _BV(OCIE0A);  //enable the compare interrupt A for timer 0
  /*------------------------------------------------------------*/
  
  Serial.begin(9600);
  //setup motors
  pinMode(L_MOTOR_1, OUTPUT);
  pinMode(L_MOTOR_2, OUTPUT);
  pinMode(R_MOTOR_1, OUTPUT);
  pinMode(R_MOTOR_2, OUTPUT);
  pinMode(L_MOTOR_ENABLE, OUTPUT);
  pinMode(R_MOTOR_ENABLE, OUTPUT);
}

void loop() {
  //YOUR CODE HERE
}

//Put you new functions here


//MOTOR FUNCTIONS
void driveLeftMotor(int speed){
  leftMotorSpeed = abs(speed);
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
  rightMotorSpeed = abs(speed);
  if (speed > 0){
    digitalWrite(R_MOTOR_1, LOW);
    digitalWrite(R_MOTOR_2, HIGH);
  }
  else {
    digitalWrite(R_MOTOR_1, HIGH);
    digitalWrite(R_MOTOR_2, LOW);
  }
}

/*------------------------------------------------------------*/
/*                    YOU CAN IGRNORE THIS                    */
/*------------------------------------------------------------*/
/**/  // motor control interrupt service routine
/**/  ISR(TIMER0_COMPA_vect) {
/**/    //alternate left and right motor control to reduce processor load.
/**/    //therefore each motor updates every 2ms
/**/    if (motorControlFlag) {
/**/    //leftMotor
/**/      long encoderReading = leftEncoder.read();
/**/      //TODO fix these magic 15s
/**/      long measuredSpeed = abs(leftEncoderStore - encoderReading) * 15; 
/**/      leftEncoderStore = encoderReading;
/**/      if (measuredSpeed > leftMotorSpeed)
/**/        digitalWrite(L_MOTOR_ENABLE, LOW);
/**/      else
/**/        digitalWrite(L_MOTOR_ENABLE, HIGH);
/**/    }
/**/    else {
/**/    //rightMotor
/**/      long encoderReading = rightEncoder.read();
/**/      //TODO fix these magic 15s
/**/      long measuredSpeed = abs(rightEncoderStore - encoderReading) * 15; 
/**/      rightEncoderStore = encoderReading;
/**/      if (measuredSpeed > rightMotorSpeed)
/**/        digitalWrite(R_MOTOR_ENABLE, LOW);
/**/      else
/**/        digitalWrite(R_MOTOR_ENABLE, HIGH);
/**/    }
/**/    motorControlFlag = !motorControlFlag;
/**/  }
/*------------------------------------------------------------*/