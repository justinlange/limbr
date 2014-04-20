//
// Controller.cpp 
// Class library C++ code
// ----------------------------------
// Developed with embedXcode+ 
// http://embedXcode.weebly.com
//
// Project 		limbrLiteG
//
// Created by 	Justin Lange, 3/20/14 9:59 PM
// 				Justin Lange
//
// Copyright 	(c) Justin Lange, 2014
// License		<#license#>
//
// See 			Controller.h and ReadMe.txt for references
//


// Library header
#include "Controller.h"




// Code
Controller::Controller() {
    


    
}

void Controller::begin() {
    _data = 0;
}

void Controller::initSensors()
    {
        

    
    
    }





String Controller::WhoAmI() {
    return "Controller";
}

void Controller::set(uint8_t data) {
    _data = data;
}

uint8_t Controller::get() {
    return _data; 
}

void Controller::listen()
{

 
}


