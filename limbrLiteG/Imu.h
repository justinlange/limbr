///
/// @file		Imu.h
/// @brief		Header
/// @details	<#details#>
/// @n	
/// @n @b		Project limbrLiteG
/// @n @a		Developed with [embedXcode+](http://embedXcode.weebly.com)
/// 
/// @author		Justin Lange
/// @author		Justin Lange
///
/// @date		5/9/14 11:17 PM
/// @version	<#version#>
/// 
/// @copyright	(c) Justin Lange, 2014
/// @copyright	<#license#>
///
/// @see		ReadMe.txt for references
///

#define HAND    1  //1 means right hand, -1 for left hand


#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_9DOF.h>

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



#ifndef Imu_h
#define Imu_h



//accelerometer data
class Imu
{
    
    int right = HAND;
    public:
    
    

    /* Assign a unique ID to the sensors */
    Adafruit_9DOF                 dof   = Adafruit_9DOF();
    Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(30301);
    Adafruit_LSM303_Mag_Unified   mag   = Adafruit_LSM303_Mag_Unified(30302);
    
    
    Imu(){
        
    }
    
    void calibrateHeading(){
        headingOffset = 0;
    }
    
    float getRoll() { return roll; }
    float getPitch() { return pitch; }
    float getheading() { return heading; }
    
    
    int getRoll(int min, int max){
        int val = map(roll, -180, 180, min, max);
        if(val<min) return min;
        if(val>max) return max;
        return val;
    }

    
    
    
    

//test

    float roll = 0;
    float pitch = 0;
    float heading = 0;
    
    float pitchUp = 90;
    float pitchDown = -90;
    float pitchFlat = 0;
    
#if HAND == 1
    float rollFlat = 0;
#else
    float rollFlat = 180;
#endif

    float rollUp = -90 * HAND;
    float rollDown = 90 * HAND;
    
    float rollThresh = 35;
    float pitchThresh = 35;
    
    float rollOffset = 0;
    float pitchOffset = 0;
    float headingOffset = 0;
    
    
    bool pointerUp()    {
        if(abs(pitch - pitchUp) < pitchThresh) return true; return false; }
    bool pointerDown()  {
        if(abs(pitch - pitchDown) < pitchThresh) return true; return false; }
    bool thumbUp()      {
        if(abs(roll - rollUp) < rollThresh) return true;
        return false;
    }
    bool thumbDown()      {  //guess. Could also be up
        if(abs(roll - rollDown) < rollThresh) return true;
        return false;
    }
    bool palmUp()     {
        if(abs(roll) - rollFlat < rollThresh && abs(pitch) - pitchFlat < pitchThresh) return true;
        return false;
    }

    
    bool palmDown()     {
        if(abs(roll) - pitchFlat < pitchThresh && abs(pitch) - pitchFlat < pitchThresh) return true;
        return false;
    }
    
    bool isShaking() {
        if(mShake.shaking) return true; return false;
    }
    

void printAll(){
    
    Serial.print(F("roll: "));
    Serial.print(roll);
    Serial.print(F("  pitch"));
    Serial.print(pitch);
    Serial.print(F(" heading "));
    Serial.print(heading);
    Serial.println(F(""));
}


    float initialHeading = 0;

    struct shake {
        float x = 0;
        float y = 0;
        float z = 0;
        float comp = 0;
        bool shaking;
        
        void update(){
            comp = sqrt(x*x + y*y + z*z);
            if(comp > thresh){
                shaking = true;
            }else{
                shaking = false;
            }
        }
        
        
    private:
        float thresh = 30;

    };
    
    shake mShake;
    
    //hand orientation states. Seperate bools for opposing positions allows
    //confirmation that hand is actually in known position as opposed to
    //somewhere in between
    
    void initIMU(){
        if(!accel.begin())
        {
            /* There was a problem detecting the LSM303 ... check your connections */
            Serial.println(F("Ooops, no LSM303 detected ... Check your wiring!"));
            while(1);
        }
        if(!mag.begin())
        {
            /* There was a problem detecting the LSM303 ... check your connections */
            Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
            while(1);
        }
    }
    void printDOFinfo(){
        
        sensors_event_t accel_event;
        sensors_event_t mag_event;
        sensors_vec_t   orientation;
        
        /* Read the accelerometer and magnetometer */
        accel.getEvent(&accel_event);
        mag.getEvent(&mag_event);
        
        /* Use the new fusionGetOrientation function to merge accel/mag data */
        if (dof.fusionGetOrientation(&accel_event, &mag_event, &orientation))
        {
            /* 'orientation' should have valid .roll and .pitch fields */
            Serial.print(F("Orientation: "));
            Serial.print(orientation.roll);
            Serial.print(F(" "));
            Serial.print(orientation.pitch);
            Serial.print(F(" "));
            Serial.print(orientation.heading);
            Serial.println(F(""));
        }
        
        delay(100);
        
        
        
    }
    
  


    void update(){
        
        sensors_event_t accel_event;
        sensors_event_t mag_event;
        sensors_vec_t   orientation;
        
        /* Read the accelerometer and magnetometer */
        accel.getEvent(&accel_event);
        mag.getEvent(&mag_event);
        
        /* Use the new fusionGetOrientation function to merge accel/mag data */
        if (dof.fusionGetOrientation(&accel_event, &mag_event, &orientation))
        {
        
            roll = orientation.roll + rollOffset;
            pitch = orientation.pitch + pitchOffset;
            heading = orientation.heading + headingOffset;
            
            
            mShake.x = accel_event.acceleration.x;
            mShake.y = accel_event.acceleration.y;
            mShake.z = accel_event.acceleration.z;
            
            mShake.update();


            }
        }
    
    void getShake(){
        
        /* Get a new sensor event */
        sensors_event_t event;
        
        /* Display the results (acceleration is measured in m/s^2) */
        accel.getEvent(&event);
        Serial.print(F("ACCEL "));
        Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print("  ");
        Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print("  ");
        Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print("  ");Serial.println("m/s^2 ");
        
        
        /* Display the results (magnetic vector values are in micro-Tesla (uT)) */
        mag.getEvent(&event);
        Serial.print(F("MAG   "));
        Serial.print("X: "); Serial.print(event.magnetic.x); Serial.print("  ");
        Serial.print("Y: "); Serial.print(event.magnetic.y); Serial.print("  ");
        Serial.print("Z: "); Serial.print(event.magnetic.z); Serial.print("  ");Serial.println("uT");
        
        /* Display the results (gyrocope values in rad/s) */
//        gyro.getEvent(&event);
//        Serial.print(F("GYRO  "));
//        Serial.print("X: "); Serial.print(event.gyro.x); Serial.print("  ");
//        Serial.print("Y: "); Serial.print(event.gyro.y); Serial.print("  ");
//        Serial.print("Z: "); Serial.print(event.gyro.z); Serial.print("  ");Serial.println("rad/s ");
        
//        Serial.println(F(""));
//        delay(1000);
        
        
        
        
    }
    
    
    //calibration
    
    float AccelMinX, AccelMaxX;
    float AccelMinY, AccelMaxY;
    float AccelMinZ, AccelMaxZ;
    float MagMinX, MagMaxX;
    float MagMinY, MagMaxY;
    float MagMinZ, MagMaxZ;
    long lastDisplayTime;
    
    void calibrateSensors(){
        /* Get a new sensor event */
        sensors_event_t accelEvent;
        sensors_event_t magEvent;
        
        accel.getEvent(&accelEvent);
        mag.getEvent(&magEvent);
        
        if (accelEvent.acceleration.x < AccelMinX) AccelMinX = accelEvent.acceleration.x;
        if (accelEvent.acceleration.x > AccelMaxX) AccelMaxX = accelEvent.acceleration.x;
        
        if (accelEvent.acceleration.y < AccelMinY) AccelMinY = accelEvent.acceleration.y;
        if (accelEvent.acceleration.y > AccelMaxY) AccelMaxY = accelEvent.acceleration.y;
        
        if (accelEvent.acceleration.z < AccelMinZ) AccelMinZ = accelEvent.acceleration.z;
        if (accelEvent.acceleration.z > AccelMaxZ) AccelMaxZ = accelEvent.acceleration.z;
        
        if (magEvent.magnetic.x < MagMinX) MagMinX = magEvent.magnetic.x;
        if (magEvent.magnetic.x > MagMaxX) MagMaxX = magEvent.magnetic.x;
        
        if (magEvent.magnetic.y < MagMinY) MagMinY = magEvent.magnetic.y;
        if (magEvent.magnetic.y > MagMaxY) MagMaxY = magEvent.magnetic.y;
        
        if (magEvent.magnetic.z < MagMinZ) MagMinZ = magEvent.magnetic.z;
        if (magEvent.magnetic.z > MagMaxZ) MagMaxZ = magEvent.magnetic.z;
        
        if ((millis() - lastDisplayTime) > 1000)  // display once/second
        {
            Serial.print("Accel Minimums: "); Serial.print(AccelMinX); Serial.print("  ");Serial.print(AccelMinY); Serial.print("  "); Serial.print(AccelMinZ); Serial.println();
            Serial.print("Accel Maximums: "); Serial.print(AccelMaxX); Serial.print("  ");Serial.print(AccelMaxY); Serial.print("  "); Serial.print(AccelMaxZ); Serial.println();
            Serial.print("Mag Minimums: "); Serial.print(MagMinX); Serial.print("  ");Serial.print(MagMinY); Serial.print("  "); Serial.print(MagMinZ); Serial.println();
            Serial.print("Mag Maximums: "); Serial.print(MagMaxX); Serial.print("  ");Serial.print(MagMaxY); Serial.print("  "); Serial.print(MagMaxZ); Serial.println(); Serial.println();
            lastDisplayTime = millis();
        }
    }
    
    
    
} ;





#endif
