#include "servo.h"

#include <Arduino.h>
#include <Servo.h>

ServoSG90::ServoSG90(){
	sig_pin = 0;
}

ServoSG90::ServoSG90(int8_t sig_p){
	sig_pin = sig_p;
}

void ServoSG90::setPin(int8_t sig_p){
	sig_pin = sig_p;
}

void ServoSG90::start(){
	s.attach(sig_pin);
	s.write(0);
	current_angle = 0;
}

void ServoSG90::angle(int16_t ang){
	requested_angle = map(ang, -90, 90, 180, 0);
	s.write(requested_angle);
	delay(240*abs(requested_angle-current_angle)/60);
	current_angle = requested_angle;
}
