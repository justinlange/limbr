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
    rHand = Imu();
    rHand.initIMU();
}


typedef struct
{
    String name;
    int lowRead;
    int highRead;
    int rawVal;
    int mapVal;
    boolean isHigh;
    
    void setPin(int _pin) { pin = _pin; }
    int getPin() { return pin; }
    
    int pMap(int min, int max){
        int mMap = map(rawVal, lowRead, highRead, min, max);
        mMap = max(mMap, 0);
        return mMap;
    }
    
private:
    int pin;
    
} sensor;
sensor flex[5];

typedef struct
{
    String name;
    int writingTo;
    boolean isHigh;
    
    
    int getPin() { return pin; }
    void setPin(int _pin) { pin = _pin; }
    void printInfo(){
        Serial.print(name);
        Serial.print(" on pin ");
        Serial.print(pin);
        Serial.print(", writing to ");
        Serial.print(writingTo);
        Serial.print("  and is ");
        Serial.println(isHigh);

        
        
    }
    
private:
    int pin;
    
} touchSensor;
touchSensor touch[5];



typedef struct
{
    void setPos(byte _bendPos, byte _touchPos, int _dirPos)
    {
        bendPos = _bendPos;
        touchPos = _touchPos;
        dirPos = _dirPos;
    }
    
    byte getTouchPos() { return touchPos; }
    byte getBendPos()  { return bendPos ; }
    int getDirPos() { return dirPos; }
    
    byte spgetBendPos()  {
        byte tPos = bendPos | 1;
        return tPos ;
    }
    
    
    
    void setInfo(String _sanskrit, String _english, byte _bendPos, byte _touchPos, byte _dirPos){
        
        sanskrit = _sanskrit;
        english = _english;
        bendPos = _bendPos;
        touchPos = _touchPos;
        dirPos = _dirPos;
        //spell = _spell; // deprecated -- spells will be assigned to gestures in case statement in main loop
    }
    
    void getInfo(){
        String printString = "name  " + sanskrit + "  benPos: " + bendPos + "  touchPos: " + touchPos + " dirPos: " + dirPos;
        Serial.println(printString);
    }
    
    void setFingerPos(int space, bool val){
        fingerPos[space] = val;
        
    }
    
    void setThumbPos(int space, bool val){
        thumbPos[space] = val;
        
    }

    
    
    
    
private:
    String sanskrit, english;
    byte bendPos, touchPos;
    bool fingerPos[4];
    bool thumbPos[4];
    int dirPos;
    int spell;
    
    
} gesture;
gesture cGesture;
gesture gestures[NUM_GESTURES];



void Shape::calibrate(){
    for(int i=0;i<5;i++){
        if(analogRead(flex[i].getPin()) < flexLow[i]){
            flexLow[i] = analogRead(flex[i].getPin());
        }
        if(analogRead(flex[i].getPin()) > flexHigh[i]){
            flexHigh[i] = analogRead(flex[i].getPin());
        }
    }
    
    
    
}

/*

int Shape::getRoll(int min, int max){
    int val = map(rHand.getRoll(), -90,90, min, max);
  
 */
    


int Shape::getFlex(int finger, int min, int max){
    int val = flex[finger].pMap(min, max);
    if(val<min) return min;
    if(val>max) return max;
    return val;
    
    
}


void Shape::setTouchRead(){
    
    for(int i=0;i<5;i++){
        
        pinMode(touch[i].getPin(), OUTPUT);
        digitalWrite(touch[i].getPin(), HIGH);
        
        for(int j=0;j<5;j++){
            if(j != i){
                /*
                 Serial.print("i: ");
                 Serial.print(i);
                 Serial.print("   j: ");
                 Serial.println(j);
                 */
                pinMode(touch[j].getPin(), INPUT);
                boolean myBool = digitalRead(touch[j].getPin());
                if(myBool) whichPin(j,i);
            }  
        }
        digitalWrite(touch[i].getPin(), LOW);
    }

    
}

void Shape::whichPin(int writePin, int readPin){
    Serial.print("pin: ");
    switch(writePin){
        case 0:
            Serial.print(touch[writePin].getPin());
            break;
        case 1:
            Serial.print(touch[writePin].getPin());
            break;
        case 2:
            Serial.print(touch[writePin].getPin());
            break;
        case 3:
            Serial.print(touch[writePin].getPin());
            break;
        case 4:
            Serial.print(touch[writePin].getPin());
            break;
    }
    Serial.print(" is writing to ");
    Serial.println(touch[readPin].getPin());
    
    
}


void Shape::readSensors(bool print){
    
    int dirPos = 0;

    rHand.update();
    
    int bendByte = 0;
    int touchByte = 0;
    
    for (int i=0; i<5; i++) {
        flex[i].rawVal = analogRead(flex[i].getPin());
        flex[i].mapVal = map(flex[i].rawVal, flex[i].lowRead, flex[i].highRead, 0, 100);
        if (flex[i].mapVal > bendThresh) {
            //Serial.print("crossed bend thresh");
            flex[i].isHigh = true;
            bendByte = bendByte | 1;
            
        }else{
            flex[i].isHigh = false;
        }
        if(i<4){
            bendByte = bendByte << 1;
        }
        
        
        
        
        
        /*  read finger states   */
        
        //first do non-thumb digits

        for (int i=0; i<5; i++) {
            for (int j=0; j<5; j++) {
                touch[i].writingTo = false;
                touch[i].isHigh = false;
            }
        }
        
        for(int i=0;i<4;i++){
            
            pinMode(touch[i].getPin(), OUTPUT);
            digitalWrite(touch[i].getPin(), HIGH);
            
            int j = i + 1;
                pinMode(touch[j].getPin(), INPUT);
                touch[j].isHigh = digitalRead(touch[j].getPin());
        
                    if(touch[j].isHigh) {
                       
                       // touch[i].printInfo();
                        //touch[j].printInfo();
                        
                        touchByte = touchByte | 1;
                        touch[i].isHigh = true;
                        touch[i].writingTo = touch[j].getPin();

                    }else{
                        touchByte = touchByte << 1;
                       
                    }
            digitalWrite(touch[i].getPin(), LOW);
        }
        
        //find what digits thumb is touching
        
        for (int i=0; i<5; i++) {
            for (int j=0; j<5; j++) {
                touch[i].writingTo = false;
                touch[i].isHigh = false;
            }
        }

        pinMode(touch[0].getPin(), OUTPUT);

        for(int i=1;i<5;i++){
            pinMode(touch[i].getPin(), INPUT);
            bool myBool = digitalRead(touch[i].getPin());
           
            if(myBool) {
                Serial.print("  reading from thumb: ");
                touch[i].printInfo();
                touchByte = touchByte | 1;
            }else{
                touchByte = touchByte << 1;
            }

        }
        
        
        if (rHand.pointerUp()) dirPos = 1;
        if (rHand.pointerDown()) dirPos = 2;
        if (rHand.thumbUp()) dirPos = 3;
        if (rHand.thumbDown()) dirPos = 4;
        if (rHand.palmUp()) dirPos = 5;
        if (rHand.palmDown()) dirPos = 6;
        
        cGesture.setPos(bendByte, touchByte, dirPos);

        if(print){
            /*
            Serial.print(flex[i].name);
            Serial.print(" raw: ");
            Serial.print(flex[i].rawVal);
            Serial.print(", map: ");
            Serial.print(flex[i].mapVal);
            Serial.print(", isHigh: ");
            Serial.print(flex[i].isHigh);

            Serial.print("  ");
             */
        }
        
       
        
    }

    Serial.print("touchByte:  ");
        for(int i = 0; i< 8; i++){
            
        }

    
    if(print) {
        Serial.print(",  dirPos");
        Serial.print(dirPos);
        rHand.printAll();
        Serial.print(",  dirPos");
    }
    
    
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

    
    //add accel state....
    

    gestures[0].setInfo("none","none",B00000000,B00000000,B000000);
    gestures[1].setInfo("PATAKA","Flag", B00000, B11110000,	1);
    gestures[2].setInfo("TRIPATAKA", "Flag with three fingers", B00010, B00110000, 1);
    gestures[3].setInfo("KARTARIMUKHA",	"Scissors blades", B10010,B00000000,1);
    gestures[4].setInfo("ARDHACHANDRA","Crescent Moon",	B00000,	B11110000,	3);
    gestures[5].setInfo("ARALA",	"Bent",	B11000,	B01110000,	B100000);
    gestures[6].setInfo("SHUKATUNDA","Parrots beak",	B11010, B00000000, 1);
    gestures[7].setInfo("MUSHTI", "The first",	B11111,	B11111111,	3);
    gestures[8].setInfo("SHIKHARA",	"Peak",	B01111,	B11110000,	3);
    gestures[9].setInfo("KAPITTA","wood apple",B01111,  B01110111,1);
    gestures[10].setInfo("KATAKAMUKHA",	"Bracelet's lock",	B01100,	B00001000,	1);
    gestures[11].setInfo("SUCHI", "Needle",	B00111	,B01110111,	1);
    gestures[12].setInfo("PADMAKOSHA", "Lotus bud",	B11111,	B00000000,	5);
    gestures[13].setInfo("SARPASIRSHA",	"Snakes head",	B01111	,B11110000,	1);
    gestures[14].setInfo("MRIGASIRSHA",	"Deers head", B01110, B11100000,	1);
    gestures[15].setInfo("LANGULA", "unknown", B00010,	B00000000, 5);
    gestures[16].setInfo("ALAPADMA","Lotus",B00111,	B00000000,5);
    gestures[17].setInfo("CHATURA",	"Four",	B10000,	B01110000,	1);
    gestures[18].setInfo("BHRAMARA", "Bee",	B01100,	B00000100,	1);
    gestures[19].setInfo("HAMSASYA", "Swan's beak",	B01000,	B00001000, 1);
    gestures[20].setInfo("HAMSAPAKSHA", "Swan's wing", B10000,	B11100000,	1);
    gestures[21].setInfo("SANDAMSA", "Pincers",	B11000,	B00001000,	1);
    gestures[22].setInfo("MUKALA","Bud",B01111,	B11111111,	5);
    gestures[23].setInfo("URNANABHA", "Spider",	B11111,	B00000000,	1);
    gestures[24].setInfo("TAMRACHUDA", "Cock",	B01111,	B00110100,	1);
    
 
    /*
    gestures[0].setInfo("change", "change", B11111, B1111000, 0); //gesture primes receiving new gesture
    gestures[4].setInfo("pataka", "flag", B00000, B11110000, 4);
    gestures[1].setInfo("thrisula", "trident", B01110, B01100000, 1);
    //gestures[2].setInfo("makula", B111110, B00001);
    gestures[2].setInfo("Kartarimukha", "Arrow shaft", B10011, B00010011, 2);
    gestures[3].setInfo("Shikhara", "Heroism", B01111, B01110000, 3);
     */
    
    
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
    	gestures[1].getInfo();
    
    
}//set gesture info for hand positions

void Shape::initSensors() {
    
    for (int i=0; i<5; i++) {
        //flex[i] = sensor();
        flex[i].setPin(analogInPins[i]);
        flex[i].name = fingerNames[i];
        flex[i].lowRead = flexLow[i];
        flex[i].highRead = flexHigh[i];
        flex[i].isHigh = false;
        pinMode(flex[i].getPin(), INPUT);
        
        touch[i].setPin(touchPins[i]);
        touch[i].name = fingerNames[i];
        touch[i].isHigh = false;
    }
    
    
}

void Shape::storeCalibration(){
    
        for (int i=0; i<5; i++) {
            int difference = flexHigh[i] - flexLow[i];
            int buffer = difference/17;
            
            flex[i].lowRead = flexLow[i] + buffer;
            flex[i].highRead = flexHigh[i] - buffer;
        }  
}




bool Shape::considerGesture() {
    //if current gesture is changeGesture
    //load next gesture but don't activate it
    
    //if shake, activate next gesture
    return true;
}

//for evaluating gestures, look at flex positions and only loosly consider (or not at all) touch positions
//between fingers that are bent


 void Shape::evalGesture(){
 
     for(int i = 1; i< NUM_GESTURES; i++ ){
         if(cGesture.getBendPos() == gestures[i].getBendPos()){
             if(cGesture.getTouchPos() == gestures[i].getTouchPos()){
                 if(cGesture.getDirPos() == gestures[i].getDirPos())    {
                     Serial.print("full match  ");
                     gestures[i].getInfo();

                 }
             }
         }
    }
   
 //String printString = "at position: " + i;
 //Serial.print(printString);

 }
 //if(touchByte == mukula.getTouchPos()){
 //set current hand gesture to last hand gesture
 //set current hand gesture to mukula
 

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

