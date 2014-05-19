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
#include <Metro.h> //Include Metro library

#define NUM_LEDS 12



//13,5,2,7,20

#define PINKIE_CT 8
#define RING_CT 8
#define MIDDLE_CT 8
#define INDEX_CT 8
#define THUMB_CT 8

//#define DATA_PIN 3
#define STRIP_NUM 5


CRGB leds[5][NUM_LEDS];



class Spell{
public:
    
    int fingerCt[5] = {8,10,11,10,8};
    int globalBright = 100;
    
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
        LEDS.setBrightness(globalBright);
        
        initGrid();
        
    }
    
    Metro metro0 = Metro(30);
    Metro metro1 = Metro(100);
    Shape s = Shape();


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
    
    struct led{
        bool on = false;
        bool isOn(){ return on; }
        void setOff() {on = false;}
        void setOn() { on = true;}
        void toggleOn() { on = !on; };

        void setTranslation(int _translation){
            translation = _translation;
        }
        
    private:
        int translation;
    };
    
    led ledGrid[5][14];
    
    
    void initGrid(){
        for (int i=0; i<gridX; i++) {
            for (int j=0; j<gridY; j++) {
                ledGrid[i][j].setTranslation(palmGrid[i][j]);
            }
        }
    }
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
    
    void setTimer(){
//        int timer = roll()
//        starBurstTimer.setTimer(
        
    }
    
    int gridX = 5;
    int gridY = 14;
    int counter = 0;
    int counterMod = 5;
    int middleX = 2;
    int middleY = 5;
    bool expanding = true;
    Metro starBurstTimer = Metro(100);

    
    void starBurst(){
    
        counter++;
        ledGrid[middleX][middleY].setOn(); //set middle LED to on
        int jump = 1;
        
        if(expanding){
            if(starBurstTimer.check()){
                for (int x=0; x<gridX; x++) {
                    for (int y=0; y<gridY; y++) {
                        if (ledGrid[x][y].isOn()) {
                            if(x<gridX && x >0 && y < gridY && gridY > 0){
                                counter++;
                                switch (counter%counterMod) {
                                    case 0:
                                        ledGrid[x+jump][y].setOn();
                                        break;
                                    case 1:
                                        ledGrid[x-jump][y].isOn();
                                        break;
                                    case 2:
                                        ledGrid[x][y+jump].isOn();
                                        break;
                                    case 3:
                                        ledGrid[x][y-jump].isOn();
                                        break;
                                    case 4:
                                        ledGrid[x-jump][y-jump].isOn();
                                        break;
                                    case 5:
                                        ledGrid[x+jump][y+jump].isOn();
                                        break;
                                    default:
                                        break;
                                }
                        }
                    }
                }
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
    

    void followFingersChase(){
        int colNum = int(s.rHand.getRoll(0,255));

        
        for(int i=0; i<5; i++){
            int controlNumber = s.getFlex(i, 0, fingerCt[i]);
            //Serial.print(controlNumber);
            for(int j = 0; j < fingerCt[i]; j++) {
                if(j == controlNumber){
                    leds[i][j].setHSV(colNum, 255, globalBright);
                }else{
                    leds[i][j].setHSV(0, 0, 0);
                }
            }
        }
        FastLED.show();
    }
    

    
    void followFingers(){
        
        int colNum = s.rHand.getRoll(0,255);
        
        //Serial.print(colNum);
        
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
    
    void runFire(int cooling, int sparking){
        
        random16_add_entropy( random());
        
        Fire2012(cooling,sparking); // run simulation frame
        FastLED.show(); // display this frame
        
#if defined(FASTLED_VERSION) && (FASTLED_VERSION >= 2001000)
        FastLED.delay(1000 / FRAMES_PER_SECOND);
#else
        delay(1000 / FRAMES_PER_SECOND);
#endif
        
    }
    void Fire2012(int cooling, int sparking){
        
        //COOLING = cooling;
        //SPARKING = sparking;
        
        
        
        
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
                heat[i] = qsub8( heat[i],  random8(0, ((cooling * 10) / NUM_LEDS) + 2));
            }
            
            // Step 2.  Heat from each cell drifts 'up' and diffuses a little
            for( int k= NUM_LEDS - 3; k > 0; k--) {
                heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
            }
            
            // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
            if( random8() < sparking ) {
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
    
    
    
    //update //get parameters from shape
    //display
    
    
    struct Format {
        
       
        
        //handPosition changeTrigger  -- i.e. for SHUKATUNDA, when the finger return to pataka with thumb still bent, the arrow is released
    };
    
    Format mFormat;
    
    
    
};


#endif
