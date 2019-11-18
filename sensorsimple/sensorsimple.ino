#include "sensor.h"

Sensor28015 left(13), right(12); //Assign pin to ultrasound sensor.

void setup()
{
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  digitalWrite(10, HIGH);
  digitalWrite(11, HIGH);
	Serial.begin(9600);
	left.start(); //Perform setup.
  right.start(); //Perform setup.
}

void loop()
{
	Serial.print("Left: ");
	Serial.print(left.ping());
  Serial.print(" Right: ");
  Serial.println(right.ping());

	delay(1000);
}
