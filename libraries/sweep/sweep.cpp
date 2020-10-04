#include "sweep.h"

#include <Arduino.h>
#include <Servo.h>

Sweep::Sweep(int8_t pin_servo, int8_t pin_sensor){
	servo.setPin(pin_servo);
	sensor.setPin(pin_sensor);
}

void Sweep::start(){
	servo.start();
	sensor.start();
	for(int i = 0; i < c_samples; i++)
	{
		angl[i] = map(i,0,c_samples-1,-90,90);
	}
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
	return sensor.ping();
}

void Sweep::sweep(){
	for(int i = 0; i < c_samples; i++)
	{
		dist[i] = Sweep::angle(angl[i]);
	}
}

int Sweep::smallestLoc(){
	int a = 1;
	int d = 10000;
	for(int i = 1; i < c_samples-1; i++){
		if(dist[i] < d && dist[i] != 0){
			d = dist[i]; 
			a = i;
		}
	}
	return a;
}

int Sweep::smallest(){
	int a = Sweep::smallestLoc();
  
	return angl[a];
}

int Sweep::carAngle(){
	Sweep:sweep();

	int u = smallestLoc();
	float a = 0, b = 0, c = 0;
	float aA = 0, aB = 0, aC = 0;
	float thetaS = 0;

	if(dist[u-1] != 0){b = dist[u-1]; c = dist[u]; aA = (angl[u]- angl[u-1])*PI/180; thetaS = angl[u];}
	else if(dist[u+1] != 0){b = dist[u]; c = dist[u+1]; aA = (angl[u+1]- angl[u])*PI/180; thetaS = angl[u+1];}
	else{return 0;}

	a = sqrt(b*b+c*c-2*b*c*cos(aA));
	aB = asin(b*sin(aA)/a)*180/PI;

	if(angl[u] < 0){aB=-aB;}

	return aB-thetaS;	
}

