#ifndef SWEEP_H_INCLUDED
#define SWEEP_H_INCLUDED

#include "servo.h"
#include "sensor.h"

#define N 11

class Sweep
{
private:
	Sensor0A41SK sensor;
	ServoSG90 servo;
	int shortest;
	const int c_samples{N};
	int angl[N] = {0};
	int dist[N] = {0};

public:
	/*Standard constructor, sets pins for servo and ultrasound.
	 */
	Sweep(int8_t pin_servo, int8_t pin_sensor);

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

	/*Fill dist and angle with a sweep.
	 */
	void sweep();

	/*Find smallest result from dist matrix.
	 */
	int smallestLoc();
	int smallest();
	/*Work out car angle from sweep
	 */
	int carAngle();
};

#endif
