//next: put spells in own class. then right function that has case statement that calls them. then have default spell that flashes white or something so we know nothing is there yet


//TO DO: reverse index flex se3nsor left hand


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
#include "Spell.h"


Metro metro0 = Metro(500);


bool flashState;

//void printDebug(String, int, float, float, bool);

int brightLevel;
int fla = 700;

void timerCheck();
void redBlue();
void adjustHue();
void initLEDs();
void cubulateSimple();
void palmJewel();
void runSpell(int spell);
void testGrid();

void followFingers();
void followFingersChase();


Shape s;
Spell mSpell;



const static int pixPins[] = {13,5,2,7,20};





//spells[numOfSpells];

//    13,5,2,7,20

void initLEDs() {
    

    
    
    
    
}

void setBrightness(){
    
    LEDS.setBrightness(brightLevel);
    

}



void setup() {
	// sanity check delay - allows reprogramming if accidently blowing power w/leds
   	delay(1500);

    initLEDs();
    s.init();

    
    Serial.begin(9600);
    
    
    
   Serial.print(s.WhoAmI());
    
    
    /*
     
     Spell::format fire;
     
     fire.blinkRate = 30;
     fire.startR = 255;
     
     
     Spell fireSpell = Spell(fire);
     
    spells[counter] = fireSpell;
     */
    
    
    while(millis() < 3000){
        s.calibrate();
    }
    
    
    //todo: make calebration get average
    s.storeCalibration();
    
    Serial.println("done calibrating!");
 
    
}
void loop() {
    
    //mSpell.followFingersChase();

    
    
    
    //timerCheck(); //fades green
    
    //xpalmJewel();
    //cubulateSimple();
    //adjustHue();
    s.readSensors(false);

    //s.rHand.printDOFinfo();
    
    mSpell.followFingers();


    
    
    
    
    //runSpell(s.spellID());
    
    
    //s.setTouchRead();
    
    //redBlue();
    //s.evalGesture();
    
    //delay(100);
    
    //int cooling = s.getFlex(0, 20, 100);
    //int sparking = s.getFlex(1, 50, 200);
    
    
    //runFire(cooling, sparking);

    
    //testGrid();

    
    
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

void adjustHue(){
    
    
    
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


    
    /*
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
     */

int showNum = 0;





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
                //delay(5);
                
                // Turn our current led back to black for the next loop around
                leds[i][whiteLed] = CRGB::Black;
            }
        }
    }
}



//#define COOLING  100
//#define SPARKING 10

/*
CHSV rotateHue(CRGB colorToChange, float changeFactor){
//    CHSV colorToChange = colorToChange.
  return
 
} */

//CHSV rgb2hsv(CRGB inColor);




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




