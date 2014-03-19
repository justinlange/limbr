/// 
/// @mainpage	limbrLiteG 
///
/// @details	a new lighting instrument for dance performance
/// @n 		
/// @n 
/// @n @a		Developed with [embedXcode+](http://embedXcode.weebly.com)
/// 
/// @author		Justin Lange
/// @author		Justin Lange
/// @date		3/19/14 5:07 PM
/// @version	<#version#>
/// 
/// @copyright	(c) Justin Lange, 2014
/// @copyright	License
///
/// @see		ReadMe.txt for references
///


///
/// @file		limbrLiteG.ino
/// @brief		Main sketch
///
/// @details	<#details#>
/// @n @a		Developed with [embedXcode+](http://embedXcode.weebly.com)
/// 
/// @author		Justin Lange
/// @author		Justin Lange
/// @date		3/19/14 5:07 PM
/// @version	<#version#>
/// 
/// @copyright	(c) Justin Lange, 2014
/// @copyright	License
///
/// @see		ReadMe.txt for references
/// @n
///


// Core library for code-sense
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
#endif

// Include application, user and local libraries
#include "LocalLibrary.h"


// Prototypes


// Define variables and constants
///
/// @brief	Name of the LED
/// @details	Each board has a LED but connected to a different pin
///
uint8_t myLED;


///
/// @brief	Setup
/// @details	Define the pin the LED is connected to
///
// Add setup code 
void setup() {
  // myLED pin number
#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega2560__) || defined(__AVR_ATmega32U4__) || defined(__SAM3X8E__) // Arduino specific 
  myLED = 13; 
#elif defined(__PIC32MX__) // chipKIT specific
  myLED = 13;
#elif defined(__AVR_ATtinyX5__) // Digispark specific
    myLED = 1; // assuming model A
#elif defined(__AVR_ATmega644P__) // Wiring specific
  myLED = 15; 
#elif defined(__MSP430G2452__) || defined(__MSP430G2553__) || defined(__MSP430G2231__) || defined(__MSP430F5529__)  || defined(__MSP430FR5739__) // LaunchPad MSP430 and Experimeter Board FR5739 specific
    myLED = RED_LED;
#elif defined(__LM4F120H5QR__) || defined(__TM4C1230C3PM__) // LaunchPad Stellaris and Tiva specific
  myLED = RED_LED;
#elif defined(MCU_STM32F103RB) || defined(MCU_STM32F103ZE) || defined(MCU_STM32F103CB) || defined(MCU_STM32F103RE) // Maple specific
  myLED = BOARD_LED_PIN; 
#elif defined(__MK20DX128__) || defined(__MK20DX256__) // Teensy 3.0 and 3.1 specific
    myLED = 13;
#endif

  pinMode(myLED, OUTPUT);     
}

///
/// @brief	Loop
/// @details	Call blink
///
// Add loop code 
void loop() {
  blink(myLED, 3, 333);
  delay(1000);    
}
