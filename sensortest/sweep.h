#ifndef SWEEP_H_INCLUDED
#define SWEEP_H_INCLUDED

#include "servo.h"
#include "sensor.h"

class Sweep
{
private:
	Sensor28015 ultrasound;
	ServoSG90 servo;

public:

	/*Standard constructor, sets default pin.
	 */
	Sweep();

	/*Custom constructor, sets custom pin.
	 */
	Sweep(int8_t sig_s, int8_t sig_u);

	/*Used to assign pins to Sweep (MUST BE PLACED IN SETUP)
	 */
	void start();
	
	int left();
	int right();
	int forward();

	int angle(int a);
};



#endif