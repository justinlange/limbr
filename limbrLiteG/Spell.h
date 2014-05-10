///
/// @file		Spell.h
/// @brief		Header
/// @details	<#details#>
/// @n	
/// @n @b		Project limbrLiteG
/// @n @a		Developed with [embedXcode+](http://embedXcode.weebly.com)
/// 
/// @author		Justin Lange
/// @author		Justin Lange
///
/// @date		5/9/14 11:35 PM
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

#ifndef Spell_h
#define Spell_h

//make an array of spells




class Spell{
public:
    
    Spell(Format& f ){
        mFormat = f;
    }
    
    
    //update //get parameters from shape
    //display
    
    
    struct Format {
        
        
    };
    
    Format mFormat;
    
    
    
};


#endif
