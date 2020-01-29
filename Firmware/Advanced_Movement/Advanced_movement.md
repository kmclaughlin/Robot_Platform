# Advanced Movement Explanation
## What is the problem with basic movement?
The basic robot movement uses PWM to control the motor speed. This method is relatively straight forward but it has its problems. 

The underpinning issue with using PWM alone for speed control is that this is an open loop control method, i.e. there is no feedback to the micro-controller of the action it has asked for. This causes a variety of problems. 

PWM in this case is acting like a digital to analog converter. The pulsed output has a time averaged value equivalent to some DC voltage between 0V and maxV. Low PWM values are therefore like low voltages to the motor and if the voltage is too low it is unable to overcome the resistance of the motor/friction with the ground/momentum of the motor and will not move. That is until it can overcome it and it starts moving relatively quickly. 

This dead-zone between 0RPM and minRPM makes it difficult to make the robot move slowly in a controlled fashion. Additionally due to differences inherent to each motor, unbalanced weight distribution of the robot, a surface with a varying coefficient of friction etc the same PWM value to 2 different motors will not result in the same speed. Therefore it is difficult to make the robot go in a straight line (or do anything consistently)

## How it is solved
The first thought might be to try and fix the problem in software with a variety of coefficients for different situations to account for the differences in motor response or other problems. However this is often not the best approach. A robot is not a system of hardware and a separate system of software. A robot is combination of both these fields and often a problem that can be solved with a great deal of effort, thought and complexity in software can be solved much more easily (and more effectively) with a combined software and hardware approach.

In this case encoders are added to the robot to close the control loop. That is when the arduino asks the motors to move at a certain speed the encoders tell the arduino what the motors actually did. The arduino can then adjust what it tells the motors to do. An additional benefit of closing this control loop to track motor speed is that we can also track how far the motor has moved, which may be useful for future tasks.

## Speed Control with Encoders - TODO

```c++
void setup() {
  // Timer interrupt setup
  OCR0A = 0xAF; // set the compare register A for timer0
  TIMSK0 |= _BV(OCIE0A);  //enable the compare interrupt A for timer 0

  //continue setup
}
```

```c++
// motor control interrupt service routine
ISR(TIMER0_COMPA_vect) {
  //alternate left and right motor control to reduce processor load.
  //therefore each motor updates every 2ms
  if (motorControlFlag) {
  //left motor
    long encoderReading = leftEncoder.read();
    long measuredSpeed = abs(leftEncoderStore - encoderReading) * 15; 
    leftEncoderStore = encoderReading;
    if (measuredSpeed > leftMotorSpeed)
      digitalWrite(L_MOTOR_ENABLE, LOW);
    else
      digitalWrite(L_MOTOR_ENABLE, HIGH);
  }
  else {
  //right motor
    long encoderReading = rightEncoder.read();
    long measuredSpeed = abs(rightEncoderStore - encoderReading) * 15; 
    rightEncoderStore = encoderReading;
    if (measuredSpeed > rightMotorSpeed)
      digitalWrite(R_MOTOR_ENABLE, LOW);
    else
      digitalWrite(R_MOTOR_ENABLE, HIGH);
  }
  motorControlFlag = !motorControlFlag;
}
```

## Useful Links for More About Interrupts
https://learn.adafruit.com/multi-tasking-the-arduino-part-2/timers  
https://www.teachmemicro.com/arduino-timer-interrupt-tutorial/  
https://arduino.stackexchange.com/questions/30968/
