/*
	RGBEffect.cpp - Effect Library for the Spark Core's RGB LED.
	Created by Harrison H. Jones, Jan 25, 2015.
*/

#ifndef RGBEffect_h
#define RGBEffect_h

#if defined (SPARK)
#include "application.h"
#else
#error "Only SparkCore RGB LED Supported."
#endif

#define NUM_COLORS 255;

class RGBEffect
{
    public:
        RGBEffect();                    // Constructor
        void update();                  // Updates the LED's color/brightness
        void off();                     // Turns OFF the LED (dark)
        void on(unsigned char colorNum);// Turns ON the LED
        void breath();                  // Breaths between two colors
        void fade();                    // Fades from color 1 to 2
        void blink();                   // Blinks between two colors
        void release();                 // Releases control of the RGB object
        void setColor(unsigned char colorNum, unsigned int red, unsigned int green, unsigned int blue);
        void setDelay(unsigned int ledDelay);
        void swapColors();              // Swaps color 1 and color 2
    private:
        unsigned int _red[NUM_COLORS], _green[NUM_COLORS], _blue[NUM_COLORS];    // Different colors
        unsigned char _fadeAmount;    // how many points to fade the LED by
        unsigned char _fadeDirection; 
        unsigned char _ledState;     // 0 = off, 1 = on, 2 = breath, 3 = fade down, 4 = fade up, 5 = blink
        unsigned int _ledDelay; // in ms
        unsigned long _time;
};

#endif
