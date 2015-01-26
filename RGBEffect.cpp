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
        _colorSequence[0] = 0;
        _colorSequenceNum = 1;
        _colorSequenceIndex = 0;    // Point to the first entry in _colorSequence
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
                    RGB.color(_red[_colorSequence[0]],_green[_colorSequence[0]],_blue[_colorSequence[0]]);
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
                    RGB.color(_red[_colorSequence[_colorSequenceIndex]],_green[_colorSequence[_colorSequenceIndex]],_blue[_colorSequence[_colorSequenceIndex]]);
                    _colorSequenceIndex++;
                    if(_colorSequenceIndex >= _colorSequenceNum)
                        _colorSequenceIndex = 0;
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
    _colorSequence[0] = colorNum;
    _colorSequenceNum = 1;
}

void RGBEffect::breath(unsigned int colorNumSeq[], unsigned int numInSeq)
{
    _ledState = STATE_BREATH;
    _copySequence(colorNumSeq, numInSeq);
}

void RGBEffect::fade(unsigned int colorNumSeq[], unsigned int numInSeq)
{
    _ledState = STATE_FADE;
    _copySequence(colorNumSeq, numInSeq);
}

void RGBEffect::blink(unsigned int colorNumSeq[], unsigned int numInSeq)
{
    _ledState = STATE_BLINK;
    _copySequence(colorNumSeq, numInSeq);
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

void RGBEffect::_copySequence(unsigned int colorNumSeq[], unsigned int numInSeq)
{
    if(numInSeq > MAX_SEQUENCE_LENGTH)  // Truncate if too many in sequence
        numInSeq = MAX_SEQUENCE_LENGTH;
    for(unsigned int i=0;i<numInSeq;i++)
        _colorSequence[i] = colorNumSeq[i];
    _colorSequenceNum = numInSeq;
}