/* PWM demo for high power LED
 *  
 *  Pero
 *  September 2015
 */


#define WhiteLED 11

void setup() {
  pinMode(WhiteLED, OUTPUT);
  digitalWrite(WhiteLED, LOW);

}

void loop() {
  delay(2000);
  for(int i=0; i<512; i++){
      analogWrite(WhiteLED, i);
      delay(1000);
  }

}
