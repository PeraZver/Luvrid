 /*  Loveread Lamp project prototype
 *
 *  ATmega32u4 with I2C interface with gyroscope and accelerometer unit MPU-6050 using low power operation
 *  and reduced output rate. Depending on the position high-power LED is turned on and 
 *  PWM-dimmed and RGB Neopixel ring is activated. Light intensity is gamma corrected. RGB NeoPixel 
 *  ring changes its intensity depending on the plane position.
 *  
 *  v4 has simmetricaly calculated light intensity based on vertical position for both lamp.
 *  
 *  v3 has color selection mode which is activated after shake, and selected color can be dimmed afterwards. The whole code is modular. Gamma correction introduced.
 *  
 *  v2 uses integration to stabilize acc and gyro output.
 *  
 *  The code is based on Arduino Basic Sketch II
 *
 *  Pero, February 2016
 */
#include <Wire.h>  
#include <Adafruit_NeoPixel.h> // library for NeoPixel RGB diode
#include "MPU6050.h"   // Here is where all registers and control words for MPU6050 are stored
#include "NeoPixelControl.h"    

void setup()
{  
        /* Set system clock */
  CLKSEL0 = 0b00010101;   // Choose Crystal oscillator with BOD
  CLKSEL1 = 0b00001111;   // 8MHz
  CLKPR = 0b10000000;     // Change the clock prescaler
  CLKPR = 0;              // Prescaler is 1.

  /* Disable JTAG interface on PORTF */
  MCUCR |= (1<<JTD);   // 
  MCUCR |= (1<<JTD);   // Have to do it twice (datasheet page 328.)
  // Initialize LEDs and turn them off.
  pinMode(WhiteLED, OUTPUT);  // Configure White LED as output
  digitalWrite(WhiteLED, LOW);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  Serial.begin(9600);
   
  delay(100); // Give more than 30 ms for MPU6050 to wake up
  MPU6050_init();
}


void loop()
{

  MPU6050_readOut();     // Read the Acc and Gyro data from the MPU6050, and average them 16 times.
    
  PrintStuff();
  
  //z- component of acc is the one in prototyping test, shift it by 4 so that you can work with normal values like 128
  RotateLamp(int_gyro_z);           // z- component of the gyro in prototype
  ChooseLED((int_acc_z) >> 4);

  int_acc_z = 0;
  int_gyro_z = 0;

  delay(25);
}




void PrintStuff() {
  // Print the raw acceleration values

  Serial.print(F("accel x,y,z: "));
  Serial.print(accel_t_gyro.value.x_accel >> 4, DEC);
  Serial.print(F(", "));
  Serial.print(accel_t_gyro.value.y_accel >> 4, DEC);
  Serial.print(F(", "));
  Serial.print(accel_t_gyro.value.z_accel >> 4, DEC);
  Serial.println(F(""));
  // The temperature sensor is -40 to +85 degrees Celsius.
  // It is a signed integer.
  // According to the datasheet:
  //   340 per degrees Celsius, -512 at 35 degrees.
  // At 0 degrees: -512 - (340 * 35) = -12412

  /*Serial.print(F("temperature: "));
  dT= ( (double) accel_t_gyro.value.temperature + 12412.0) / 340.0;
  Serial.print(dT, 3);
  Serial.print(F(" degrees Celsius"));
  Serial.println(F(""));*/

  // Print the raw gyro values.
  Serial.print(F("gyro x,y,z : "));
  Serial.print(accel_t_gyro.value.x_gyro, DEC);
  Serial.print(F(", "));
  Serial.print(accel_t_gyro.value.y_gyro, DEC);
  Serial.print(F(", "));
  Serial.print(accel_t_gyro.value.z_gyro, DEC);
  Serial.print(F(", "));
  Serial.println(F(""));

  //Integrated values
  Serial.print(F("Integrated acc: "));
  Serial.print(int_acc_z >> 4, DEC);
  Serial.print(F("\nIntegrated gyro: "));
  Serial.print(int_gyro_z >> 4, DEC);
  Serial.println(F("\n"));

  
  Serial.print("Light Intensity: ");
  Serial.print(Intensity(abs(int_acc_z) >> 4));
  Serial.print("\n");
  Serial.print("Position in plane: ");
  Serial.print(plane_position);
  Serial.print("\n");

}


ISR(TIMER3_COMPA_vect){ 
  //Serial.println("5 seconds passed. I hope you chose your color!");
  TCCR3B = 0;  // Turn off interrupts.
  TIMSK3 = 0;
  cli();
  shake = 0;
}


