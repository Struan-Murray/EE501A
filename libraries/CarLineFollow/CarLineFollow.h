////////////////////////////////////////////////////////////////////////////////
// EE501A ROBOTICS PROJECT
// LINE FOLLOWING
// This Header will allow for the measurement of light intensity through an LDR
// Written by Calum Muir
////////////////////////////////////////////////////////////////////////////////

#ifndef CARLINEFOLLOW_H
#define CARLINEFOLLOW_H
#include <Arduino.h>

class line_follower{
	protected:
		int LDRval0;
		int LDRpin0;
 		int thresh=300;
	public:
		line_follower(){;};
		~line_follower(){;};
		
		void LDR_setup(int in0){
			LDRpin0=in0;
		}
		bool LDR_measure(){
			LDRval0=analogRead(LDRpin0);
			Serial.print("LDR =");
			Serial.println(LDRval0);	
				if(LDRval0<=thresh){
//					Serial.println("----DARK----");
					return	LOW;				
				}
				else{
//					Serial.println("----LIGHT---");
					return HIGH;			
				}	
			}
};
#endif
