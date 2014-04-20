//
// Geometry_h_.cpp 
// Class library C++ code
// ----------------------------------
// Developed with embedXcode+ 
// http://embedXcode.weebly.com
//
// Project 		limbrLiteG
//
// Created by 	Justin Lange, 4/15/14 11:49 PM
// 				Justin Lange
//
// Copyright 	(c) Justin Lange, 2014
// License		<#license#>
//
// See 			Geometry.h .h and ReadMe.txt for references
//


// Library header
#include "Geometry.h .h"

// Code
Geometry_h_::Geometry_h_() {
    
}

void Geometry_h_::begin() {
    _data = 0;
}

String Geometry_h_::WhoAmI() {
    return "Geometry_h_";
}

void Geometry_h_::set(uint8_t data) {
    _data = data;
}

uint8_t Geometry_h_::get() {
    return _data; 
}

