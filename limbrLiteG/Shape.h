///
/// @file		Shape.h
/// @brief		Class library header
/// @details	<#details#>
/// @n
/// @n @b		Project limbrLiteG
/// @n @a		Developed with [embedXcode+](http://embedXcode.weebly.com)
///
/// @author		Justin Lange
/// @author		Justin Lange
///
/// @date		4/16/14 7:27 PM
/// @version	<#version#>
///
/// @copyright	(c) Justin Lange, 2014
/// @copyright	<#license#>
///
/// @see		ReadMe.txt for references
///

#define NUM_GESTURES 4



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

#ifndef Shape_h

#define Shape_h


///
/// @class	<#Description#>
///
class Shape {
  
public:
  ///
  /// @brief	Cosntructor
  ///
  Shape();
  
  ///
  /// @brief	Initialisation
  ///
    
    void init();
    
    void readSensors(bool print);

    void evalGesture();
    
  void begin();
  
  ///
  ///	@brief Who am I?
  ///	@return Who am I? string
  ///
  String WhoAmI();
  
  ///
  ///	@brief	<#Description#>
  ///	@param	data <#data description#>
  ///
  void set(uint8_t data);
  
  ///
  ///	@brief	<#Description#>
  ///	@return	<#return value description#>
  ///
  uint8_t get();
    
    void initSensors();
    void initGestures();
    
    const int lArray[5] = {3,4,5,6,7};
    
    String fingerNames[5] = {"thumb", "index", "middle", "ring", "pinkie"};
    const int analogInPins[5] = {A3, A7, A8, A9, A6};
    const int flexLow[5] = {723,680,690,710,706};
    const int flexHigh[5] = {840,834,987,880,870};
    const static int bendThresh = 50;
    const int digitalInPins[4] = {8,9,15,16};

    
    
    
  
private:
    
    
    
    
    
  uint8_t _data;
};

#endif
