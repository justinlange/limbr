///
/// @file		Controller.h
/// @brief		Class library header
/// @details	<#details#>
/// @n
/// @n @b		Project limbrLiteG
/// @n @a		Developed with [embedXcode+](http://embedXcode.weebly.com)
///
/// @author		Justin Lange
/// @author		Justin Lange
///
/// @date		3/20/14 9:59 PM
/// @version	<#version#>
///
/// @copyright	(c) Justin Lange, 2014
/// @copyright	<#license#>
///
/// @see		ReadMe.txt for references
///


// Core library - IDE-based
#if defined(WIRING) // Wiring specific
#include "Wiring.h"
#elif defined(MAPLE_IDE) // Maple specific
#include "WProgram.h"
#elif defined(MPIDE) // chipKIT specific
#include "WProgram.h"
#elif defined(DIGISPARK) // Digispark specific
#include "Arduino.h"
#elif defined(ENERGIA) // LaunchPad MSP430 G2 and F5529, Stellaris and Tiva, Experimeter Board FR5739 specific
#include "Energia.h"
#elif defined(MICRODUINO) // Microduino specific
#include "Arduino.h"
#elif defined(TEENSYDUINO) // Teensy specific
#include "Arduino.h"
#elif defined(ARDUINO) // Arduino 1.0 and 1.5 specific
#include "Arduino.h"
#else // error
#error Platform not defined
#endif // end IDE

#ifndef Controller_h

#define Controller_h

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_9DOF.h>
#include <Adafruit_L3GD20_U.h>
#include "LocalLibrary.h"


/* Assign a unique ID to the sensors */



#define NUM_SENS 5
#define NUM_SWITCH 4

///
/// @class	processes sensor readings
///
class Controller {
  
public:
    
    int flexReadings [];
    int touchReadings [];
    int heading;
    int totalAccel;
    int pitch;
    int yaw;
    int roll;

    
    
  ///
  /// @brief	Cosntructor
  ///
  Controller();
  
  ///
  /// @brief	Initialisation
  ///
  void begin();
  void initSensors();
  void listen();
  
  
  ///
  ///	@brief Who am I?
  ///	@return Who am I? string
  ///
  String WhoAmI();
  
  ///
  ///	@brief
  ///	@param	data of some type
  ///
  void set(uint8_t data);
  
  ///
  ///	@brief	fill in later
  ///	@return	fill in return data later
  ///
  uint8_t get();
  
private:
  uint8_t _data;
    
    const int analogInPins[NUM_SENS] = {A6, A7, A8, A9, A3};
    const int digitalInPins[NUM_SWITCH] = {8,9,15,16};
    const int numDigitalPins = 4;
    
    
};

#endif
