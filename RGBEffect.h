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

class RGBEffect
{
  public:
	RGBEffect(int pin);
	void update();
	void off();
	void on();
	void breath(int ledDelay);
	void fadeDown(int ledDelay);
	void fadeUp(int ledDelay);
	void blink(int ledDelay);
	void dim(unsigned char brightness);
  private:
	int _pin;
	unsigned char _brightness;
	unsigned char _fadeAmount;    // how many points to fade the LED by
	unsigned char _fadeDirection; 
	unsigned char _ledState;     // 0 = off, 1 = on, 2 = breath, 3 = fade down, 4 = fade up, 5 = blink
	int _ledDelay; // in ms
	unsigned long _time;
};

#endif
