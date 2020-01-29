# Basic Robot Movement
## Motor Driver
### What is a motor driver for?
The arduino can't provide the voltage and current required to power the motor directly. The arduino pins can't provide (source) or take (sink) that much current, trying to run a motor directly from the arduino can damage it! The arduino is also limited to 5V which may be lower than desired for the motors. The motor driver is the interface between the power source an the motors that allow the arduino to control the motor direction and speed.
### How does a motor driver work?
When a voltage is applied to the terminals of a DC motor it rotates. To make it rotate the opposite direction the wires need to be switched to make the current flow the other way. To achieve this without having to physically switching the wires, transistors are used. Transistors set up in a configuration known as a H-bridge allow the the direction of current through a motor to be changed.

This image gives a simplified diagram of the H-bridge in the motor driver https://i.stack.imgur.com/aS6V5.jpg

A left direction pin controls the left switches. When `HIGH` top left is closed and bottom left is open. The same is true for the right direction pin for the right switches. So to drive the motor set leftDir to `HIGH` and rightDir to `LOW`. To reverse the direction set leftDir to `LOW` and rightDir to `HIGH`. So using two digital pins the motor direction can be controlled.

This gives the motor 3 states; off, full forward, full reverse. The speed of the motor can be controlled with a pwm signal to the enable switch at the bottom. (more on pwm speed control below). 

Therefore the motor needs 1 pwm pin and 2 digital pins to fully control it.
There are ways to control the speed and direction of the motor using 1 pwm pin and 1 digital pin, or even with 1 pwm pin and a NOT gate. If you are running out of pins on the uno this could be a simple way to free up some space.

### Speed Control with PWM
PWM stands for pulse width modulation. A digital pin is pulsed `HIGH` and `LOW` quickly at a fixed rate with the width of each pulse being changed depending on the desired output. Trivially when the pulse width is 0 (0% duty cycle) the digital pin is off completely and when the pulse width is max (100% duty cycle) the pin is on completely. At different duty cycles in between the output provides an averaged voltage between 0-100%. Therefore the PWM signal acts like a digital to analog converter, when the motor is given a lower duty cycle pwm input it turns slower as if it were being driven with a lower voltage.

The arduino only has a few pins capable of PWM these are marked on the board with a `~` symbol

## Motor Driver Function
This example left motor function takes care of motor control so you never need to address the motor pins directly, just call this function. Send it a speed value between -255 and 255 and the motor will go from full reverse to full forward.
```c++
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
```
## Troubleshooting
The robot is circular so you many end up redefining which way is "forward". Doing this is an issue because it inverts the direction of the motors but it also switches left and right. This can be fixed by switching the pin definitions for the motors at the top of the file. Do it slowly and check one motor at a time that it drives forward and reverse as expected.