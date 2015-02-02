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
                    if(_colorDiff(_colorSequence[_colorSequenceIndex]) == 0)    // We have reached the current color
                    {
                        _colorSequenceIndex++;
                        if(_colorSequenceIndex >= _colorSequenceNum)
                            _colorSequenceIndex = 0;
                    }
                    _moveTowardsColorS(_colorSequenceIndex);
		}
		else if (_ledState == STATE_FADE)
		{
                    // Fading starts at the current color in the sequence and then gradually moves toward the next one. 
                    // Once it reaches the end of the sequence it abruptely transitions t the first color in the sequence
                    if(_colorDiff(_colorSequence[_colorSequenceIndex]) == 0)    // We have reached the current color
                    {
                        _colorSequenceIndex++;
                        if(_colorSequenceIndex >= _colorSequenceNum)
                        {
                            _colorSequenceIndex = 0;
                            _setColorS(_colorSequenceIndex);
                        }
                    }
                    _moveTowardsColorS(_colorSequenceIndex);
                    
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
    _colorSequenceIndex = 0;
}

void RGBEffect::fade(unsigned int colorNumSeq[], unsigned int numInSeq)
{
    _ledState = STATE_FADE;
    _copySequence(colorNumSeq, numInSeq);
    _colorSequenceIndex = 0;
    _setColorS(_colorSequenceIndex); // Instantly transition to the first color
}

void RGBEffect::blink(unsigned int colorNumSeq[], unsigned int numInSeq)
{
    _ledState = STATE_BLINK;
    _copySequence(colorNumSeq, numInSeq);
}

void RGBEffect::release()
{
    _ledState = STATE_RELEASED;
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
    
    int redDiff = _currRed - _red[colorNum];
    int greenDiff = _currGreen - _green[colorNum];
    int blueDiff = _currBlue - _blue[colorNum];
    
    if (abs(redDiff) <= FADE_AMOUNT)
    {
        Serial.println("redDiff ~= FADE_AMOUNT");
        _currRed = _red[colorNum];
    }
    else
    {
        if (redDiff > FADE_AMOUNT)
        {
            _currRed -= FADE_AMOUNT;
            Serial.println("redDiff > FADE_AMOUNT");
        }
        else
        {
            Serial.println("redDiff < FADE_AMOUNT");
            _currRed += FADE_AMOUNT;
        }
    }
    
    if (abs(greenDiff) <= FADE_AMOUNT)
    {
        _currGreen = _green[colorNum];
    }
    else
    {
        if (greenDiff > FADE_AMOUNT)
        {
            _currGreen -= FADE_AMOUNT;
        }
        else
        {
            _currGreen += FADE_AMOUNT;
        }
    }
    
    if (abs(blueDiff) <= FADE_AMOUNT)
    {
        _currBlue = _blue[colorNum];
    }
    else
    {
        if (blueDiff > FADE_AMOUNT)
        {
            _currBlue -= FADE_AMOUNT;
        }
        else
        {
            _currBlue += FADE_AMOUNT;
        }
    }
    
    _setColor(_currRed,_currGreen,_currBlue);
}

void RGBEffect::_moveTowardsColorS(unsigned int sequenceIndex)
{
    _moveTowardsColor(_colorSequence[sequenceIndex]);
}

void RGBEffect::_setColor(unsigned int red, unsigned int green, unsigned int blue)
{
    if(red > MAX_RGB_VALUE)
        red = MAX_RGB_VALUE;
    if(green > MAX_RGB_VALUE)
        green = MAX_RGB_VALUE;
    if(blue > MAX_RGB_VALUE)
        blue = MAX_RGB_VALUE;
    
    RGB.control(true);
    RGB.color(red,green,blue);
    _currRed = red;
    _currGreen = green;
    _currBlue = blue;
    Serial.print(red);
    Serial.print(",");
    Serial.print(green);
    Serial.print(",)");
    Serial.println(blue);
}

void RGBEffect::_setColor(unsigned char colorNum)
{
    _setColor(_red[colorNum],_green[colorNum],_blue[colorNum]);
}

void RGBEffect::_setColorS(unsigned int sequenceIndex)
{
    _setColor(_colorSequence[sequenceIndex]);
}
