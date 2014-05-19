///
/// @file		Sorcery.h
/// @brief		Header
/// @details	<#details#>
/// @n	
/// @n @b		Project limbrLiteG
/// @n @a		Developed with [embedXcode+](http://embedXcode.weebly.com)
/// 
/// @author		Justin Lange
/// @author		Justin Lange
///
/// @date		5/15/14 10:56 AM
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

#ifndef Sorcery_h
#define Sorcery_h

class Sorcery {
public:
    
    Sorcery(Format& f){
        mFormat = f;
        
    }
    struct Format {
        
        
        
        //handPosition changeTrigger  -- i.e. for SHUKATUNDA, when the finger return to pataka with thumb still bent, the arrow is released
    };
    
    Format mFormat;
};


struct Format {
    
    
    
    //handPosition changeTrigger  -- i.e. for SHUKATUNDA, when the finger return to pataka with thumb still bent, the arrow is released
};

Format mFormat;


#endif
