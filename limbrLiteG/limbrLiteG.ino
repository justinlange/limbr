#define LED_PIN     3
#define COLOR_ORDER GRB
//#define CHIPSET     WS2811
#define BRIGHTNESS  100
#define FRAMES_PER_SECOND 60


int COOLING = 100;
int SPARKING = 100;

// Core library for code-sense
#include "Wiring.h"
#include "Arduino.h"

// Include application, user and local libraries
#include "LocalLibrary.h"
#include "FastLED.h"
#include <Metro.h> //Include Metro library
#include "Controller.h"

#define NUM_LEDS 12 //must address LEDS individually :-(

#define PINKIE_CT 9
#define RING_CT 10
#define MIDDLE_CT 11
#define INDEX_CT 12
#define THUMB_CT 11

#define DATA_PIN 3
#define STRIP_NUM 5
#define NUM_GESTURES 4


CRGB ledsThumb[THUMB_CT];
CRGB ledsIndex[INDEX_CT];
CRGB ledsMiddle[MIDDLE_CT];
CRGB ledsRing[RING_CT];
CRGB ledsPinkie[PINKIE_CT];


CRGB leds[5][NUM_LEDS];

Metro metro0 = Metro(500);
Metro metro1 = Metro(30);


bool flashState;

//void printDebug(String, int, float, float, bool);

const int lArray[5] = {3,4,5,6,7};

String fingerNames[] = {"thumb", "index", "middle", "ring", "pinkie"};
const int analogInPins[] = {A3, A7, A8, A9, A6};

int fla = 700;
const int flexLow[] = {723,680,690,710,706};
const int flexHigh[] = {840,834,987,880,870};
const static int bendThresh = 50;
const int digitalInPins[] = {8,9,15,16};

void readSensors();
void timerCheck();
void redBlue();
void adjustHue();
void initLEDs();
void evalGesture();
void cubulateSimple();
void palmJewel();
void runSpell(int spell);
void testGrid();

void Fire2012();


typedef struct
{
    bool isTouch[4]; //fingers that are touching
    int id;
    
    void setPos(byte _bendPos, byte _touchPos)
    {
        bendPos = _bendPos;
        touchPos = _touchPos;
    }
    
    byte getTouchPos() { return touchPos; }
    byte getBendPos()  { return bendPos ; }
    
    byte spgetBendPos()  {
        byte tPos = bendPos | 1;
        return tPos ;
    }

    
    
    void setInfo(String _sanskrit, String _english, byte _bendPos, byte _touchPos, int _spell ){
        
        sanskrit = _sanskrit;
        english = _english;
        bendPos = _bendPos;
        touchPos = _touchPos;
        spell = _spell;
    }

    void getInfo(){
        String printString = "name  " + sanskrit + "  benPos: " + bendPos + "  touchPos: " + touchPos;
        Serial.println(printString);
        delay(100);
    }

    int getSpell(){ return spell; }
    
private:
    String sanskrit, english;
    byte bendPos, touchPos;
    int spell;


} gesture;
gesture    cGesture, mukula, thrisula;
gesture gestures[NUM_GESTURES];

typedef struct
{
    String name;
    int pin;
    int lowRead;
    int highRead;
    int rawVal;
    int mapVal;
    boolean isHigh;
    
} sensor;
sensor flex[5];
sensor touch[8];

void initGestures(){
    
    int touchByte = B00000;
/*
          / ' )   ./')
         /' /.--''./'')
     :--''  ;    ''./'')
     :     '     ''./')
     :           ''./'
     :--''-..--''''
*/
    mukula.setPos(B11111, touchByte);  //trailing 0 is ignored
    thrisula.setPos(B01110, touchByte);
    
    gestures[0].setInfo("pataka", "flag", B00000, B11110000, 0);
    gestures[1].setInfo("thrisula", "trident", B01110, B01100000, 1);
    //gestures[2].setInfo("makula", B111110, B00001);
    gestures[2].setInfo("Kartarimukha", "Arrow shaft", B10011, B00010011, 2);
    gestures[3].setInfo("Shikhara", "Heroism", B01111, B01110000, 3);


    //gestures[3].setInfo("Mudrakhya",)
    //gestures[0].setPos(B111110, B001001);
    gestures[0].getInfo();
    
    
}//set gesture info for hand positions
void initSensors() {
    
    for (int i=0; i<5; i++) {
        //flex[i] = sensor();
        flex[i].pin = analogInPins[i];
        flex[i].name = fingerNames[i];
        flex[i].lowRead = flexLow[i];
        flex[i].highRead = flexHigh[i];
        flex[i].isHigh = false;
        pinMode(flex[i].pin, INPUT);
    }
    
    for (int i=0; i<4; i++) {
        pinMode(digitalInPins[i], INPUT_PULLUP);
        touch[i].pin = digitalInPins[i];
    }
    
}
void readSensors(bool print){
    
    int bendByte = 0;
    int touchByte = 0;
    
    for (int i=0; i<5; i++) {
        flex[i].rawVal = analogRead(flex[i].pin);
        flex[i].mapVal = map(flex[i].rawVal, flex[i].lowRead, flex[i].highRead, 0, 100);
        if (flex[i].mapVal > bendThresh) {
            flex[i].isHigh = true;
            bendByte = bendByte | 1;
        
        }else{
            flex[i].isHigh = false;
        }
        if(i<4){
            bendByte = bendByte << 1;
        }
        
        bool readState;
        
        
        for (int i=0; i<8; i++){
             readState = digitalRead(touch[i].pin);
            
            if(readState){
                touch[i].isHigh = true;
                touchByte = touchByte | 1;
                
            }else{
                touch[i].isHigh = true;
                
            }
            if (i<7) touchByte = touchByte << 1;
            
        }
        
        cGesture.setPos(bendByte, touchByte);
   
        if(print){
            Serial.print(flex[i].name);
            Serial.print(" raw: ");
            Serial.print(flex[i].rawVal);
            Serial.print(", map: ");
            Serial.print(flex[i].mapVal);
            Serial.print(", isHigh: ");
            Serial.print(flex[i].isHigh);
            Serial.print("    ");

        }
        
    } // create a byte representing bent fingers
    
    
    //have 8 switches, four between spaces between fingers left to right, and four between thumb & each finger
 
    
    if(print) {
       // Serial.println();
      
        /*
        if(bendByte == mukula.getBendPos())
        {
            Serial.print("mukula!");
        }
        else if(bendByte == thrisula.getBendPos())
        {
            Serial.print("thrisula!");
        }
    
        //Serial.print("  byte:  ");
        //Serial.println(bendByte);
         */
    
    } //print values for testing (delete soon)
    
    Serial.println();
 
}
bool sameGesture(gesture gesCur, gesture gesRef){
    if(gesCur.getBendPos() == gesRef.getBendPos() && gesCur.getTouchPos() == gesRef.getTouchPos()){
        return true;
    }
    return false;
}
bool sameBesidesPinkie(gesture gesCur, gesture gesRef){
    if(gesCur.spgetBendPos() == gesRef.spgetBendPos() ){
        return true;
    }
    return false;
}
bool sameBend(gesture gesCur, gesture gesRef) {
    if(gesCur.getBendPos() == gesRef.getBendPos() ){
        return true;
    }
    return false;
}
void evalGesture(){
    
    for(int i = 0; i< NUM_GESTURES; i++ ){
    
        //gestures[i].getInfo();
        
        if(sameBend(cGesture, gestures[i])){
            //String printString = "at position: " + i;
            //Serial.print(printString);
            gestures[i].getInfo();
            runSpell( gestures[i].getSpell() );
        }
       
    }
        //if(touchByte == mukula.getTouchPos()){
        //set current hand gesture to last hand gesture
        //set current hand gesture to mukula
    
}

void setup() {
	// sanity check delay - allows reprogramming if accidently blowing power w/leds
   	delay(500);

    initLEDs();
    initSensors();
    initGestures();
    
    Serial.begin(9600);
    
}
void loop() {
    
    readSensors(false);

    /*
    
    random16_add_entropy( random());
    
    Fire2012(); // run simulation frame
    FastLED.show(); // display this frame
    
#if defined(FASTLED_VERSION) && (FASTLED_VERSION >= 2001000)
    FastLED.delay(1000 / FRAMES_PER_SECOND);
#else
    delay(1000 / FRAMES_PER_SECOND);
#endif  ﻿
     */
    
    //testGrid();
    
   // timerCheck();
    
    //xpalmJewel();
    //cubulateSimple();
    //adjustHue();
    readSensors(true);
    //redBlue();
    evalGesture();
    
}

void printDebug(String title, int num1, float num2, float num3, bool newLine){
    String printString = title + ":  num1: " + num1 + "  num2: " + num2 + "  num3: " + num3 + "  ";
    if(newLine)  Serial.println(printString);
    if(!newLine) Serial.print(printString);
}


/* ---------------------------------------------- */
/* ------------------- SPELLS ------------------- */
/* ---------------------------------------------- */

void runSpell(int spell) {
    switch (spell) {
        case 0:
            palmJewel();
            break;
        case 1:
            redBlue();
            break;
        case 2:
            cubulateSimple();
            break;
        default:
            adjustHue();
            break;
    }
    
    
    
    
}
void initLEDs() {
    
    /*
    FastLED.addLeds<WS2812, 5, GRB>(ledsPinkie, PINKIE_CT);
    FastLED.addLeds<WS2812, 7, GRB>(ledsRing, RING_CT);
    FastLED.addLeds<WS2812, 4, GRB>(ledsMiddle, MIDDLE_CT);
    FastLED.addLeds<WS2812, 3, GRB>(ledsIndex, INDEX_CT);
    FastLED.addLeds<WS2812, 6, GRB>(ledsThumb, THUMB_CT);
    
     */
    FastLED.addLeds<WS2812, 6, GRB>(leds[0], THUMB_CT);
    FastLED.addLeds<WS2812, 3, GRB>(leds[1], INDEX_CT);
    FastLED.addLeds<WS2812, 4, GRB>(leds[2], MIDDLE_CT);
    FastLED.addLeds<WS2812, 7, GRB>(leds[3], RING_CT);
    FastLED.addLeds<WS2812, 5, GRB>(leds[4], PINKIE_CT);
    LEDS.setBrightness(100);
    
    
    
    
}
int palmGrid[5][14] = {
    
    //things to do:
    
    //create palm grid (x & y axis)
    //create tips-of-finger-grid (x axis)
    
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 },   //sample values
    {-1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,-1,-1,-1 },  // index finger
    { 2, 3, 4, 5, 6, 7, 8, 9,10,-1,-1,-1,-1,-1 },  // middle
    {-1, 2, 3, 4, 5, 6, 7, 8, 9,-1,-1,-1,-1,-1 },  // ring
    {-1,-1,-1,-1,-1,-1, 1, 2, 3, 4, 5, 6, 7, 8 },  // pinkie
};


void testGrid(){

    for (int j=0; j<14; j++) {
    for (int i=1; i<5; i++) {
            int delayVal = 30;
            
            if(palmGrid[i][j] > -1){
                int ledToShow = palmGrid[i][j];
                leds[i][ledToShow] = CRGB::Purple;
                LEDS.show();
                delay(delayVal);
                leds[i][ledToShow] = CRGB::Black;
                LEDS.show();
            }else{
                delay(delayVal);
            }
            
        }
    }
    
    /* void gridOutside(){
     
     bool dripping = true;
     bool scanningR = false;
     bool scanningL = false;
     bool rising = false;
     
     int column = 1;
     int row = 0;
     
     if(dripping) row++;
     
     
     if(row == 13) {
     dripping = false;
     scanningR = true;
     }
     
     if(scanningR){
     column ++;
     }
     
     if(column)
     
     
     
     for (int j=0; j<14; j++) {
     for (int i=1; i<5; i++) {
     int delayVal = 30;
     
     if(palmGrid[i][j] > -1){
     int ledToShow = palmGrid[i][j];
     leds[i][ledToShow] = CRGB::Purple;
     LEDS.show();
     delay(delayVal);
     leds[i][ledToShow] = CRGB::Black;
     LEDS.show();
     }else{
     delay(delayVal);
     }
     
     }
     }
     
     } */
    
}
void adjustHue(){
    
    for(int i=0; i<5; i++){
        for(int ledNum = 0; ledNum < NUM_LEDS; ledNum++) {
            leds[i][ledNum].setHSV(flex[i].mapVal,255,150);
        }
    }
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

CRGB HeatColor( uint8_t temperature)
{
    // CRGB HeatColor( uint8_t temperature)
    // [to be included in the forthcoming FastLED v2.1]
    //
    // Approximates a 'black body radiation' spectrum for
    // a given 'heat' level.  This is useful for animations of 'fire'.
    // Heat is specified as an arbitrary scale from 0 (cool) to 255 (hot).
    // This is NOT a chromatically correct 'black body radiation'
    // spectrum, but it's surprisingly close, and it's extremely fast and small.
    //
    // On AVR/Arduino, this typically takes around 70 bytes of program memory,
    // versus 768 bytes for a full 256-entry RGB lookup table.
    
    CRGB heatcolor;
    
    // Scale 'heat' down from 0-255 to 0-191,
    // which can then be easily divided into three
    // equal 'thirds' of 64 units each.
    uint8_t t192 = scale8_video( temperature, 192);
    
    // calculate a value that ramps up from
    // zero to 255 in each 'third' of the scale.
    uint8_t heatramp = t192 & 0x3F; // 0..63
    heatramp <<= 2; // scale up to 0..252
    
    // now figure out which third of the spectrum we're in:
    if( t192 & 0x80) {
        // we're in the hottest third
        heatcolor.r = 255; // full red
        heatcolor.g = 255; // full green
        heatcolor.b = heatramp; // ramp up blue
        
    } else if( t192 & 0x40 ) {
        // we're in the middle third
        heatcolor.r = 255; // full red
        heatcolor.g = heatramp; // ramp up green
        heatcolor.b = 0; // no blue
        
    } else {
        // we're in the coolest third
        heatcolor.r = heatramp; // ramp up red
        heatcolor.g = 0; // no green
        heatcolor.b = 0; // no blue
    }
    
    return heatcolor;
}

/*
#define COOLING  100
#define SPARKING 10
 */

void Fire2012()
{
    

    
    COOLING = map(flex[0].rawVal, flex[0].lowRead, flex[0].highRead, 20, 100);
    SPARKING = map(flex[1].rawVal, flex[0].lowRead, flex[0].highRead, 50, 200);

    // Fire2012 by Mark Kriegsman, July 2012
    
    // as part of "Five Elements" shown here: http://youtu.be/knWiGsmgycY
    //
    // This basic one-dimensional 'fire' simulation works roughly as follows:
    // There's a underlying array of 'heat' cells, that model the temperature
    // at each point along the line.  Every cycle through the simulation,
    // four steps are performed:
    //  1) All cells cool down a little bit, losing heat to the air
    //  2) The heat from each cell drifts 'up' and diffuses a little
    //  3) Sometimes randomly new 'sparks' of heat are added at the bottom
    //  4) The heat from each cell is rendered as a color into the leds array
    //     The heat-to-color mapping uses a black-body radiation approximation.
    //
    // Temperature is in arbitrary units from 0 (cold black) to 255 (white hot).
    //
    // This simulation scales it self a bit depending on NUM_LEDS; it should look
    // "OK" on anywhere from 20 to 100 LEDs without too much tweaking.
    //
    // I recommend running this simulation at anywhere from 30-100 frames per second,
    // meaning an interframe delay of about 10-35 milliseconds.
    //
    //
    // There are two main parameters you can play with to control the look and
    // feel of your fire: COOLING (used in step 1 above), and SPARKING (used
    // in step 3 above).
    //
    // COOLING: How much does the air cool as it rises?
    // Less cooling = taller flames.  More cooling = shorter flames.
    // Default 55, suggested range 20-100

    // SPARKING: What chance (out of 255) is there that a new spark will be lit?
    // Higher chance = more roaring fire.  Lower chance = more flickery fire.
    // Default 120, suggested range 50-200.
    
    
    // Array of temperature readings at each simulation cell
    static byte heat[NUM_LEDS];
    
    for(int finger = 0; finger< 5; finger++){
    
    // Step 1.  Cool down every cell a little
    for( int i = 0; i < NUM_LEDS; i++) {
        heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / NUM_LEDS) + 2));
    }
    
    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for( int k= NUM_LEDS - 3; k > 0; k--) {
        heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
    }
    
    // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
    if( random8() < SPARKING ) {
        int y = random8(7);
        heat[y] = qadd8( heat[y], random8(160,255) );
    }
    
    // Step 4.  Map from heat cells to LED colors
    for( int j = 0; j < NUM_LEDS; j++) {
        leds[finger][j] = HeatColor( heat[j]);
    }
    }
    
    LEDS.setBrightness(map(flex[2].rawVal, flex[0].lowRead, flex[0].highRead, 0, 255));

}




