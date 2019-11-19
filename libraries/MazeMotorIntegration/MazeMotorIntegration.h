#ifndef MAZEMOTORINTEGRATION_h
#define MAZEMOTORINTEGRATION_h

// The following is useful for use with the Visual Studio Projects provided.
#ifdef COMPILE_CPP_NOT_ARDUINO
#include "..\All_Arduino_or_Cpp_symboldefines\All_Arduino_or_Cpp_symboldefines.h"
#else
#include <Arduino.h>
#endif

class mazeMotor{
    
    
	protected:
		int motor_pin;
        int direction_pin;
        int reference_pwm;
        int low_pwm_limit;  // Added.
        int high_pwm_limit; // Added.
		int current_pwm;
    	int off_pwm;
        int odometer_pin;
        int current_direction;  // Stopped = 0, Forwards = 1, Backwards = 2
        int odometer_reading;
        boolean motor_enabled;
        boolean direction_enabled;
        boolean odometer_enabled;
        boolean motor_on;
        
		
		void set_motor_pin_on(){                // Sets pin to current_pwm value.
			analogWrite(motor_pin, current_pwm);
		}
		

		void set_motor_pin_off(){               // Sets pin to off_pwm value.
			analogWrite(motor_pin, off_pwm);
		}
	
    
        void set_direction_pin_forwards(){      // Sets direction pin to HIGH.
            current_direction = 1;
            digitalWrite(direction_pin, HIGH);
        }
    
    
        void set_direction_pin_backwards(){     // Sets direction pin to LOW.
            current_direction = 2;
            digitalWrite(direction_pin, LOW);
        }
        
        
    	void set_default_vals(){         // Initialize variables to default values.
			motor_pin = -1;
            direction_pin = -1;
            reference_pwm = 0;
            low_pwm_limit = 0;  // Added.
            high_pwm_limit = 0; // Added.
			current_pwm = 0;
			off_pwm = 0; 
			motor_enabled = false;
            direction_enabled = false;
			motor_on = false;
            current_direction = 0;
            odometer_pin = -1;
            odometer_reading = 0;
            odometer_enabled = false;
		}
	
    
    public:
        mazeMotor(){                   // Default constructor.
            set_default_vals();
        }

        
        mazeMotor(int mot_pin, int dir_pin, int dir, int odo_pin, int ref_pwm){
            set_default_vals();
            setup_motor(mot_pin);
            setup_direction(dir_pin, dir);
            setup_odometer_pin(odo_pin);
            set_reference_pwm(ref_pwm);
        }
        
        
        boolean isMotorEnabled(){       // Checks if motor is enabled,
            return motor_enabled;
        }
        
        
        boolean isDirectionEnabled(){   // Checks if direction output is enabled.
            return direction_enabled;
        }
    
        boolean isOdometerEnabled(){
            return odometer_enabled;
        }
        
        
        boolean AreAllEnabled(){        // Checks if all components are enabled.
            return (motor_enabled && direction_enabled && odometer_enabled);
        }
        
        
        boolean isMotorOn(){        // Checks if motor is on.
            return motor_on;
        }

        
        void setup_motor(int mot_pin){     // Sets pin number for motor, and sets pin mode as OUTPUT.
            if(isMotorEnabled())
                return;
            if(mot_pin>=0)
            {
                motor_pin = mot_pin;
                pinMode(mot_pin,OUTPUT);
                motor_enabled = true;
            }
        }
        
        
        void setup_direction(int dir_pin, int dir){      // Sets pin number for direction, and sets pin mode as OUTPUT.
            current_direction = dir;
            if(isDirectionEnabled())
                return;
            if(dir_pin>=0)
            {
                direction_pin = dir_pin;
                pinMode(dir_pin,OUTPUT);
                direction_enabled = true;
            }
        }
    
    
        void setup_odometer_pin(int odo_pin){
            if(isOdometerEnabled())
                return;
            if(odo_pin>=0)
            {
                odometer_pin = odo_pin;
                pinMode(odo_pin, INPUT_PULLUP);
                odometer_enabled = true;
            }
        }
        
        void set_direction(int dir){        // Changes direction.
            current_direction = dir;
        }
        
        
        void operate_motor(){
            if (current_direction == 0){
                switch_off_motor();
            }
            if (current_direction == 1){
                operate_motor_forwards();
            }
            if (current_direction == 2){
                operate_motor_backwards();
            }
        }
        
        
        void operate_motor_forwards(){            // Activates motor in forward direction.
            
            if (isMotorEnabled()){
                set_direction_pin_forwards();
                set_motor_pin_on();
                motor_on = true;
            }
            
        }
        
        
        void operate_motor_backwards(){    // Activates motor in backwards direction.
            
            if (isMotorEnabled()){
                set_direction_pin_backwards();
                set_motor_pin_on();
                motor_on = true;
            }
            
        }
        
        
        void switch_off_motor(){                        // Turns motor off.
            if(isMotorEnabled() && isMotorOn())
            {
                set_motor_pin_off();
                current_direction = 0;
                motor_on = false;
            }
        }
        
        
        int return_odometer_pin(){
            return odometer_pin;
        }
        
        
        int return_odometer_reading(){
            return odometer_reading;
        }
        
    
        void update_odometer_value(){
            switch(current_direction){
                case 1:
                    odometer_reading += 1;
                    break;
                case 2:
                    odometer_reading -= 1;
                    break;
                default:
                    break;
            }
        }
    
    
        void set_odometer_value(int magnets){   // Added.
            odometer_reading = magnets;
        }
    
    
        int display_distance(){
            static double magnet_displacement = 0.37186;
            double distance = odometer_reading*magnet_displacement;
            return (int)distance;
        }
        
        
        int return_current_motor_pwm(){
            return current_pwm;
        }
    
    
        void set_max_pwm(){
            current_pwm = 255;
        }
    
        
        void set_reference_pwm(int ref_pwm){    // If error, return this to private section.
            if (ref_pwm<235 && ref_pwm>25){
                reference_pwm = ref_pwm;
                low_pwm_limit = ref_pwm - 25;   // Added.
                high_pwm_limit = ref_pwm + 25;  // Added.
                current_pwm = ref_pwm;
            }
        }
        
        
        void decrease_speed_incrementally(){
            if (current_pwm > low_pwm_limit){             // Added.
                current_pwm = current_pwm - 5;
                set_motor_pin_on();
            }
        }
        
        
        void increase_speed_incrementally(){
            if (current_pwm < high_pwm_limit){             // Added.
                current_pwm = current_pwm + 5;
                set_motor_pin_on();
            }
        }


        int return_current_direction(){
            return current_direction;
        }
    
  
};

#endif
