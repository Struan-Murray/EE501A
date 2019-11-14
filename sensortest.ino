#include "sweep.h"

Sweep sweep(2, 13);

void setup()
{
  Serial.begin(9600);
  sweep.start();
  pinMode(12, OUTPUT);
  digitalWrite(12, HIGH);
  pinMode(11, OUTPUT);
  digitalWrite(11, LOW);
}

void loop()
{
  Serial.println(sweep.left());
  Serial.println(sweep.right());
  Serial.println(sweep.forward());
  delay(2000);
}
