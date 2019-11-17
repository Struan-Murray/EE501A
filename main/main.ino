//Main Script for robot car development.

#include "sweep.h"

Sweep sweeper(2,13);

void setup()
{
	sweeper.start();
}

void loop()
{
	int distLeft = sweeper.left();
	int distRight = sweeper.right();
  int distFront = sweeper.front();
	
	if(distFront < 100){/*Disable forward motion*/}
	else{/*Enable forward motion*/}
	if(distLeft < 200){/*Disable right turn*/}
	else{/*Enable right turn*/}
	if(distRight < 200){/*Disable left turn*/}
	else{/*Enable left turn*/}

	delay(1000);
}
