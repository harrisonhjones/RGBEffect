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
#define MAX_SEQUENCE_LENGTH 10
#define FADE_AMOUNT 5

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
        void breath(unsigned int colorNumSeq[], unsigned int numInSeq);                  // Breaths between two colors
        void fade(unsigned int colorNumSeq[], unsigned int numInSeq);                    // Fades from color 1 to 2
        void blink(unsigned int colorNumSeq[], unsigned int numInSeq);                   // Blinks between colors
        void release();                 // Releases control of the RGB object
        void setColor(unsigned char colorNum, unsigned int red, unsigned int green, unsigned int blue);
        void setDelay(unsigned int ledDelay);
        void swapColors(unsigned char colorNum1, unsigned char colorNum2);
    private:
        unsigned int _currRed;
        unsigned int _currGreen;
        unsigned int _currBlue;
        unsigned int _red[NUM_COLORS];
        unsigned int _green[NUM_COLORS];
        unsigned int _blue[NUM_COLORS];    // Different colors
        unsigned char _fadeAmount;    // how many points to fade the LED by
        unsigned char _fadeDirection; 
        unsigned char _ledState;     
        unsigned int _ledDelay; // in ms
        unsigned long _time;
        unsigned int _colorSequence[MAX_SEQUENCE_LENGTH];
        unsigned int _colorSequenceNum;
        unsigned int _colorSequenceIndex;
        void _copySequence(unsigned int colorNumSeq[], unsigned int numInSeq);
        unsigned int _colorDiff(unsigned int colorNum);
        void _moveTowardsColor(unsigned int colorNum);
        void _setColor(unsigned int red, unsigned int green, unsigned int blue);
        void _setColor(unsigned char colorNum);
        void _setColorS(unsigned char sequenceIndex);
};

#endif
