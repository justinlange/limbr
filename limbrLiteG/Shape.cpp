//
// Shape.cpp 
// Class library C++ code
// ----------------------------------
// Developed with embedXcode+ 
// http://embedXcode.weebly.com
//
// Project 		limbrLiteG
//
// Created by 	Justin Lange, 4/16/14 7:27 PM
// 				Justin Lange
//
// Copyright 	(c) Justin Lange, 2014
// License		<#license#>
//
// See 			Shape.h and ReadMe.txt for references
//


// Library header
#include "Shape.h"

// Code
Shape::Shape() {
    
    
    
}


void Shape::init(){
    initSensors();
    initGestures();
    
    

}

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

bool considerGesture() {
    //if current gesture is changeGesture
        //load next gesture but don't activate it
    
        //if shake, activate next gesture
    return true;
}


void evalGesture(){
    
    for(int i = 0; i< NUM_GESTURES; i++ ){
        
        //gestures[i].getInfo();
        
        if(sameBesidesPinkie(cGesture, gestures[i])){
            //String printString = "at position: " + i;
            //Serial.print(printString);
            gestures[i].getInfo();
            //runSpell( gestures[i].getSpell() );
        }
        
    }
    //if(touchByte == mukula.getTouchPos()){
    //set current hand gesture to last hand gesture
    //set current hand gesture to mukula
    
}

void Shape::readSensors(bool print){
    
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

void Shape::initGestures(){
    
    int touchByte = B00000;
    /*
     / ' )   ./')
     /' /.--'   './'')
     :--''  ;    ''./'')
     :     '     ''./')
     :           ''./'
     :--''-..--''''
     */
    mukula.setPos(B11111, touchByte);  //trailing 0 is ignored
    thrisula.setPos(B01110, touchByte);
    
    
    gestures[0].setInfo("change", "change", B11111, B1111000, 0); //gesture primes receiving new gesture
    gestures[4].setInfo("pataka", "flag", B00000, B11110000, 4);
    gestures[1].setInfo("thrisula", "trident", B01110, B01100000, 1);
    //gestures[2].setInfo("makula", B111110, B00001);
    gestures[2].setInfo("Kartarimukha", "Arrow shaft", B10011, B00010011, 2);
    gestures[3].setInfo("Shikhara", "Heroism", B01111, B01110000, 3);
    
    
    /*  neutral gesuture turns off lights? or have this controlled by spell formulas while you are in it?
     _.-._
     | | | |_
     | | | | |
     | | | | |
   _ |  '-._ |
  \`\`-.'-._;
    \    '   |
     \  .`  /
     |    |
     */
    
    //gestures[3].setInfo("Mudrakhya",)
    //gestures[0].setPos(B111110, B001001);
    gestures[0].getInfo();
    
    
}//set gesture info for hand positions

void Shape::initSensors() {
    
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


void Shape::begin() {
    _data = 0;
}

String Shape::WhoAmI() {
    return "Shape";
}

void Shape::set(uint8_t data) {
    _data = data;
}

uint8_t Shape::get() {
    return _data; 
}

