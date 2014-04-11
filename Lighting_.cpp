//
// Lighting_.cpp 
// Class library C++ code
// ----------------------------------
// Developed with embedXcode+ 
// http://embedXcode.weebly.com
//
// Project 		limbrLiteG
//
// Created by 	Justin Lange, 3/20/14 10:05 PM
// 				Justin Lange
//
// Copyright 	(c) Justin Lange, 2014
// License		<#license#>
//
// See 			Lighting .h and ReadMe.txt for references
//


// Library header
#include "Lighting .h"

// Code
Lighting_::Lighting_() {
    
}

void Lighting_::begin() {
    _data = 0;
}

String Lighting_::WhoAmI() {
    return "Lighting_";
}

void Lighting_::set(uint8_t data) {
    _data = data;
}

uint8_t Lighting_::get() {
    return _data; 
}


