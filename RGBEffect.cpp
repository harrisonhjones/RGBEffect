/*
	RGBEffect.cpp - Effect Library for the Spark Core's RGB LED.
	Created by Harrison H. Jones, Jan 25, 2015.
*/

#if defined (SPARK)
#include "application.h"
#else
#error "Only SparkCore RGB LED Supported."
#endif

#include "RGBEffect.h"

RGBEffect::RGBEffect(int pin)
{
	pinMode(pin, OUTPUT);
	_pin = pin;
	_time = millis();
	_brightness = 125;
	_fadeAmount = 5;    // how many points to fade the LED by
	_fadeDirection = _fadeAmount; 
	_ledState = 0;     // 0 = off, 1 = on, 2 = breath, 3 = fade down, 4 = fade up, 5 = blink
	_ledDelay = 30; // in ms
}

void RGBEffect::update()
{
	if((millis() - _time) > _ledDelay)
	{
		_time = millis();
		if(_ledState == 0)
			_brightness = 0;
		else if(_ledState == 1)
			_brightness = 255;
		else if (_ledState == 2)
		{
			// change the _brightness for next time through the loop:
			_brightness = _brightness + _fadeDirection;
			// reverse the direction of the fading at the ends of the fade:
			if (_brightness == 0)
				_fadeDirection = _fadeAmount;
			else if (_brightness == 255)
				_fadeDirection = -_fadeAmount;
		}
		else if (_ledState == 3)	// Fade down
		{
			// change the _brightness for next time through the loop:
			_brightness = _brightness - _fadeAmount;
			// reverse the direction of the fading at the ends of the fade:
			if (_brightness == 0)
				_brightness = 255;
		}
		else if (_ledState == 4)	// Fade up
		{
			// change the _brightness for next time through the loop:
			_brightness = _brightness + _fadeAmount;
			// reverse the direction of the fading at the ends of the fade:
			if (_brightness == 255)
				_brightness = 0;
		}
		else if(_ledState == 5)
		{
			if(_brightness == 255)
				_brightness = 0;
			else
				_brightness = 255;
		}
		else if(_ledState == 6) // Dim
		{
		}
	}
    analogWrite(_pin, _brightness);  
}
void RGBEffect::off()
{
	_ledState = 0;
	_ledDelay = 10;
}

void RGBEffect::on()
{
	_ledState = 1;
	_ledDelay = 10;
}

void RGBEffect::breath(int ledDelay)
{
    if(_brightness == 0)
        _fadeDirection = _fadeAmount;
    else if(_brightness == 255)
        _fadeDirection = -_fadeAmount;
	_ledState = 2;
	_ledDelay = ledDelay;
}

void RGBEffect::fadeDown(int ledDelay)
{
    if(_brightness == 0)
        _brightness = 255;
    _fadeDirection = -_fadeAmount;
	_ledState = 3;
	_ledDelay = ledDelay;
}

void RGBEffect::fadeUp(int ledDelay)
{
    if(_brightness == 255)
        _brightness = 0;
    _fadeDirection = _fadeAmount;
	_ledState = 4;
	_ledDelay = ledDelay;
}

void RGBEffect::blink(int ledDelay)
{
	_ledState = 5;
	_ledDelay = ledDelay;
}

void RGBEffect::dim(unsigned char brightness)
{
    _ledState = 6;
    _brightness = brightness;
    _ledDelay = 1000;   // Not really required. 
}
