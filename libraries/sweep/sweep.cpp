#include "sweep.h"

#include <Arduino.h>
#include <Servo.h>

Sweep::Sweep(int8_t pin_servo, int8_t pin_ultrasound){
	servo.setPin(pin_servo);
	ultrasound.setPin(pin_ultrasound);
}

void Sweep::start(){
	servo.start();
	ultrasound.start();
}

int Sweep::left(){
	return Sweep::angle(-90);
}

int Sweep::right(){
	return Sweep::angle(90);
}

int Sweep::forward(){
	return Sweep::angle(0);
}

int Sweep::front(){
	return Sweep::forward();
}

int Sweep::angle(int a){
	servo.angle(a);
	return ultrasound.ping();
}
