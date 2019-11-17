#include "sweep.h"

#define N 181 //Number of samples to take.

Sweep sweep(2, 13); //Servo pin 2, ultrasound pin 13.

int angle[N] = {0};
int dist[N] = {0};

void printUSB(); //Prints angles to serial.

void setup()
{
  Serial.begin(9600); //Begin USB comms.
  sweep.start(); //Assign pins.
  for(int i = 0; i < N; i++)
  {
    angle[i] = map(i,0,N-1,-90,90);
  }
}

void loop()
{
  for(int i = 0; i < N; i++)
  {
    dist[i] = sweep.angle(angle[i]);
  }
  sweep.front(); 

  printUSB();

  Serial.println(sweep.block(80));
  sweep.front();

  delay(1000);
}

void printUSB()
{
  for(int i = 0; i < N; i++)
  {
    Serial.print(angle[i]);
    Serial.print("\t");
  }
  Serial.println();
  for(int i = 0; i < N; i++)
  {
    Serial.print(dist[i]);
    Serial.print("\t");
  } 
  Serial.println();
}
