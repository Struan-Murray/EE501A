#include "MazeMotor.h"
//#include <Time.h>;  // Is this needed?
#include <Arduino.h>; // Is this needed?
#include <math.h>;  // Is this needed?
#include <Sonar.h>;


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
int ref_pwm = 125;

//flag to check for turnings
bool check_turnings = true;

// TEST.
unsigned long interval_timer;
unsigned long time_checked;

mazeMotor motor_right(motor_pwm_pin_right, motor_direction_pin_right, dir_right, odometer_pin_right, ref_pwm);
mazeMotor motor_left(motor_pwm_pin_left, motor_direction_pin_left, dir_left, odometer_pin_left, ref_pwm); 

Sonar sonar_left;
Sonar sonar_right;

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

  // TEST.
  interval_timer = millis();

  sonar_left.pin(10);
  sonar_right.pin(4);

  //setup interruots for lft and right sensor
    noInterrupts();           // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;
  int timer1_counter = 8572;   // preload timer 65536-16MHz/256/2Hz was 34286

  TCNT1 = timer1_counter;   // preload timer
  TCCR1B |= (1 << CS12);    // 256 prescaler
  TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt

  interrupts();             // enable all interrupts
}


void loop() {

  // Maintain equal motor speeds by adjusting based on odometer readings.
  update_motor_speed();

   //might need to disable interruot first
   int maxClearance =2500;

   if (check_turnings == true){
    int left_clearance = sonar_left.ping();
    int right_clearance = sonar_right.ping();

    Serial.print("Left = ");
    Serial.print(left_clearance);

    Serial.print(" Right = ");
    Serial.println(right_clearance);
   
    //check_turnings =false;
     if (left_clearance > maxClearance){
      time_checked = millis();
      check_turnings =false; 
      
      turn_anticlockwise_odo_2();

      }
      
      if (right_clearance > maxClearance){
        time_checked = millis();
        check_turnings =false; 
        turn_clockwise_odo_2();

         
        } 
        
        }

         if(check_turnings==false){
        if(millis() - time_checked >5000){
            check_turnings =true;
          } } 

}


void right_odometer_update(){
  motor_right.update_odometer_value();
}


void left_odometer_update(){
  motor_left.update_odometer_value();
}


// The functions below could be conbined into another header for which has access to both the wheels.

void update_motor_speed(){  
  if (abs(motor_right.return_odometer_reading()) > abs(motor_left.return_odometer_reading())){
    motor_right.decrease_speed_incrementally();
    motor_left.increase_speed_incrementally();
  }
  else{
    motor_right.increase_speed_incrementally();
    motor_left.decrease_speed_incrementally();
  }

  
  // Print motor pwm's and odometer readings using serial plotter.
  //Serial.print(motor_right.return_current_motor_pwm());
  //Serial.print(" ");
  //Serial.print(motor_right.display_distance());
  //Serial.print(" ");
  //Serial.print(motor_left.return_current_motor_pwm());
  //Serial.print(" ");
  //Serial.println(motor_left.display_distance());
  

}

// SONAR SENSORS
void update_motor_speed_sonar(){  
  if (abs(sonar_left.ping()) > abs(sonar_right.ping())){
    motor_right.decrease_speed_incrementally();
    motor_left.increase_speed_incrementally();
  }
  else{
    motor_right.increase_speed_incrementally();
    motor_left.decrease_speed_incrementally();
  }

  
  // Print motor pwm's and odometer readings using serial plotter.
  Serial.print(motor_right.return_current_motor_pwm());
  Serial.print(" ");
  Serial.print(sonar_left.ping());
  Serial.print(" ");
  Serial.println(motor_left.return_current_motor_pwm());
  

}


// TEST.
void turn_clockwise(){

  // Store current direction, so it can be re-enabled after the turn.
  int stored_direction = motor_right.return_current_direction();
  
  // Disable odometer when turning on the spot.
  detachInterrupt(digitalPinToInterrupt(motor_right.return_odometer_pin()));
  detachInterrupt(digitalPinToInterrupt(motor_left.return_odometer_pin()));
    
  motor_right.set_direction(STOPPED);
  motor_left.set_direction(STOPPED);
  motor_right.operate_motor();
  motor_left.operate_motor();
  
  delay(1000);
  
  motor_right.set_direction(BACKWARDS);
  motor_left.set_direction(FORWARDS);
  motor_right.operate_motor(); 
  motor_left.operate_motor();
  
  delay(1000);  // Calibrate this delay such that the car rotates for 90 degrees.

  motor_right.set_direction(STOPPED);
  motor_left.set_direction(STOPPED);
  motor_right.operate_motor();
  motor_left.operate_motor();
  
  delay(1000);  

  // Re-enabe odometer before proceeding in a straight line again.
  attachInterrupt(digitalPinToInterrupt(motor_right.return_odometer_pin()), right_odometer_update, FALLING);
  attachInterrupt(digitalPinToInterrupt(motor_left.return_odometer_pin()), left_odometer_update, FALLING);
  
  motor_right.set_direction(stored_direction);
  motor_left.set_direction(stored_direction);
  motor_right.operate_motor(); 
  motor_left.operate_motor();
}

// TEST.
void turn_anticlockwise(){

  // Store current direction, so it can be re-enabled after the turn.
  int stored_direction = motor_right.return_current_direction();
  
  // Disable odometer when turning on the spot.
  detachInterrupt(digitalPinToInterrupt(motor_right.return_odometer_pin()));
  detachInterrupt(digitalPinToInterrupt(motor_left.return_odometer_pin()));
    
  motor_right.set_direction(STOPPED);
  motor_left.set_direction(STOPPED);
  motor_right.operate_motor();
  motor_left.operate_motor();
  
  delay(1000);
  
  motor_right.set_max_pwm();
  motor_left.set_max_pwm();
  motor_right.set_direction(FORWARDS);
  motor_left.set_direction(BACKWARDS);
  motor_right.operate_motor(); 
  motor_left.operate_motor();
  
  delay(2000);  // Calibrate this delay such that the car rotates for 90 degrees.

  motor_right.set_direction(STOPPED);
  motor_left.set_direction(STOPPED);
  motor_right.operate_motor();
  motor_left.operate_motor();
  
  delay(1000);  

  // Re-enabe odometer before proceeding in a straight line again.
  attachInterrupt(digitalPinToInterrupt(motor_right.return_odometer_pin()), right_odometer_update, FALLING);
  attachInterrupt(digitalPinToInterrupt(motor_left.return_odometer_pin()), left_odometer_update, FALLING);
  
  motor_right.set_reference_pwm(ref_pwm);
  motor_left.set_reference_pwm(ref_pwm);
  motor_right.set_direction(stored_direction);
  motor_left.set_direction(stored_direction);
  motor_right.operate_motor(); 
  motor_left.operate_motor();
}

// TEST USING ODOMETRY.
// One wheel turning.
void turn_clockwise_odo(){

  // Store current direction, so it can be re-enabled after the turn.
  int stored_direction = motor_right.return_current_direction();
  
  int stored_odometer;
  int corrected_odometer;

  // Adjust this parameter when calibrating on different surfaces.
  // Should be 41 with no slip.
  int turn_distance = 47;
    
  motor_right.set_direction(STOPPED);
  motor_left.set_direction(STOPPED);
  motor_right.operate_motor();
  motor_left.operate_motor();

  // Store current odometry reading so it can be restored with added bias at end of turn.
  stored_odometer = motor_left.return_odometer_reading();
  
  delay(1000);

  //motor_left.set_max_pwm();
  motor_left.set_direction(FORWARDS); 
  motor_left.operate_motor();

  while( (motor_left.return_odometer_reading()-stored_odometer)<turn_distance ){
    motor_left.operate_motor();
  }
    
  motor_left.set_direction(STOPPED);
  motor_left.operate_motor();
  
  delay(1000);  

  // Reset odometers to required value before continuing, account for added distance in turn.
  // Assumes perfect turn with no slip.
  if (stored_direction == 1){
    corrected_odometer = stored_odometer+(turn_distance/2);
  }
  else if (stored_direction == 2){
    corrected_odometer = stored_odometer-(turn_distance/2);
  }
  
  motor_right.set_odometer_value(corrected_odometer);
  motor_left.set_odometer_value(corrected_odometer);

  //motor_left.set_reference_pwm(ref_pwm);
  motor_right.set_direction(stored_direction);
  motor_left.set_direction(stored_direction);
  motor_right.operate_motor(); 
  motor_left.operate_motor();
}

// TEST USING ODOMETRY.
// Both wheels turning
void turn_clockwise_odo_2(){

  // Store current direction, so it can be re-enabled after the turn.
  int stored_direction = motor_right.return_current_direction();
  
  int stored_odometer_right;
  int stored_odometer_left;

  // Adjust this parameter when calibrating on different surfaces.
  // Should be 20 with no slip.
  int turn_distance = 15;
    
  motor_right.set_direction(STOPPED);
  motor_left.set_direction(STOPPED);
  motor_right.operate_motor();
  motor_left.operate_motor();

  // Store current odometry reading so it can be restored with added bias at end of turn.
  stored_odometer_right = motor_right.return_odometer_reading();
  stored_odometer_left = motor_left.return_odometer_reading();
  
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

  motor_right.set_reference_pwm(ref_pwm);
  motor_right.set_reference_pwm(ref_pwm);
  motor_right.set_direction(stored_direction);
  motor_left.set_direction(stored_direction);
  motor_right.operate_motor(); 
  motor_left.operate_motor();
}


void turn_anticlockwise_odo_2(){

  // Store current direction, so it can be re-enabled after the turn.
  int stored_direction = motor_right.return_current_direction();
  
  int stored_odometer_right;
  int stored_odometer_left;

  // Adjust this parameter when calibrating on different surfaces.
  // Should be 20 with no slip.
  int turn_distance = 15;
    
  motor_right.set_direction(STOPPED);
  motor_left.set_direction(STOPPED);
  motor_right.operate_motor();
  motor_left.operate_motor();

  // Store current odometry reading so it can be restored with added bias at end of turn.
  stored_odometer_right = motor_right.return_odometer_reading();
  stored_odometer_left = motor_left.return_odometer_reading();
  
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

  motor_right.set_reference_pwm(ref_pwm);
  motor_right.set_reference_pwm(ref_pwm);
  motor_right.set_direction(stored_direction);
  motor_left.set_direction(stored_direction);
  motor_right.operate_motor(); 
  motor_left.operate_motor();
}


ISR(TIMER1_OVF_vect) {
  }
