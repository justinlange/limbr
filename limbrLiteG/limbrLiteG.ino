//next: put spells in own class. then right function that has case statement that calls them. then have default spell that flashes white or something so we know nothing is there yet



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
#include "Controller.h"

// Include application, user and local libraries
#include "LocalLibrary.h"
#include "FastLED.h"
#include <Metro.h> //Include Metro library
#include "Controller.h"
#include "Shape.h"

#define NUM_LEDS 12 //must address LEDS individually :-(

#define PINKIE_CT 9
#define RING_CT 10
#define MIDDLE_CT 11
#define INDEX_CT 12
#define THUMB_CT 11

#define DATA_PIN 3
#define STRIP_NUM 5


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





int fla = 700;


void timerCheck();
void redBlue();
void adjustHue();
void initLEDs();
void cubulateSimple();
void palmJewel();
void runSpell(int spell);
void testGrid();
void runFire();
void Fire2012(int cooling, int sparking);

Shape s;








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




void setup() {
	// sanity check delay - allows reprogramming if accidently blowing power w/leds
   	delay(500);

    initLEDs();
    s.initSensors();
    s.initGestures();
    
    Serial.begin(9600);
    
    Serial.print(s.WhoAmI());
 
    
}
void loop() {
    

    
    
    /*runFire(    COOLING = map(flex[0].rawVal, flex[0].lowRead, flex[0].highRead, 20, 100);
    SPARKING = map(flex[1].rawVal, flex[0].lowRead, flex[0].highRead, 50, 200););*/
    
    //testGrid();
    
   // timerCheck();
    
    //xpalmJewel();
    //cubulateSimple();
    //adjustHue();
    s.readSensors(false);
    
    //redBlue();
    //s.evalGesture();
    
}

void printDebug(String title, int num1, float num2, float num3, bool newLine){
    String printString = title + ":  num1: " + num1 + "  num2: " + num2 + "  num3: " + num3 + "  ";
    if(newLine)  Serial.println(printString);
    if(!newLine) Serial.print(printString);
}


/* ----------------------------------------------
   ------------------- SPELLS -------------------
   ---------------------------------------------- */

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
/*
void adjustHue(){
    
    for(int i=0; i<5; i++){
        for(int ledNum = 0; ledNum < NUM_LEDS; ledNum++) {
            leds[i][ledNum].setHSV(flex[i].mapVal,255,150);
        }
    }
    FastLED.show();

}
 */
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

typedef struct RgbColor
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
} RgbColor;

typedef struct HsvColor
{
    unsigned char h;
    unsigned char s;
    unsigned char v;
} HsvColor;

RgbColor HsvToRgb(HsvColor hsv){
    RgbColor rgb;
    unsigned char region, remainder, p, q, t;
    
    if (hsv.s == 0)
    {
        rgb.r = hsv.v;
        rgb.g = hsv.v;
        rgb.b = hsv.v;
        return rgb;
    }
    
    region = hsv.h / 43;
    remainder = (hsv.h - (region * 43)) * 6;
    
    p = (hsv.v * (255 - hsv.s)) >> 8;
    q = (hsv.v * (255 - ((hsv.s * remainder) >> 8))) >> 8;
    t = (hsv.v * (255 - ((hsv.s * (255 - remainder)) >> 8))) >> 8;
    
    switch (region)
    {
        case 0:
            rgb.r = hsv.v; rgb.g = t; rgb.b = p;
            break;
        case 1:
            rgb.r = q; rgb.g = hsv.v; rgb.b = p;
            break;
        case 2:
            rgb.r = p; rgb.g = hsv.v; rgb.b = t;
            break;
        case 3:
            rgb.r = p; rgb.g = q; rgb.b = hsv.v;
            break;
        case 4:
            rgb.r = t; rgb.g = p; rgb.b = hsv.v;
            break;
        default:
            rgb.r = hsv.v; rgb.g = p; rgb.b = q;
            break;
    }
    
    return rgb;
}
HsvColor RgbToHsv(RgbColor rgb){
    HsvColor hsv;
    unsigned char rgbMin, rgbMax;
    
    rgbMin = rgb.r < rgb.g ? (rgb.r < rgb.b ? rgb.r : rgb.b) : (rgb.g < rgb.b ? rgb.g : rgb.b);
    rgbMax = rgb.r > rgb.g ? (rgb.r > rgb.b ? rgb.r : rgb.b) : (rgb.g > rgb.b ? rgb.g : rgb.b);
    
    hsv.v = rgbMax;
    if (hsv.v == 0)
    {
        hsv.h = 0;
        hsv.s = 0;
        return hsv;
    }
    
    hsv.s = 255 * long(rgbMax - rgbMin) / hsv.v;
    if (hsv.s == 0)
    {
        hsv.h = 0;
        return hsv;
    }
    
    if (rgbMax == rgb.r)
        hsv.h = 0 + 43 * (rgb.g - rgb.b) / (rgbMax - rgbMin);
    else if (rgbMax == rgb.g)
        hsv.h = 85 + 43 * (rgb.b - rgb.r) / (rgbMax - rgbMin);
    else
        hsv.h = 171 + 43 * (rgb.r - rgb.g) / (rgbMax - rgbMin);
    
    return hsv;
}
CRGB HeatColor( uint8_t temperature){
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
/*
CHSV rotateHue(CRGB colorToChange, float changeFactor){
//    CHSV colorToChange = colorToChange.
  return
 
} */

//CHSV rgb2hsv(CRGB inColor);

void runFire(){
    
    random16_add_entropy( random());
    
    Fire2012(50,100); // run simulation frame
    FastLED.show(); // display this frame
    
#if defined(FASTLED_VERSION) && (FASTLED_VERSION >= 2001000)
    FastLED.delay(1000 / FRAMES_PER_SECOND);
#else
    delay(1000 / FRAMES_PER_SECOND);
#endif  ﻿
    
}
void Fire2012(int cooling, int sparking){
    
    COOLING = cooling;
    SPARKING = sparking;

    


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
        //CRGB mColor;
        //CHSV hColor = rgb2hsv(HeatColor( heat[j]));

        //mColor.setHSV(hColor.h, hColor.s, hColor.v);
        /*
        CRGB heatColor = HeatColor( heat[j]);
        RgbColor rColor;
        rColor.r = heatColor.r;
        rColor.g = heatColor.g;
        rColor.b = heatColor.b;
        
        CRGB h;
        h.r = rColor.r;
        h.g = rColor.g;
        h.b = rColor.b;
         */
        
        leds[finger][j] = HeatColor( heat[j]); }
    }
    
    //LEDS.setBrightness(map(flex[2].rawVal, flex[0].lowRead, flex[0].highRead, 0, 255)); //doesn't work

    //CRGB myColor = CHSV(100, 100, 150);
    
    //CHSV myColorH = CHSV(100,150,150);
    
    //myColorH.saturation = 100;
}


/*

typedef struct {
    double r;       // percent
    double g;       // percent
    double b;       // percent
} rgb;

typedef struct {
    double h;       // angle in degrees
    double s;       // percent
    double v;       // percent
} hsv;

static hsv      rgb2hsv(rgb in);
static rgb      hsv2rgb(hsv in);

CHSV rgb2hsv(CRGB inColor)
{
    delay(10);
    
    Serial.print("CRGB r: ");
    Serial.print(inColor.r);
    Serial.print(",  g: ");
    Serial.print(inColor.g);
    Serial.print(",  b: ");
    Serial.print(inColor.b);

    
    rgb in;
    in.r = static_cast<double>(inColor.r);
    in.g = static_cast<double>(inColor.g);
    in.b = static_cast<double>(inColor.b);
    
    Serial.print("     in.r: ");
    Serial.print(in.r);
    Serial.print(",  in.g: ");
    Serial.print(in.g);
    Serial.print(",  in.b: ");
    Serial.print(in.b);

    
    CHSV outColor;
    
    
    hsv         out;
    double      min, max, delta;
    
    min = in.r < in.g ? in.r : in.g;
    min = min  < in.b ? min  : in.b;
    
    max = in.r > in.g ? in.r : in.g;
    max = max  > in.b ? max  : in.b;
    
    out.v = max;                                // v
    delta = max - min;
    if( max > 0.0 ) {
        out.s = (delta / max);                  // s
    } else {
        // r = g = b = 0                        // s = 0, v is undefined
        out.s = 0.0;
        out.h = NAN;                            // its now undefined
        outColor.s = map(out.s,0.0,1.0,0.0,255.0);
        outColor.h = map(out.h,0.0,360.0,0.0,255.0);
        outColor.v = map(out.v,0.0,1.0,0.0,255.0);
        Serial.print("  out.s: ");
        Serial.print(out.s);
        Serial.print(",  out.h: ");
        Serial.print(out.h);
        Serial.print(",  out.v: ");
        Serial.println(out.v);

        
        return outColor;
    }
    if( in.r >= max )                           // > is bogus, just keeps compilor happy
        out.h = ( in.g - in.b ) / delta;        // between yellow & magenta
    else
        if( in.g >= max )
            out.h = 2.0 + ( in.b - in.r ) / delta;  // between cyan & yellow
        else
            out.h = 4.0 + ( in.r - in.g ) / delta;  // between magenta & cyan
    
    out.h *= 60.0;                              // degrees
    
    if( out.h < 0.0 )
        out.h += 360.0;
    outColor.s = map(out.s,0.0,1.0,0.0,255.0);
    outColor.h = map(out.h,0.0,360.0,0.0,255.0);
    outColor.v = map(out.v,0.0,1.0,0.0,255.0);
    Serial.print("  2nd conditional out.s: ");
    Serial.print(out.s);
    Serial.print(",  out.h: ");
    Serial.print(out.h);
    Serial.print(",  out.v: ");
    Serial.println(out.v);
    
    
    //outColor.s = 255;
    //outColor.h = 150;
    //outColor.v = 50;
    return outColor;
}


rgb hsv2rgb(hsv in)
{
    double      hh, p, q, t, ff;
    long        i;
    rgb         out;
    
    if(in.s <= 0.0) {       // < is bogus, just shuts up warnings
        out.r = in.v;
        out.g = in.v;
        out.b = in.v;
        return out;
    }
    hh = in.h;
    if(hh >= 360.0) hh = 0.0;
    hh /= 60.0;
    i = (long)hh;
    ff = hh - i;
    p = in.v * (1.0 - in.s);
    q = in.v * (1.0 - (in.s * ff));
    t = in.v * (1.0 - (in.s * (1.0 - ff)));
    
    switch(i) {
        case 0:
            out.r = in.v;
            out.g = t;
            out.b = p;
            break;
        case 1:
            out.r = q;
            out.g = in.v;
            out.b = p;
            break;
        case 2:
            out.r = p;
            out.g = in.v;
            out.b = t;
            break;
            
        case 3:
            out.r = p;
            out.g = q;
            out.b = in.v;
            break;
        case 4:
            out.r = t;
            out.g = p;
            out.b = in.v;
            break;
        case 5:
        default:
            out.r = in.v;
            out.g = p;
            out.b = q;
            break;
    }
    return out;     
}
 
 */




