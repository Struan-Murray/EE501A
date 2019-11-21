#include "MazeMotor.h"
#include <Time.h>;  // Is this needed?
#include <Arduino.h>; // Is this needed?
#include <math.h>;  // Is this needed?


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
int ref_pwm = 150;

// Used for testing different functionalities in the loop.
unsigned long interval_timer;

mazeMotor motor_right(motor_pwm_pin_right, motor_direction_pin_right, dir_right, odometer_pin_right, ref_pwm);
mazeMotor motor_left(motor_pwm_pin_left, motor_direction_pin_left, dir_left, odometer_pin_left, ref_pwm); 

bool flag1 = true;
bool flag2 = true;
bool flag3 = true;


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

  //interval_timer = millis();
  
}


void loop() {

  // Maintain equal motor speeds by adjusting based on odometer readings.
  update_motor_speed();

  // Test functionality.
  if (motor_right.display_distance()>80 && flag1){
    flag1 = false;
    turn_anticlockwise();
    //interval_timer = millis();
  }

  if (motor_right.display_distance()>160 && flag2){
    flag2 = false;
    turn_anticlockwise();
    //interval_timer = millis();
  }

  if (motor_right.display_distance()>200 && flag3){
    flag3 = false;
    turn_clockwise();
    //interval_timer = millis();
  }

  Serial.print(motor_right.return_x_distance());
  Serial.print(" ");
  Serial.println(motor_right.return_y_distance());
  
}


void right_odometer_update(){
  motor_right.update_odometer_value();
  motor_right.update_xy_value();    // Only need to update localised position using one motor.
}


void left_odometer_update(){
  motor_left.update_odometer_value();
}


// Functions involving both motors.

void update_motor_speed(){  
  if (abs(motor_right.return_odometer_reading()) > abs(motor_left.return_odometer_reading())){
    motor_right.decrease_speed_incrementally();
    motor_left.increase_speed_incrementally();
  }
  else{
    motor_right.increase_speed_incrementally();
    motor_left.decrease_speed_incrementally();
  }

  
//  // Print motor pwm's and odometer readings using serial plotter.
//  Serial.print(motor_right.return_current_motor_pwm());
//  Serial.print(" ");
//  Serial.print(motor_right.display_distance());
//  Serial.print(" ");
//  Serial.print(motor_left.return_current_motor_pwm());
//  Serial.print(" ");
//  Serial.println(motor_left.display_distance());
 

}


void turn_clockwise(){

  // Store current direction, so it can be re-enabled after the turn.
  int stored_direction = motor_right.return_current_direction();
  
  int stored_odometer_right;
  int stored_odometer_left;

  int stored_x;
  int stored_y;

  // Adjust this parameter when calibrating on different surfaces.
  // Should be 20 with no slip.
  int turn_distance = 18;
    
  motor_right.set_direction(STOPPED);
  motor_left.set_direction(STOPPED);
  motor_right.operate_motor();
  motor_left.operate_motor();

  stored_odometer_right = motor_right.return_odometer_reading();
  stored_odometer_left = motor_left.return_odometer_reading();

  stored_x = motor_right.return_x_position_mag();
  stored_y = motor_right.return_y_position_mag();
  
  delay(1000);

  motor_right.set_max_pwm();
  motor_left.set_max_pwm();
  motor_right.set_direction(BACKWARDS); 
  motor_left.set_direction(FORWARDS); 
  motor_right.operate_motor();
  motor_left.operate_motor();

  while( (motor_left.return_odometer_reading()-stored_odometer_left)<turn_distance ){
    motor_left.operate_motor();
  }

  motor_right.set_direction(STOPPED);
  motor_left.set_direction(STOPPED);
  motor_right.operate_motor();
  motor_left.operate_motor();
  
  delay(1000);  

  // Reset odometers to required value before continuing.
  motor_right.set_odometer_value(stored_odometer_right);
  motor_left.set_odometer_value(stored_odometer_left);

  motor_right.set_x_position_mag(stored_x);
  motor_right.set_y_position_mag(stored_y);

  motor_right.increase_heading();

  motor_right.set_reference_pwm(ref_pwm);
  motor_left.set_reference_pwm(ref_pwm);
  motor_right.set_direction(stored_direction);
  motor_left.set_direction(stored_direction);
  motor_right.operate_motor(); 
  motor_left.operate_motor();
}


void turn_anticlockwise(){

  // Store current direction, so it can be re-enabled after the turn.
  int stored_direction = motor_right.return_current_direction();
  
  int stored_odometer_right;
  int stored_odometer_left;

  int stored_x;
  int stored_y;

  // Adjust this parameter when calibrating on different surfaces.
  // Should be 20 with no slip.
  int turn_distance = 20;
    
  motor_right.set_direction(STOPPED);
  motor_left.set_direction(STOPPED);
  motor_right.operate_motor();
  motor_left.operate_motor();

  stored_odometer_right = motor_right.return_odometer_reading();
  stored_odometer_left = motor_left.return_odometer_reading();

  stored_x = motor_right.return_x_position_mag();
  stored_y = motor_right.return_y_position_mag();
  
  delay(1000);

  motor_right.set_max_pwm();
  motor_left.set_max_pwm();
  motor_right.set_direction(FORWARDS); 
  motor_left.set_direction(BACKWARDS); 
  motor_right.operate_motor();
  motor_left.operate_motor();

  while( (motor_right.return_odometer_reading()-stored_odometer_right)<turn_distance ){
    motor_right.operate_motor();
  }

  motor_right.set_direction(STOPPED);
  motor_left.set_direction(STOPPED);
  motor_right.operate_motor();
  motor_left.operate_motor();
  
  delay(1000);  

  // Reset odometers to required value before continuing.
  motor_right.set_odometer_value(stored_odometer_right);
  motor_left.set_odometer_value(stored_odometer_left);

  motor_right.set_x_position_mag(stored_x);
  motor_right.set_y_position_mag(stored_y);

  motor_right.decrease_heading();

  motor_right.set_reference_pwm(ref_pwm);
  motor_left.set_reference_pwm(ref_pwm);
  motor_right.set_direction(stored_direction);
  motor_left.set_direction(stored_direction);
  motor_right.operate_motor(); 
  motor_left.operate_motor();
}

