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

#include "FastLED.h"
#define NUM_LEDS 12



//13,5,2,7,20

#define PINKIE_CT 8
#define RING_CT 8
#define MIDDLE_CT 8
#define INDEX_CT 8
#define THUMB_CT 8

//#define DATA_PIN 3
#define STRIP_NUM 5


CRGB ledsThumb[THUMB_CT];
CRGB ledsIndex[INDEX_CT];
CRGB ledsMiddle[MIDDLE_CT];
CRGB ledsRing[RING_CT];
CRGB ledsPinkie[PINKIE_CT];


CRGB leds[5][NUM_LEDS];



class Spell{
public:
    
    /*
    Spell(Format& f ){
        mFormat = f;
    }
     */
    
    Spell(){
        
        FastLED.addLeds<WS2812, 7, GRB>(leds[0], THUMB_CT);
        FastLED.addLeds<WS2812, 5, GRB>(leds[1], INDEX_CT);
        FastLED.addLeds<WS2812, 2, GRB>(leds[2], MIDDLE_CT);
        FastLED.addLeds<WS2812, 20, GRB>(leds[3], RING_CT);
        FastLED.addLeds<WS2812, 13, GRB>(leds[4], PINKIE_CT);
        LEDS.setBrightness(100);
        
    }
    
    Metro metro0 = Metro(30);
    Metro metro1 = Metro(100);
    Shape s = Shape();


    
    void followFingersChase(){
        int showNum = 0;
        if(metro0.check()){
            showNum++;
        }
        
        int colNum = int(s.rHand.getRoll(0,255));
        
        for(int i=0; i<5; i++){
            int controlNumber = s.getFlex(i, 0, 255);
            //Serial.print(controlNumber);
            for(int j = 0; j < NUM_LEDS; j++) {
                if(j == (showNum%NUM_LEDS)){
                    leds[i][j].setHSV(colNum, 255, controlNumber);
                }else{
                    leds[i][j].setHSV(0, 0, 0);
                    
                }
            }
        }
        FastLED.show();
        
    }
    void followFingers(){
        
        int colNum = int(s.rHand.getRoll(0,255));
        
        for(int i=0; i<5; i++){
            int controlNumber = s.getFlex(i, 0, 255);
            //Serial.print(controlNumber);
            for(int j = 0; j < NUM_LEDS; j++) {
                leds[i][j].setHSV(colNum, 255, controlNumber);
            }
        }
        FastLED.show();
        
    }
    void followFingersMono(){
        
        for(int i=0; i<5; i++){
            int controlNumber = s.getFlex(i, 0, 255);
            Serial.print(controlNumber);
            for(int j = 0; j < NUM_LEDS; j++) {
                leds[i][j].setRGB(0,0,controlNumber);
            }
        }
        FastLED.show();
        
    }
    void followHand(){
        
        int controlNumber = s.getFlex(2, 0, 100);
        
        for(int i=0; i<5; i++){
            for(int j = 0; j < NUM_LEDS; j++) {
                leds[i][j] = CRGB::Blue;
            }
        }
        FastLED.setBrightness(controlNumber);
        FastLED.show();
        
    }
    void cubulateSimple(){
        
        int pause = 20;
        int longPause = pause * 10;
        
        //turn all the LEDS
        
        for(int i=1; i<5; i++){
            for(int j = 0; j < NUM_LEDS; j++) {
                leds[i][j] = CRGB::Yellow;
            }
        }
        FastLED.show();
        delay(pause);
        
        for(int i=1; i<5; i++){
            for(int j = 0; j < NUM_LEDS; j++) {
                leds[i][j] = CRGB::Black;
            }
        }
        
        FastLED.show();
        delay(pause);
        
        //turn on the outside leds at an interval, for 10 times
        
        for (int t=0; t<5; t++) {
            for(int j = 0; j < NUM_LEDS; j++) {
                leds[1][j] = CRGB::Yellow;
                leds[4][j] = CRGB::Yellow;
                if(j < 3 || j > 8){
                    leds[2][j] = CRGB::Yellow;
                    leds[3][j] = CRGB::Yellow;
                    
                }
            }
            
            FastLED.show();
            delay(pause);
            
            for(int i=1; i<5; i++){
                for(int j = 0; j < NUM_LEDS; j++) {
                    leds[i][j] = CRGB::Black;
                }
            }
            FastLED.show();
            delay(pause);
            
        }
        
        for(int i=1; i<5; i++){
            for(int j = 0; j < NUM_LEDS; j++) {
                leds[i][j] = CRGB::Yellow;
            }
        }
        FastLED.show();
        delay(pause);
        
        for(int i=1; i<5; i++){
            for(int j = 0; j < NUM_LEDS; j++) {
                leds[i][j] = CRGB::Black;
            }
        }
        FastLED.show();
        
        delay(longPause);
        
        
        //turn back all the leds again
        //wait
        
        
    }
    void palmJewel(){
        
        int increment = 1;
        
        for(int scale = 0; scale < 128; scale++) {
            LEDS.showColor(CHSV(100, 200, 150), scale);
            delay(random8(increment, increment+3));
        }
        
        
        
        for(int scale = 128; scale > 0; scale--) {
            LEDS.showColor(CHSV(100, 200, 150), scale);
            delay(random8(increment, increment+3));
        }
        
        
    }
    
    
    bool flashState;
    void redBlue(){
        int stripNum = STRIP_NUM;
        
        if (metro1.check() == 1){
            flashState = !flashState;
            if(flashState){
                
                for(int i=0; i<5; i++){
                    for(int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed++) {
                        leds[i][whiteLed] = CRGB::Blue;
                    }
                }
            }else if(!flashState){
                for(int i=0; i<5; i++){
                    for(int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed++) {
                        leds[i][whiteLed] = CRGB::Red;
                    }
                }
            }
            FastLED.show();
            
        }
    }
    
    
    
    //update //get parameters from shape
    //display
    
    
    struct Format {
        
       
        
        //handPosition changeTrigger  -- i.e. for SHUKATUNDA, when the finger return to pataka with thumb still bent, the arrow is released
    };
    
    Format mFormat;
    
    
    
};


#endif
