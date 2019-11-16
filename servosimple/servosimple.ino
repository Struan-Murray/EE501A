#include "servo.h"

ServoSG90 servo(2); //Assign pin to SG90 servo.

void setup()
{
	servo.start(); //Perform setup.
}

void loop()
{
	servo.angle(-90); //Servo all the way left.
	servo.angle(-30); //Slightly left (-30 degrees)
	servo.angle(0); //Centre servo.
	servo.angle(30); //Slightly right (30 degrees)
	servo.angle(90); //Servo all the way right
	servo.angle(0);

	delay(1000);
}
