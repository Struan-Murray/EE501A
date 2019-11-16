#include "sweep.h"

Sweep sweep(2, 13); //Servo pin 2, ultrasound pin 13.

void setup()
{
  Serial.begin(9600); //Begin USB comms.
  sweep.start(); //Assign pins.
}

void loop()
{
  int leftDistance = sweep.left(); //Moves servo to left(-90 deg) and takes ultrasound distance value.
  int rightDistance = sweep.right(); //As above but right(90 deg).
  int forwardDistance = sweep.forward(); //As above but front(0 deg).
  int custom1Distance = sweep.angle(-35); //As above but leftish(-35 deg).
  int custom2Distance = sweep.angle(45); //As above but rightish(45 deg).

  delay(1000);
}
