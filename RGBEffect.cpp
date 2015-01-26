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

RGBEffect::RGBEffect()
{
	_time = millis();
	_fadeAmount = 5;    // how many points to fade the LED by
	_fadeDirection = _fadeAmount; 
	_ledState = 0;     // 0 = off, 1 = on, 2 = breath, 3 = fade down, 4 = fade up, 5 = blink
	_ledDelay = 30; // in ms
        // Color 1 = White
        _red[0] = 255;
        _green[0] = 255;
        _blue[0] = 255;
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
    RGB.control(true);
    RGB.color(0,0,0);
    _ledState = 0;
    _ledDelay = 10;
}

void RGBEffect::on(unsigned char colorNum)
{
    RGB.control(true);
    RGB.color(_red[colorNum],_green[colorNum],_blue[colorNum]);
    _ledState = 1;
    _ledDelay = 10;
}

void RGBEffect::breath()
{
    if(_brightness == 0)
        _fadeDirection = _fadeAmount;
    else if(_brightness == 255)
        _fadeDirection = -_fadeAmount;
	_ledState = 2;
	_ledDelay = ledDelay;
}

void RGBEffect::fade()
{
    if(_brightness == 255)
        _brightness = 0;
    _fadeDirection = _fadeAmount;
	_ledState = 4;
	_ledDelay = ledDelay;
}

void RGBEffect::blink()
{
	_ledState = 5;
	_ledDelay = ledDelay;
}

void RGBEffect::release();                 // Releases control of the RGB object
void RGBEffect::setColor(unsigned char colorNum, unsigned int red, unsigned int green, unsigned int blue);
void RGBEffect::setDelay(unsigned int ledDelay);
void RGBEffect::swapColors(); 