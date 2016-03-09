#include <Adafruit_NeoPixel.h>

#define PIN 6  // the digital pin the data line is connected to

// Modifed NeoPixel sample for the holiday craft project

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, PIN, NEO_GRB + NEO_KHZ800);

#define low_red strip.Color(3, 0, 0)
#define low_green strip.Color(0, 3, 0)
#define med_red strip.Color(20, 0, 0)
#define med_green strip.Color(0, 20, 0)
#define hi_red strip.Color(40, 0, 0)
#define hi_green strip.Color(0, 40, 0)

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  uint16_t i, j;
  int num_steps = 100;

  fade_up(100, 30, 30, 0, 0);
  fade_up(100, 30, 0, 30, 0);
  fade_up(100, 30, 30, 0, 0);
  fade_up(100, 30, 0, 30, 0);
  
  colorWipe(med_red, 50); // Red
  colorWipe(med_green, 50); // Green
  colorWipe(med_red, 50); // Red
  colorWipe(med_green, 50); // Green
  
  for (j=0; j<2; j++) {
    for(i=0; i<strip.numPixels()+3; i++) {
      if (i<strip.numPixels()) strip.setPixelColor(i, hi_red);
      if ((i-1 >= 0) && (i-1 < strip.numPixels())) strip.setPixelColor(i-1, med_red);
      if ((i-2 >= 0) && (i-2 < strip.numPixels())) strip.setPixelColor(i-2, low_red);
      if ((i-3 >= 0) && (i-3 < strip.numPixels())) strip.setPixelColor(i-3, med_green);
      strip.show();
      delay(50);
    }
  }  

} // loop


// fade_up - fade up to the given color
void fade_up(int num_steps, int wait, int R, int G, int B) {
   uint16_t i, j;
   
   for (i=0; i<num_steps; i++) {
      for(j=0; j<strip.numPixels(); j++) {
         strip.setPixelColor(j, strip.Color(R * i / num_steps, G * i / num_steps, B * i / num_steps));
      }  
   strip.show();
   delay(wait);
   }  
} // fade_up


// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}
