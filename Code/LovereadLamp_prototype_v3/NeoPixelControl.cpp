#include "NeoPixelControl.h"

Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, PIN, NEO_GRB + NEO_KHZ800);  // Class that deals with neopixel
boolean vertical = LOW;    // Indikator jeli lampa postavljena vertikalno ili se podiže
bool shake = 0;
uint32_t color = 0x000000FF; // 32-bit color code, upper 8 bits, nothing, next 8 bits: RED, next 8 bits: GREEN, lowest 8 bits: BLUE

uint8_t LampIntensity = 0;         // Lamp intensity control
int plane_position = 0;        // Rotation angle in x-y plane

void TurnLampOn(int angle) {
  /*  Lamp turns on when inclined more than 15° with the dimmed light.
   *  Light intensifies to 50% as the lamp comes to vertical position
   *  Shift right for 3 to beacuse the light is painful*/
 // int plane = plane_position; 

  if ((angle >= INCLINED_15DEG) && (angle < 117)) {      // When lamp is moving from horizontal to vertical position, light intensity rises proportionally to 50% of the maximum
    if (!vertical) {
      LampIntensity = (angle>>1);
      plane_position = 0;
      }
    else 
       if (angle <= 100){    // Arbitrarily chosen value at the border of region where LampIntensity = angle>>1 and region where LampIntensity = angle>>1 + plane_position
           vertical = LOW;
           LampIntensity = (angle>>1); 
           plane_position = 0;
       }
       else
           LampIntensity = (angle>>1) + plane_position;
  }
  
  else if ((angle >= 117) && (angle <= 150)) {           // When lamp is more or less vertically positioned, light intensity is regulated by rotation
      if (!vertical)          
          vertical = HIGH;
      LampIntensity = (angle>>1) + plane_position;
      if (LampIntensity >= (254))
          LampIntensity = (254);
      if (LampIntensity <=1)
          LampIntensity = 1;
  }
  
  else
      LampIntensity = 0; 
}

void RotateLamp(int omega) {
  /* In vertical position (along the z axis) the gyro measures
   *  angular velocity in about the z-axis and this function calculates
   *  rotation angle in x-y plane */
  int rot_offset = 200;      // There is non-zero sensor output when the lamp is not rotating.
  if (( omega > rot_offset) || (omega < (~rot_offset + 1)))
    plane_position += (omega>>8);  // scale with 2000°/s and mulitply with 10ms, equals dividing with 200 or shifting for 2^8 = 256
//  plane_position = plane_position % 360; 

  if (plane_position > 255) // Make sure plane position is between -255 and 255, Optimize later
     plane_position = 255;
  if (plane_position < -255)
     plane_position = -255;
}

void ColoredLamp(int angle) {
  /*  In the upside down position, power LED turns off and colored LED turns on
   *  The color and intensity is regulated by rotation in x-y plane.
   */
   
  DetectShake(angle);   // Check if we have shaked the lamp
   
  if ((angle <= -108) && (angle >= -136) && !shake ) {         // when the lamp is upside down, it's time to turn on the colored LEDs
    Serial.println("Color LED Mode!");
    LampIntensity = 0;  // Turn the power LED off.
    ColorIntensity();
  } 
  else if ((angle <= -108) && (angle >= -136) && shake ) {         // when the lamp is upside down, and shaked, you have 5 seconds to chose your color
    Serial.println("Color LED Mode!");
    LampIntensity = 0;  // Turn the power LED off.
    ChooseColor();
  }
  else  {
    Serial.println("Color LED Off");
    for (char i = 0; i < 16; i++) {
      strip.setPixelColor(i, 0); // Turn all pixels off
      strip.show();
    }
  }
}

static void DetectShake(int angle){
    /* If shake is detected, the program will turn on the 8 seconds timer and enable interrupts
     */

    if (abs(angle) > SHAKED){
        Serial.println("Shake detected!!");
        shake = 1;   

        TCCR3A = 0;
        TCCR3B = 0;
        TCNT3  = 0;
      
        TCCR3B |= ((1 << CS30) | (1 << CS32));  // Prescale 1024
        TCCR3B |= (1 << WGM32);  // Turn the timer1 on, in CTC mode
        TIFR3 = (1<<OCF3A); // Clean possible interrupts
        OCR3A = 0xFFFF;
         
        TIMSK3 |= (1 << OCIE3A); // Enable CTC interrupt
        sei(); // Enable global interrupts
        /*Serial.println(TCCR3A, BIN);
        Serial.println(TCCR3B, BIN);
        Serial.println(OCR3AL, BIN);        
        Serial.println(OCR3AH, BIN);
        Serial.println(TIFR3, BIN);*/
    }
  
}

static void ChooseColor(){
  /* This function changes the color of the NeoPixel ring by rotation around z-axis. 
     The color value is stored in 32-bit variable color */
  Serial.println("Choose a color:");
  for(int i=0; i<strip.numPixels(); i++) 
      strip.setPixelColor(i, Wheel((int)(plane_position) & 255));
  strip.show();
  color = strip.getPixelColor(1); // Pick up the color from the 1st pixel.
  Serial.print("0x");
  Serial.print(color, HEX);
  Serial.println("\n");
}

static void ColorIntensity(){
  /* This function changes intensity of the NeoPixel color LED ring depending on the rotation around the z-axis*/
  //color_brightness = ((uint32_t)abs(plane_position) << 16) | ((uint32_t)abs(plane_position) << 8) | abs(plane_position);
  for(int i=0; i<= strip.numPixels(); i++)
      strip.setPixelColor(i,color);
  strip.setBrightness(abs(plane_position));
  strip.show();  
}

static uint32_t Wheel(byte WheelPos) {
/* Returns packed 32-bit RGB color code depending on the rotation position. */
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

const uint8_t PROGMEM gamma[] = {
    0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  2,
    2,  2,  2,  2,  3,  3,  3,  3,  4,  4,  4,  4,  5,  5,  5,  6,
    6,  6,  7,  7,  8,  8,  8,  9,  9, 10, 10, 10, 11, 11, 12, 12,
   13, 13, 14, 14, 15, 15, 16, 16, 17, 17, 18, 18, 19, 19, 20, 21,
   21, 22, 22, 23, 24, 24, 25, 26, 26, 27, 28, 28, 29, 30, 30, 31,
   32, 32, 33, 34, 35, 35, 36, 37, 38, 38, 39, 40, 41, 41, 42, 43,
   44, 45, 46, 46, 47, 48, 49, 50, 51, 52, 53, 53, 54, 55, 56, 57,
   58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73,
   74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 86, 87, 88, 89, 90,
   91, 92, 93, 95, 96, 97, 98, 99,100,102,103,104,105,107,108,109,
  110,111,113,114,115,116,118,119,120,122,123,124,126,127,128,129,
  131,132,134,135,136,138,139,140,142,143,145,146,147,149,150,152,
  153,154,156,157,159,160,162,163,165,166,168,169,171,172,174,175,
  177,178,180,181,183,184,186,188,189,191,192,194,195,197,199,200,
  202,204,205,207,208,210,212,213,215,217,218,220,222,224,225,227,
  229,230,232,234,236,237,239,241,243,244,246,248,250,251,253,255 };
