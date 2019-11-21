#include "MazeMotor.h"
#include "CarLineFollow.h"

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
int ref_pwm = 125;
int correction_pwm_1=100;
int correction_pwm_2=75;

    mazeMotor motor_right(motor_pwm_pin_right, motor_direction_pin_right, dir_right, odometer_pin_right, ref_pwm);
    mazeMotor motor_left(motor_pwm_pin_left, motor_direction_pin_left, dir_left, odometer_pin_left, ref_pwm); 

//Setup LDR inputs
    int LDRpin0=A1;
    int LDRpin1=A2;
    bool LineFollowFlag=HIGH;
//Create object instances for each LDR
    line_follower line_right;
    line_follower line_left;
    

void setup() {
    Serial.begin(9600);
    line_right.LDR_setup(LDRpin0);
    line_left.LDR_setup(LDRpin1);

    // Control motors using set_direction() and operate_motor().
    motor_right.set_direction(FORWARDS);
    motor_left.set_direction(FORWARDS);
}

void loop() {
  line_following();
  delay(250);
}

void line_following(){
  if(LineFollowFlag==HIGH){
    //If both sensors detect light then car is following line
    if(line_right.LDR_measure()==HIGH&&line_left.LDR_measure()==HIGH){
      Serial.println("----FOLLOWING LINE----");
      motor_right.set_reference_pwm(ref_pwm);
      motor_left.set_reference_pwm(ref_pwm);
      motor_right.operate_motor();
      motor_left.operate_motor();
    }
    //If the right sensor stops detecting the line, slow down right motor
    else if(line_right.LDR_measure()==LOW&&line_left.LDR_measure()==HIGH){
      Serial.println("----TOO FAR RIGHT----");
      motor_right.set_reference_pwm(correction_pwm_1);
      motor_left.set_reference_pwm(correction_pwm_2);
      motor_left.operate_motor();
      motor_right.operate_motor();
    }
    //If the left sensor stops detecting the line, slow down the left motor
    else if(line_left.LDR_measure()==LOW&&line_right.LDR_measure()==HIGH){
      Serial.println("----TOO FAR LEFT----");
      motor_right.set_reference_pwm(correction_pwm_2);
      motor_left.set_reference_pwm(correction_pwm_1);
      motor_left.operate_motor();
      motor_right.operate_motor();
    }
    //If neither sensor detects the line, stop the car
    else if(line_left.LDR_measure()==LOW&&line_right.LDR_measure()==LOW){
      Serial.println("----STOP----");
        motor_right.switch_off_motor();
        motor_left.switch_off_motor();
        LineFollowFlag=LOW;
    }
  }
  else{
    Serial.println("----NO LINE SEGMENT DETECTED----");
    return;
  }
}
