#ifndef SENSOR_H_INCLUDED
#define SENSOR_H_INCLUDED

#include <stdint.h>

class Sensor28015
{
private:
	int8_t sig_pin;
	int32_t duration;
public:

	/*Default constructor, sets no pins.
	 */
	Sensor28015();

	/*Custom constructor, sets custom pins.
	 */
	Sensor28015(int8_t sig_p);

	/*Allows external program to set pin before start()
	 */
	void setPin(int8_t sig_p);

	/*Used to assign pin to Sensor (MUST BE PLACED IN SETUP)
	 */
	void start();

	/*Returns integer value in mm.
	 */
	int32_t ping();
};

#endif