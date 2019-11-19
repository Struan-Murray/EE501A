#include "sensor.h"

Sensor28015 sound(13); //Assign pin to ultrasound sensor.
Sensor0A41SK ir(A0);

void setup()
{
	Serial.begin(9600);
	sound.start(); //Perform setup.
  ir.start();
}

void loop()
{
	Serial.print("Sound:");
  Serial.print(sound.ping());
  Serial.print(",IR:");
  Serial.println(ir.ping());
  
	delay(100);
}
