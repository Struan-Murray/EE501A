#include "sensor.h"

Sensor28015 ultrasound(13); //Assign pin to ultrasound sensor.

void setup()
{
	Serial.begin(9600);
	ultrasound.start(); //Perform setup.
}

void loop()
{
  int distance = ultrasound.ping(); //Return distance in mm as integer.
	Serial.print("Dist: ");
	Serial.println(distance);

	delay(1000);
}
