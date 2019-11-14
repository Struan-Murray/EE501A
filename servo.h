#ifndef SERVO_H_INCLUDED
#define SERVO_H_INCLUDED

#include <stdint.h>
#include <Arduino.h>
#include <Servo.h>

class ServoSG90
{
private:
	int8_t sig_pin;
	int16_t current_angle, requested_angle;
	Servo s;
public:

	/*Default constructor, sets no pin.
	 */
	ServoSG90();

	/*Custom constructor, sets custom pin.
	 */
	ServoSG90(int8_t sig_p);

	/*Allows external program to set pin before start()
	 */
	void setPin(int8_t sig_p);

	/*Used to assign pin to Servo (MUST BE PLACED IN SETUP)
	 */
	void start();

	/*Sets angle of servo.
	 */
	void angle(int16_t ang);
};

#endif