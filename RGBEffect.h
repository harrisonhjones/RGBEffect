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

#define NUM_COLORS 255
#define STATE_OFF 0
#define STATE_ON 1
#define STATE_BREATH 2
#define STATE_FADE 3
#define STATE_BLINK 4

class RGBEffect
{
    public:
        RGBEffect();                    // Constructor
        void update();                  // Updates the LED's color/brightness
        void off();                     // Turns OFF the LED (dark)
        void on(unsigned char colorNum);// Turns ON the LED
        void breath(unsigned char colorNum1, unsigned char colorNum2);                  // Breaths between two colors
        void fade(unsigned char colorNum1, unsigned char colorNum2);                    // Fades from color 1 to 2
        void blink(unsigned char colorNum1, unsigned char colorNum2);                   // Blinks between two colors
        void release();                 // Releases control of the RGB object
        void setColor(unsigned char colorNum, unsigned int red, unsigned int green, unsigned int blue);
        void setDelay(unsigned int ledDelay);
        void swapColors(unsigned char colorNum1, unsigned char colorNum2);
    private:
        unsigned int _red[NUM_COLORS];
        unsigned int _green[NUM_COLORS];
        unsigned int _blue[NUM_COLORS];    // Different colors
        unsigned char _fadeAmount;    // how many points to fade the LED by
        unsigned char _fadeDirection; 
        unsigned char _ledState;     
        unsigned int _ledDelay; // in ms
        unsigned long _time;
        unsigned char _destinationColor;
        unsigned char _sourceColor;
};

#endif
