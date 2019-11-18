//Main Script for robot car development.

#include "sweep.h"

Sweep sweeper(2,13);

void setup()
{
	sweeper.start();
  pinMode(12, OUTPUT);
  digitalWrite(12, HIGH);
}

void loop()
{
	int distLeft = sweeper.left();
	int distRight = sweeper.right();
  int distFront = sweeper.front();
	
	if(distFront < 100){/*Disable forward motion*/}
	else{/*Enable forward motion*/}
  if(distRight < 160){/*Disable front left turn*/}
  else{/*Enable front left turn*/}
	if(distRight < 220){/*Disable back left turn*/}
	else{/*Enable back left turn*/}
  if(distLeft < 160){/*Disable front right turn*/}
  else{/*Enable front right turn*/}
  if(distLeft < 220){/*Disable back right turn*/}
  else{/*Enable back right turn*/}

  int a = sweeper.left();
  int b = sweeper.angle(-60);
  


	delay(100);
}
