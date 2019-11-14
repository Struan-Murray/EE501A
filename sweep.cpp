#include "sweep.h"

#include <Arduino.h>
#include <Servo.h>

Sweep::Sweep(){
	servo.setPin(2);
	ultrasound.setPin(13);
}

Sweep::Sweep(int8_t sig_s, int8_t sig_u){
	servo.setPin(sig_s);
	ultrasound.setPin(sig_u);
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

int Sweep::angle(int a){
	servo.angle(a);
	return ultrasound.ping();
}