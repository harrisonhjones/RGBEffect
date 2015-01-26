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
                RGB.control(true);
		if(_ledState == STATE_OFF)
                    RGB.color(0,0,0);
		else if(_ledState == STATE_ON)
                    RGB.color(_red[_destinationColor],_green[_destinationColor],_blue[_destinationColor]);
		else if (_ledState == STATE_BREATH)
		{
                    /*
			// change the _brightness for next time through the loop:
			_brightness = _brightness + _fadeDirection;
			// reverse the direction of the fading at the ends of the fade:
			if (_brightness == 0)
				_fadeDirection = _fadeAmount;
			else if (_brightness == 255)
				_fadeDirection = -_fadeAmount;*/
		}
		else if (_ledState == STATE_FADE)	// Fade down
		{
			/*// change the _brightness for next time through the loop:
			_brightness = _brightness - _fadeAmount;
			// reverse the direction of the fading at the ends of the fade:
			if (_brightness == 0)
				_brightness = 255;*/
		}
		else if (_ledState == STATE_BLINK)	// Fade up
		{
                    unsigned char temp = _destinationColor;
                    _destinationColor = _sourceColor;
                    _sourceColor = temp;
                    RGB.color(_red[_destinationColor],_green[_destinationColor],_blue[_destinationColor]);
		}
	} 
}
void RGBEffect::off()
{
    _ledState = STATE_OFF;
}

void RGBEffect::on(unsigned char colorNum)
{
    _ledState = STATE_ON;
    _destinationColor = colorNum;
}

void RGBEffect::breath(unsigned char colorNum1, unsigned char colorNum2)
{
    _ledState = STATE_BREATH;
    _sourceColor = colorNum1;
    _destinationColor = colorNum2;
}

void RGBEffect::fade(unsigned char colorNum1, unsigned char colorNum2)
{
    _sourceColor = colorNum1;
    _destinationColor = colorNum2;
    _ledState = STATE_FADE;
}

void RGBEffect::blink(unsigned char colorNum1, unsigned char colorNum2)
{
    _ledState = STATE_BLINK;
    _sourceColor = colorNum1;
    _destinationColor = colorNum2;
}

void RGBEffect::release()
{
    RGB.control(false);
}
void RGBEffect::setColor(unsigned char colorNum, unsigned int red, unsigned int green, unsigned int blue)
{
    _red[colorNum] = red;
    _green[colorNum] = green;
    _blue[colorNum] = blue;
    
}

void RGBEffect::setDelay(unsigned int ledDelay)
{
    _ledDelay = ledDelay;
}

void RGBEffect::swapColors(unsigned char colorNum1, unsigned char colorNum2)
{
    unsigned int red = _red[colorNum1];
    unsigned int green = _green[colorNum1];
    unsigned int blue = _blue[colorNum1];
    
    _red[colorNum1] = _red[colorNum2];
    _green[colorNum1] = _green[colorNum2];
    _blue[colorNum1] = _blue[colorNum2];
    
    _red[colorNum2] = red;
    _green[colorNum2] = green;
    _blue[colorNum2] = blue;
}