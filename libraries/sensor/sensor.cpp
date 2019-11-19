#include "sensor.h"

#include <Arduino.h>

#define SPEED_OF_SOUND 340	//Speed of sound in current atmosphere.
#define MAX_RANGE 1000    	//(In mm) Accuracy Tails off > 2000 mm.

Sensor28015::Sensor28015():
	sig_pin{0}{
}

Sensor28015::Sensor28015(int8_t sig_p):
	sig_pin{sig_p}{
}

void Sensor28015::setPin(int8_t sig_p){
	sig_pin = sig_p;
}

void Sensor28015::start(){
	pinMode(sig_pin, OUTPUT);
	digitalWrite(sig_pin, HIGH);
}

int32_t Sensor28015::ping(){
	pinMode(sig_pin, OUTPUT);

	digitalWrite(sig_pin, LOW);
	delayMicroseconds(2);
	digitalWrite(sig_pin, HIGH); //Activates ultrasound pulse.
	delayMicroseconds(5);
	digitalWrite(sig_pin, LOW);

	pinMode(sig_pin, INPUT);

	duration = pulseIn(sig_pin, HIGH, (int32_t)2000 * (int32_t)MAX_RANGE / (int32_t)SPEED_OF_SOUND);

	return duration * (int32_t)SPEED_OF_SOUND / (int32_t)2000;
}

Sensor0A41SK::Sensor0A41SK():
	sig_pin{0}{
}

Sensor0A41SK::Sensor0A41SK(int8_t sig_p):
	sig_pin{sig_p}{
}

void Sensor0A41SK::setPin(int8_t sig_p){
	sig_pin = sig_p;
}

void Sensor0A41SK::start(){
	pinMode(sig_pin, INPUT);
}

int32_t Sensor0A41SK::ping(){
	pinMode(sig_pin, INPUT);

	float voltage = analogRead(sig_pin) * 0.0048828125;
	distance = 13*pow(voltage,-1);

	return distance;
}
