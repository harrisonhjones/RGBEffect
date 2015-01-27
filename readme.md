RGBEffect
===========

A RGB effects library for Spark Core. 

# Installation
## SparkCore (OTA for Demoing)

* Navigate to [The Demo Web App](hhj.me/rgblibrarydemo)
* Follow the instructions to flash the latest demo firmware to your Spark Core over the air (OTA) and control it once it's there.

## SparkCore (for Development)

* Add RGBEffect.cpp & RGBEffect.h to your project
* Add a #include "RGBEffect.h" to the top of your main project file
* Look at the demos/usage below

## Usage
This library is much more complicated than my original LEDEffect library, which this library is loosely based on. To use this library you must first define colors (sort of like a color palette) and then you can use those defined colors with different effects. 

### List of Available Effects

* off - turns the RGB LED off
* on - assigned a specified color to the RGB LED
* breath - smoothly fades between the different colors designed by the colorNumSequence which is an array of color numbers
* fade - similar to breath but when the end of the sequence is reached the first color is jumped to sharply. Can be used to create a near fading up or fading down effect
* blink - blinks the color sequence

### Interacting with Colors

* setColor - used to associate a red, green, blue color to a specific color number
* swapColors - used to swap two colors in the palette

### Other Functions

* update - should be called in your main loop. The more often it is called the smoother the animations are
* release - releases control of the RGB LED (so it will behave normally (breathing cyan))
* setDelay - used to change how fast or slow an animation plays

### Example Application

    #include "RGBEffect.h"

    SYSTEM_MODE(AUTOMATIC);

    // Define the RGB Effect object
    RGBEffect led;

    /* This function is called once at start up ----------------------------------*/
    void setup()
    {
        // Define a few colors           
        led.setColor(0,0,0,0);          // Dark / Off
        led.setColor(1,255,0,0);        // Red
        led.setColor(2,255,255,0);      // Yellow
        led.setColor(3,0,255,0);        // Green
        led.setColor(4,0,255,255);      // Cyan
        led.setColor(5,0,0,255);        // Blue
        led.setColor(6,255,0,255);      // Magenta
        led.setColor(7,255,255,255);    // White
        
        // Define a color sequence of 6 colors
        unsigned int colorSeq[6] = {1,2,3,4,5,6};   // Red, White, Blue, Green
        
        // Set the delay to fairly quick blink
        led.setDelay(150);
        // Blink the LED 
        led.blink(colorSeq,6);

        // Commented Out Breath Demo. Uncomment the two //led lines below for a LED breath effect
        // Set the delay to a fairly quick breath
        //led.setDelay(50);
        // Breath the LED between the colors in the color sequence
        //led.breath(colorSeq,6);
    }

    /* This function loops forever --------------------------------------------*/
    void loop()
    {
        led.update();
    }

