///
/// @file		Lighting_.h
/// @brief		Class library header
/// @details	<#details#>
/// @n
/// @n @b		Project limbrLiteG
/// @n @a		Developed with [embedXcode+](http://embedXcode.weebly.com)
///
/// @author		Justin Lange
/// @author		Justin Lange
///
/// @date		3/20/14 10:05 PM
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

#ifndef Lighting__h

#define Lighting__h


///
/// @class	<#Description#>
///
class Lighting_ {
  
public:
  ///
  /// @brief	Cosntructor
  ///
  Lighting_();
  
  ///
  /// @brief	Initialisation
  ///
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

    ///
    ///	@brief	<#Description#>
    ///	@param	data <#data description#>
    ///
    void setColorScheme();
    
    
    
  
private:
  uint8_t _data;
};

#endif
