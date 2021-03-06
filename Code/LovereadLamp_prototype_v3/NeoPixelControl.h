#ifndef NEOPIXELCONTROL_H
#define NEOPIXELCONTROL_H

#include <Adafruit_NeoPixel.h>  
#include<avr/io.h>
#include<avr/pgmspace.h>

#define PIN 7               // Ctrl output for NeoPixel RGB strip
#define WhiteLED 11         // PWM output for white LED
#define LIGHT_MIN 20        // Minimum value for the white LED output
// Constants
#define INCLINED_15DEG 256>>4                // Value of z-component at 15° inclination (2048*cos(15°)=1978) ( Range +/- 16g, resolution 16 bits, signed -> 2^15 = 16g, 2^11 = 1g )
// Shift it by 4 so that you can work with normal values, like 256
#define SHAKED 200    //Acc value for shaknig trigger


extern Adafruit_NeoPixel strip;  // Class that deals with neopixel
extern int plane_position;        // Rotation angle in x-y plane
extern bool shake;
extern boolean vertical;    // Indicates if the lamp is set completely vertical or still rising.

extern const uint8_t gamma[];  // Declaration of gamma corecttion LUT. The value is at the bottom of this sketch

void ChooseLED(int angle);
int16_t Intensity(int angle);
void RotateLamp(int omega);
void ColoredLamp(int angle);
static void DetectShake(int angle);
static void ChooseColor();
static void ColorIntensity(int position_lamp);
static uint32_t Wheel(byte WheelPos);


#endif
