#include "sweep.h"

Sweep sweep(2, 13); //Servo pin 2, sensor pin 13.

void setup()
{
	Serial.begin(9600); //Begin USB comms.
	sweep.start(); //Assign pins.
	pinMode(12, OUTPUT);
	digitalWrite(12, HIGH);
}

void loop()
{
	Serial.print("Angle:");
	Serial.print(sweep.carAngle());
	delay(500);

	Serial.print("ShortestAngle:");
	Serial.print(sweep.smallest());
	sweep.angle(sweep.smallest());
	delay(500);

	Serial.print("FrontDistance:");
	Serial.println(sweep.front());
	delay(1000);
}
