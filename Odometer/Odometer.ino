#include "MazeMotor.h"


#define STOPPED   0
#define FORWARDS  1
#define BACKWARDS 2


// Declare right motor parameters.
int motor_pwm_pin_right = 5;
int motor_direction_pin_right = 7;
int dir_right = STOPPED;
int odometer_pin_right = 2;

// Declare left motor parameters.
int motor_pwm_pin_left = 6;
int motor_direction_pin_left = 8;
int dir_left = STOPPED;
int odometer_pin_left = 3;

// Default motor pwm. 
// Max value of 206 perissable.
int ref_pwm = 150;

mazeMotor motor_right(motor_pwm_pin_right, motor_direction_pin_right, dir_right, odometer_pin_right, ref_pwm);
mazeMotor motor_left(motor_pwm_pin_left, motor_direction_pin_left, dir_left, odometer_pin_left, ref_pwm); 


void setup() {

  Serial.begin(9600);
  
  // Setup right odometer interrupt.
  attachInterrupt(digitalPinToInterrupt(motor_right.return_odometer_pin()), right_odometer_update, FALLING);
  
  // Setup left odometer interrupt.
  attachInterrupt(digitalPinToInterrupt(motor_left.return_odometer_pin()), left_odometer_update, FALLING);

  // Control motors using set_direction() and operate_motor().
  motor_right.set_direction(FORWARDS);
  motor_left.set_direction(FORWARDS);
  
  motor_right.operate_motor(); 
  motor_left.operate_motor();
  
}


void loop() {

  // Maintain equal motor speeds by adjusting based on odometer readings.
  update_motor_speed();

}


void right_odometer_update(){
  motor_right.update_odometer_value();
}


void left_odometer_update(){
  motor_left.update_odometer_value();
}


void update_motor_speed(){  
  if (motor_right.return_odometer_reading() > motor_left.return_odometer_reading()){
    motor_right.decrease_speed_incrementally();
    //motor_left.increase_speed_incrementally();
  }
  else /*(motor_right.return_odometer_reading() < motor_left.return_odometer_reading())*/{
    //motor_left.decrease_speed_incrementally();
    motor_right.increase_speed_incrementally();
  }

  // Print motor pwm's and odometer readings using serial plotter.
  Serial.print(motor_right.return_current_motor_pwm());
  Serial.print(" ");
  Serial.print(motor_right.return_odometer_reading());
  Serial.print(" ");
  Serial.print(motor_left.return_current_motor_pwm());
  Serial.print(" ");
  Serial.println(motor_left.return_odometer_reading());

}
