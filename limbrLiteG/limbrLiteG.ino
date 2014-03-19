
// Core library for code-sense
#include "Wiring.h"
#include "Arduino.h"

// Include application, user and local libraries
#include "LocalLibrary.h"
#include "FastLED.h"
#include <Metro.h> //Include Metro library


// Use if you want to force the software SPI subsystem to be used for some reason (generally, you don't)
// #define FORCE_SOFTWARE_SPI
// Use if you want to force non-accelerated pin access (hint: you really don't, it breaks lots of things)
// #define FORCE_SOFTWARE_SPI
// #define FORCE_SOFTWARE_PINS

///////////////////////////////////////////////////////////////////////////////////////////
//
// Move a white dot along the strip of leds.  This program simply shows how to configure the leds,
// and then how to turn a single pixel white and then off, moving down the line of pixels.
//

// How many leds are in the strip?
#define NUM_LEDS 8

// Data pin that led data will be written out over
#define DATA_PIN 5

// Clock pin only needed for SPI based chipsets when not using hardware SPI
//#define CLOCK_PIN 8

// This is an array of leds.  One item for each led in your strip.
CRGB ledsA[NUM_LEDS];
CRGB ledsB[NUM_LEDS];
CRGB ledsC[NUM_LEDS];

CRGB leds[3][NUM_LEDS];

Metro metro0 = Metro(500);
Metro metro1 = Metro(10);


void timerCheck();
void redBlue();
bool flashState;



//CRGB[] leds;


// This function sets up the ledsand tells the controller about them
void setup() {
	// sanity check delay - allows reprogramming if accidently blowing power w/leds
   	delay(2000);

    FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds[0], NUM_LEDS);
    FastLED.addLeds<WS2812, DATA_PIN+1, GRB>(leds[1], NUM_LEDS);
    FastLED.addLeds<WS2812, DATA_PIN+2, GRB>(leds[2], NUM_LEDS);
    
    LEDS.setBrightness(10);

    
  //  for (int i = 0; i<3; i++) {
  //  }



    
    //  FastLED.addLeds<UCS1903B, DATA_PIN, RGB>(leds[i], NUM_LEDS);
    
}


void loop() {
    
   // timerCheck();
    redBlue();

    
    
    
    /* each array addressed individually by name
     // Move a single white led
     for(int whiteLed = 0; whiteLed < stripNum; whiteLed = whiteLed + 1) {
     // Turn our current led on to white, then show the leds
     ledsA[whiteLed] = CRGB::White;
     // Show the leds (only one of which is set to white, from above)
     FastLED.show();
     // Wait a little bit
     delay(100);
     
     // Turn our current led back to black for the next loop around
     ledsA[whiteLed] = CRGB::Black;
     }
     for(int whiteLed = 0; whiteLed < stripNum; whiteLed = whiteLed + 1) {
     // Turn our current led on to white, then show the leds
     ledsB[whiteLed] = CRGB::White;
     // Show the leds (only one of which is set to white, from above)
     FastLED.show();
     // Wait a little bit
     delay(100);
     
     // Turn our current led back to black for the next loop around
     ledsB[whiteLed] = CRGB::Black;
     }
     for(int whiteLed = 0; whiteLed < stripNum; whiteLed = whiteLed + 1) {
     // Turn our current led on to white, then show the leds
     ledsC[whiteLed] = CRGB::White;
     // Show the leds (only one of which is set to white, from above)
     FastLED.show();
     // Wait a little bit
     delay(100);
     
     // Turn our current led back to black for the next loop around
     ledsC[whiteLed] = CRGB::Black;
     }
     */
    
    // stripNum = (stripNum+NUM_LEDS)%NUM_LEDS;
    
}

void redBlue(){
    int stripNum = NUM_LEDS;
    
    if (metro1.check() == 1){
        if(flashState){

        for(int i=0; i<3; i++){
            for(int whiteLed = 0; whiteLed < stripNum; whiteLed = whiteLed + 1) {
                    leds[i][whiteLed] = CRGB::Blue;
                }
            }
        }else if(!flashState){
            for(int i=0; i<3; i++){
                for(int whiteLed = 0; whiteLed < stripNum; whiteLed = whiteLed + 1) {
                    leds[i][whiteLed] = CRGB::Red;
                }
            }
        }
        FastLED.show();
        flashState = !flashState;
    
    }
}


void timerCheck(){
    int stripNum = NUM_LEDS;
    
    if (metro0.check() == 1){
        for(int i=0; i<3; i++){
            for(int whiteLed = 0; whiteLed < stripNum; whiteLed = whiteLed + 1) {
                // Turn our current led on to white, then show the leds
                leds[i][whiteLed] = CRGB::Green;
                // Show the leds (only one of which is set to white, from above)
                FastLED.show();
                // Wait a little bit
                delay(5);
                
                // Turn our current led back to black for the next loop around
                leds[i][whiteLed] = CRGB::Black;
            }
        }
    }
}