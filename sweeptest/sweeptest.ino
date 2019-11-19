#include "sweep.h"

Sweep sweep(2, A0); //Servo pin 2, sensor pin A0.

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
  Serial.println(sweep.carAngle());
  sweep.angle(sweep.smallest());

  delay(1000);
}
