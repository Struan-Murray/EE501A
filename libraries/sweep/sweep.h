#ifndef SWEEP_H_INCLUDED
#define SWEEP_H_INCLUDED

#include "servo.h"
#include "sensor.h"

class Sweep
{
private:
	Sensor28015 ultrasound;
	ServoSG90 servo;
	int shortest;

public:
	/*Standard constructor, sets pins for servo and ultrasound.
	 */
	Sweep(int8_t pin_servo, int8_t pin_ultrasound);

	/*Used to assign pins to Sweep (MUST BE PLACED IN SETUP)
	 */
	void start();
	
	/*Returns integer distance (mm) values from Left, Right, and Forward directions.
	 */
	int left();
	int right();
	int forward();
	int front(); //Calls forward();

	/*Return integer distance (mm) values from custom angle. (-90 Left to 90 Right)
	 */
	int angle(int a);

	/*Sweeps an angle of 'a' in front of the sensor (-a/2 to a/2) and return the shortest distance.
	 */
	int Sweep::block(int a);
};

// Examle Use
/*
Sweep sweeper(2,13);

void setup()
{
	sweeper.start(); //Assigns pins, does trivial in/out setup.
}

void loop()
{
	sweep.left(); //Moves servo to left(-90 degrees) and returns sensor distance.
	sweep.right(); //Moves servo to right(90 degrees) and returns sensor distance.
	sweep.angle(-45); //Moves servo 45 degrees to left of centre and returns distance.
	sweep.angle(20); //Moves servo 20 degrees to right of centre and returns distance.
	sweep.front(); //Moves servo to front and returns distance.
}
*/


#endif
