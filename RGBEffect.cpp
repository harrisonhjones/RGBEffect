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
                
		if(_ledState == STATE_OFF)
                    _setColor(0,0,0);
		else if(_ledState == STATE_ON)
                    _setColor(0);
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
		else if (_ledState == STATE_FADE)
		{
                    // Fading starts at the current color in the sequence and then gradually moves toward the next one. 
                    // Once it reaches the end of the sequence it abruptely transitions t the first color in the sequence
                    /*if(_colorDiff(_colorSequence[_colorSequenceIndex + 1]) == 0)    // We are at the next color
                    {
                        if((_colorSequenceIndex + 1) >= _colorSequenceNum)    // We are at the end of the sequence
                        {
                            _colorSequenceIndex = 0;
                            _se
                        }
                        _colorSequenceIndex = 0;
                    }
                    _moveTowardsColor(unsigned int colorNum)*/
		}
		else if (_ledState == STATE_BLINK)
		{
                    _setColorS(_colorSequenceIndex);
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

/**
 _colorDiff
 
 Returns the absolute difference between two colors: the active color and the 
 color designated by colorNum
 */
unsigned int RGBEffect::_colorDiff(unsigned int colorNum)
{
    unsigned int redDiff = abs(_currRed - _red[colorNum]);
    unsigned int greenDiff = abs(_currGreen - _green[colorNum]);
    unsigned int blueDiff = abs(_currBlue - _blue[colorNum]);
    return redDiff + greenDiff + blueDiff;
}

void RGBEffect::_moveTowardsColor(unsigned int colorNum)
{
    if(_colorDiff(colorNum) == 0)
        return;
    
    if (_currRed > (_red[colorNum] + FADE_AMOUNT))
        _currRed -= FADE_AMOUNT;
    else if(_currRed < (_red[colorNum] - FADE_AMOUNT))
        _currRed += FADE_AMOUNT;
    else
        _currRed = _red[colorNum];
    
    if (_currGreen > (_green[colorNum] + FADE_AMOUNT))
        _currGreen -= FADE_AMOUNT;
    else if(_currRed < (_green[colorNum] - FADE_AMOUNT))
        _currGreen += FADE_AMOUNT;
    else
        _currGreen = _green[colorNum]; 
    
    if (_currBlue > (_blue[colorNum] + FADE_AMOUNT))
        _currBlue -= FADE_AMOUNT;
    else if(_currBlue < (_blue[colorNum] - FADE_AMOUNT))
        _currBlue += FADE_AMOUNT;
    else
        _currBlue = _blue[colorNum]; 
    
    _setColor(_currRed,_currGreen,_currBlue);
}

void RGBEffect::_setColor(unsigned int red, unsigned int green, unsigned int blue)
{
    RGB.control(true);
    RGB.color(red,green,blue);
    _currRed = red;
    _currGreen = green;
    _currBlue = blue;
}

void RGBEffect::_setColor(unsigned char colorNum)
{
    _setColor(_red[colorNum],_green[colorNum],_blue[colorNum]);
}

void RGBEffect::_setColorS(unsigned char sequenceIndex)
{
    _setColor(_colorSequence[sequenceIndex]);
}
