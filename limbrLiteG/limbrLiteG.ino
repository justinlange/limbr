
// Core library for code-sense
#include "Wiring.h"
#include "Arduino.h"

// Include application, user and local libraries
#include "LocalLibrary.h"
#include "FastLED.h"
#include <Metro.h> //Include Metro library
#include "Controller.h"

// How many leds are in the strip?
#define NUM_LEDS 12

// Data pin that led data will be written out over
#define DATA_PIN 3
#define STRIP_NUM 5

// Clock pin only needed for SPI based chipsets when not using hardware SPI
//#define CLOCK_PIN 8

// This is an array of leds.  One item for each led in your strip.


CRGB leds1[NUM_LEDS];
CRGB leds2[NUM_LEDS];
CRGB leds3[NUM_LEDS];
CRGB leds4[NUM_LEDS];
CRGB leds5[NUM_LEDS];

CRGB ledsA[NUM_LEDS];
CRGB ledsB[NUM_LEDS];
CRGB ledsC[NUM_LEDS];



CRGB leds[5][NUM_LEDS];



Metro metro0 = Metro(500);
Metro metro1 = Metro(100);

void readSensors();
float fFsr;
float pot;

void timerCheck();

void redBlue();
bool flashState;

void adjustHue();
//void printDebug(String, int, float, float, bool);


const int lArray[5] = {3,4,5,6,7};

String fingerNames[] = {"thumb", "index", "middle", "ring", "pinkie"};
const int analogInPins[] = {A3, A7, A8, A9, A6};

int fla = 700;
const int flexLow[] = {760,680,690,710,706};
const int flexHigh[] = {856,834,987,880,870};
const static int bendThresh = 50;




const int digitalInPins[] = {8,9,15,16};

//thumb is 0, pinkie is 4

typedef struct
{
    String name;
    byte isBent;
    bool isTouch[4]; //fingers that are touching
    int id;
    
} gestures;


gestures    mukula, thrisula;

typedef struct
{
    String name;
    int pin;
    int lowRead;
    int highRead;
    int rawVal;
    int mapVal;
    boolean isBent;
    
} sensor;




sensor flex[5];
sensor touch[4];

//CRGB[] leds;


/*
 
        /~ )  ./')
      /' /.--''./'')
:--''  ;    ''./'')
:     '     ''./')
:           ''./'
:--''-..--''''
 
*/
void initGestures(){
    

    
    mukula.isBent = B111110;  //trailing 0 is ignored
    thrisula.isBent = B011100;
    
    
}

void initSensors() {
    
    for (int i=0; i<5; i++) {
        //flex[i] = sensor();
        flex[i].pin = analogInPins[i];
        flex[i].name = fingerNames[i];
        flex[i].lowRead = flexLow[i];
        flex[i].highRead = flexHigh[i];
        flex[i].isBent = false;
        pinMode(flex[i].pin, INPUT);
    }
    
    for (int i=0; i<4; i++) {
        pinMode(digitalInPins[i], INPUT_PULLUP);
        touch[i].pin = digitalInPins[i];
    }
    
}

void readSensors(bool print){
    
    int refByte = 0;
    
    for (int i=0; i<5; i++) {
        flex[i].rawVal = analogRead(flex[i].pin);
        flex[i].mapVal = map(flex[i].rawVal, flex[i].lowRead, flex[i].highRead, 0, 100);
        if (flex[i].mapVal > bendThresh) {
            flex[i].isBent = true;
            refByte = refByte | 1;
            refByte = refByte << 1;
        }else{
            flex[i].isBent = false;

            refByte = refByte << 1;
        }
        
        
        if(print){
            Serial.print(flex[i].name);
            Serial.print("  rawVal:  ");
            Serial.print(flex[i].rawVal);
            Serial.print("  mapVal:  ");
            Serial.print(flex[i].mapVal);
            Serial.print("  isBent:  ");
            Serial.println(flex[i].isBent);


            
        }
        
        
    }
    

    
  
    if(print) {
        Serial.println();
        
        String t;
      
        /*
        switch (refByte) {
            case mukula.isBent:
                t = "mukula!";
                break;
                
            case thrisula.isBent:
                t = "thrisula!";
                break;
            default:
                break;
        }
         */
        
        if(refByte == mukula.isBent)
        {
            Serial.print("mukula!");
        }
        else if(refByte == thrisula.isBent)
        {
            Serial.print("thrisula!");
        }
    
        Serial.print("  byte:  ");
        Serial.print(refByte);
    
}
    Serial.println();
    
    
    //delay(300);
    
}

void returnState(){

    
    
    
    
}

void initLEDs() {
    
    
    FastLED.addLeds<WS2812, 3, GRB>(leds[0], NUM_LEDS);
    FastLED.addLeds<WS2812, 4, GRB>(leds[1], NUM_LEDS);
    FastLED.addLeds<WS2812, 5, GRB>(leds[3], NUM_LEDS);
    FastLED.addLeds<WS2812, 6, GRB>(leds[4], NUM_LEDS);
    FastLED.addLeds<WS2812, 7, GRB>(leds[5], NUM_LEDS);
    
    LEDS.setBrightness(20);
    
    
    
}


// This function sets up the ledsand tells the controller about them
void setup() {
	// sanity check delay - allows reprogramming if accidently blowing power w/leds
   	delay(2000);
    
    
   // mController.initSensors();

    
  //  for (int i = 0; i<3; i++) {
  //  }

    initLEDs();

    initSensors();
    initGestures();
    
    //  FastLED.addLeds<UCS1903B, DATA_PIN, RGB>(leds[i], NUM_LEDS);
    Serial.begin(9600);
    
}


void loop() {
    
   // timerCheck();
    
    if(mukula.isBent){
    redBlue();
    }
    //readSensors();
    //adjustHue();
  //  mController.listen();
    readSensors(false);
    
    
}



/*
    


void printDebug(String title, int num1, float num2, float num3, bool newLine){
    String printString = title + ":  num1: " + num1 + "  num2: " + num2 + "  num3: " + num3 + "  ";
    if(newLine)  Serial.println(printString);
    if(!newLine) Serial.print(printString);
    
    
}
 */


void adjustHue(){
    
    for(int i=0; i<3; i++){
        for(int ledNum = 0; ledNum < NUM_LEDS; ledNum++) {
            leds[i][ledNum].setHSV(fFsr,255,150);
            //leds[i][ledNum].setHSV(255,255,255);
        }
    }
    FastLED.show();

}


void redBlue(){
    int stripNum = STRIP_NUM;
    
    if (metro1.check() == 1){
        flashState = !flashState;
        if(flashState){

        for(int i=0; i<5; i++){
            for(int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1) {
                    leds[i][whiteLed] = CRGB::Blue;
                }
            }
        }else if(!flashState){
            for(int i=0; i<5; i++){
                for(int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1) {
                    leds[i][whiteLed] = CRGB::Red;
                }
            }
        }
        FastLED.show();
    
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


