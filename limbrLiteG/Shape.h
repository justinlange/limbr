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

#define NUM_GESTURES 25



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

//DOF
#include <Wire.h>
#include "Imu.h"



///
/// @class	<#Description#>
///
class Shape {
  
public:
  ///
  /// @brief	Cosntructor
  ///
  Shape();
  
    
       
    void init();

    void initIMU();
    
    void printDOFinfo();
    
    void readSensors(bool print);
    int getFlex(int finger, int min, int max);

    void evalGesture();
    
    void begin();
    
    int spellID();
    
    Imu rHand;
    
    void setTouchRead();
    
    void whichPin(int writePin, int readPin);
    
    

    
   // bool sameGesture(gesture gesCur, gesture gesRef);
    //bool sameBend(gesture gesCur, gesture gesRef);
    bool considerGesture();
  
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
    
    //const int lArray[5] = {3,4,5,6,7};
    
    String fingerNames[5] = {"thumb", "index", "middle", "ring", "pinkie"};
    const int analogInPins[5] = {23, 22, 21, 14, 17};
//    const int flexLow[5] = {770,900,730,750,710};
//    const int flexHigh[5] = {805,860,900,900,750};
    
    int flexLow[5] = {10000,10000,10000,10000,10000};
    int flexHigh[5] = {0,0,0,0,0};
    const static int bendThresh = 50;
    //const int digitalInPins[5] = {3,4,15,16,6};
    const int touchPins[5] = {6,4,3,15,16};
    void calibrate();
        void storeCalibration();
    int getRoll(int min, int max);
    
    //int spellID;

  
private:
    
    
    
    
    
  uint8_t _data;
};

#endif
