/* PWM demo for high power LED
 *  
 *  Pero
 *  September 2015
 */

#define WhiteLED 11

void setup() {     
  /* Set system clock */
  CLKSEL0 = 0b00010101;   // Choose Crystal oscillator with BOD
  CLKSEL1 = 0b00001111;   // 8MHz
  CLKPR = 0b10000000;     // Change the clock prescaler
  CLKPR = 0;              // Prescaler is 1.

  pinMode(WhiteLED, OUTPUT);
  digitalWrite(WhiteLED, LOW);

}

void loop() {
  delay(2000);
  for(int i=0; i<512; i++){
      analogWrite(WhiteLED, i);
      delay(500);
  }

}
