/*  MPU-6050 Interface
 *  
 *  Loveread Lamp project prototype
 *  
 *  I2C interface with gyroscope and accelerometer unit MPU-6050 using low power operation
 *  and reduced output rate. Simulation of the turning lamp is provided.
 *  
 *  The code is based on Arduino Basic Sketch II
 *  
 *  Pero, September 2015
 */

#include <Wire.h>
#include "MPU6050.h"   // Here is where all registers and control words for MPU6050 are stored
#include <Adafruit_NeoPixel.h>    // library for NeoPixel RGB diode

#define MPU6050_I2C_ADDRESS 0x68 // Default I2C address for the MPU-6050 is 0x68.
#define WhiteLED 5            // PWM output for white LED
#define PIN 6                 // Ctrl output for NeoPixel RGB strip
Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, PIN, NEO_GRB + NEO_KHZ800);  // Class that deals with neopixel  


// Declaring an union for the registers and the axis values.
// The byte order does not match the byte order of 
// the compiler and AVR chip.
// The AVR chip (on the Arduino board) has the Low Byte 
// at the lower address.
// But the MPU-6050 has a different order: High Byte at
// lower address, so that has to be corrected.
// The register part "reg" is only used internally, 
// and are swapped in code.
typedef union accel_t_gyro_union
{
  struct
  {
    uint8_t x_accel_h;
    uint8_t x_accel_l;
    uint8_t y_accel_h;
    uint8_t y_accel_l;
    uint8_t z_accel_h;
    uint8_t z_accel_l;
    uint8_t t_h;
    uint8_t t_l;
    uint8_t x_gyro_h;
    uint8_t x_gyro_l;
    uint8_t y_gyro_h;
    uint8_t y_gyro_l;
    uint8_t z_gyro_h;
    uint8_t z_gyro_l;
  } reg;
  struct 
  {
    int16_t x_accel;
    int16_t y_accel;
    int16_t z_accel;
    int16_t temperature;
    int16_t x_gyro;
    int16_t y_gyro;
    int16_t z_gyro;
  } value;
};

// Constants
#define INCLINED_15DEG 1978>>4                // Value of z-component at 15° inclination (2048*cos(15°)=1978) ( Range +/- 16g, resolution 16 bits, signed -> 2^15 = 16g, 2^11 = 1g )
                                              // Shift it by 4 so that you can work with normal values, like 256

//Variables
int error;
double dT;
accel_t_gyro_union accel_t_gyro;
int LampIntensity = 0;         // Lamp intensity control
int plane_position = 0;        // Rotation angle in x-y plane


void setup()
{      
  int error;
  uint8_t c;
  // Initialize LEDs and turn them off.
  pinMode(WhiteLED, OUTPUT);  // Configure White LED as output
  digitalWrite(WhiteLED, LOW);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  
  Serial.begin(9600);
  // Initialize the 'Wire' class for the I2C-bus.
  Wire.begin();
  // default at power-up:
  //    Gyro at 250 degrees second
  //    Acceleration at 2g
  //    Clock source at internal 8MHz
  //    The device is in sleep mode.
  error = MPU6050_read (MPU6050_WHO_AM_I, &c, 1);
  Serial.print(F("WHO_AM_I : "));
  Serial.print(c,HEX);
  Serial.print(F(", error = "));
  Serial.println(error,DEC);
  // According to the datasheet, the 'sleep' bit
  // should read a '1'.
  // That bit has to be cleared, since the sensor
  // is in sleep mode at power-up. 
  error = MPU6050_read (MPU6050_PWR_MGMT_1, &c, 1);
  Serial.print(F("PWR_MGMT_1 : "));
  Serial.print(c,HEX);
  Serial.print(F(", error = "));
  Serial.println(error,DEC);
  
  MPU6050_write_reg (MPU6050_PWR_MGMT_1, 0);                     // Clear the 'sleep' bit to start the sensor.
  MPU6050_write_reg (MPU6050_CONFIG, MPU6050_DLPF_5HZ);          // Configure DLPF (digital low pass filter to 5Hz bandwidth 
  MPU6050_write_reg (MPU6050_ACCEL_CONFIG, MPU6050_AFS_SEL_16G);      // Configure Accelerometer to +/- 16g.
  MPU6050_write_reg (MPU6050_GYRO_CONFIG, MPU6050_FS_SEL_2000);  // full scale gyro at 2000°/s
}


void loop()
{
  // Read the raw values.
  // Read 14 bytes at once, containing acceleration, temperature and gyro.
  // With the default settings of the MPU-6050, there is no filter enabled, and the valuesare not very stable.
  error = MPU6050_read (MPU6050_ACCEL_XOUT_H, (uint8_t *) &accel_t_gyro, sizeof(accel_t_gyro));

  // Swap all high and low bytes. After this, the registers values are swapped, 
  // so the structure name like x_accel_l does no longer contain the lower byte.
  uint8_t swap;
  #define SWAP(x,y) swap = x; x = y; y = swap
  SWAP (accel_t_gyro.reg.x_accel_h, accel_t_gyro.reg.x_accel_l);
  SWAP (accel_t_gyro.reg.y_accel_h, accel_t_gyro.reg.y_accel_l);
  SWAP (accel_t_gyro.reg.z_accel_h, accel_t_gyro.reg.z_accel_l);
  SWAP (accel_t_gyro.reg.t_h, accel_t_gyro.reg.t_l);
  SWAP (accel_t_gyro.reg.x_gyro_h, accel_t_gyro.reg.x_gyro_l);
  SWAP (accel_t_gyro.reg.y_gyro_h, accel_t_gyro.reg.y_gyro_l);
  SWAP (accel_t_gyro.reg.z_gyro_h, accel_t_gyro.reg.z_gyro_l);
  accel_t_gyro.value.z_accel -= 200;  // Compensate for the offset of accellerometer

  PrintStuff();

  TurnLampOn(accel_t_gyro.value.z_accel>>4);          // z- component of acc is the one in prototyping test, shift it by 4 so that you can work with normal values like 128
  ColoredLamp(accel_t_gyro.value.z_accel>>4); 
  RotateLamp(accel_t_gyro.value.x_gyro + 62);           // x- component of the gyro in prototype

  Serial.print("Light Intensity: ");
  Serial.print(LampIntensity);
  Serial.print("\n");
  Serial.print("Position in plane: ");
  Serial.print(plane_position);
  Serial.print("\n");

  analogWrite(WhiteLED, LampIntensity);
  
  delay(10);
}


void TurnLampOn(int angle){
/*  Lamp turns on when inclined more than 15° with the dimmed light. 
 *  Light intensifies to 50% as the lamp comes to vertical position */
 
    if ((angle <= INCLINED_15DEG) && (angle > 0)){        // When lamp is moving from horizontal to vertical position, light intensity rises proportionally to 50% of the maximum
       LampIntensity = 128 - angle;
        plane_position = 0;
    }
    else if ((angle >= -30) && (angle <= 30)){            // When lamp is more or less vertically positioned, light intensity is regulated by rotation
      LampIntensity = 128 + (plane_position);
    }   
    else if ((angle >= ~INCLINED_15DEG+1) && (angle < 0)) // when lamp goes from vertical to horizontal, the light dims  
       LampIntensity = 128 + angle;   
    else 
      LampIntensity = 0;     
}

void RotateLamp(int omega){
/* In vertical position (along the z axis) the gyro measures
 *  angular velocity in about the z-axis and this function calculates 
 *  rotation angle in x-y plane */
 
  int offset = 60;      // There is non-zero sensor output when the lamp is not rotating.
    if(( omega > offset) || (omega < (~offset+1)))
        plane_position += (omega>>8);    // Take only upper half word to reduce all the noise and offset shit
}

void ColoredLamp(int angle){
/* In the upside down position, power LED turns off and colored LED turns on  
 *  The color is regulated by rotation in x-y plane.
 */     
    if((angle <= -120) && (angle >= -136) ) {          // when the lamp is upside down, it's time to turn on the colored LEDs
       
        Serial.println("Color LED Mode!");
        LampIntensity = 0;  // Turn the power LED off.
    
        for(int i=0;i<16;i++){
        // strip.Color takes RGB values, from 0,0,0 up to 255,255,255
            strip.setPixelColor(i, strip.Color(0,150,0)); // Moderately bright green color.
            strip.show(); // This sends the updated pixel color to the hardware.
            //delay(10); // Delay for a period of time (in milliseconds).
         }
    }
    else  {
        Serial.println("Color LED Off");
        for(int i=0;i<16;i++){
            strip.setPixelColor(i, 0); // Turn all pixels off
            strip.show();
         }
    }
      

}

void PrintStuff(){
    // Print the raw acceleration values

  Serial.print(F("accel x,y,z: "));
  Serial.print(accel_t_gyro.value.x_accel, DEC);
  Serial.print(F(", "));
  Serial.print(accel_t_gyro.value.y_accel, DEC);
  Serial.print(F(", "));
  Serial.print(accel_t_gyro.value.z_accel, DEC);
  Serial.println(F(""));
  // The temperature sensor is -40 to +85 degrees Celsius.
  // It is a signed integer.
  // According to the datasheet: 
  //   340 per degrees Celsius, -512 at 35 degrees.
  // At 0 degrees: -512 - (340 * 35) = -12412

  /*Serial.print(F("temperature: "));
  dT = ( (double) accel_t_gyro.value.temperature + 12412.0) / 340.0;
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
}

// --------------------------------------------------------
// MPU6050_read
//
// This is a common function to read multiple bytes 
// from an I2C device.
//
// It uses the boolean parameter for Wire.endTransMission()
// to be able to hold or release the I2C-bus. 
// This is implemented in Arduino 1.0.1.
//
// Only this function is used to read. 
// There is no function for a single byte.
//
int MPU6050_read(int start, uint8_t *buffer, int size)
{
  int i, n, error;

  Wire.beginTransmission(MPU6050_I2C_ADDRESS);
  n = Wire.write(start);
  if (n != 1)
    return (-10);

  n = Wire.endTransmission(false);    // hold the I2C-bus
  if (n != 0)
    return (n);

  // Third parameter is true: relase I2C-bus after data is read.
  Wire.requestFrom(MPU6050_I2C_ADDRESS, size, true);
  i = 0;
  while(Wire.available() && i<size)
  {
    buffer[i++]=Wire.read();
  }
  if ( i != size)
    return (-11);

  return (0);  // return : no error
}


// --------------------------------------------------------
// MPU6050_write
//
// This is a common function to write multiple bytes to an I2C device.
//
// If only a single register is written,
// use the function MPU_6050_write_reg().
//
// Parameters:
//   start : Start address, use a define for the register
//   pData : A pointer to the data to write.
//   size  : The number of bytes to write.
//
// If only a single register is written, a pointer
// to the data has to be used, and the size is
// a single byte:
//   int data = 0;        // the data to write
//   MPU6050_write (MPU6050_PWR_MGMT_1, &c, 1);
//
int MPU6050_write(int start, const uint8_t *pData, int size)
{
  int n, error;

  Wire.beginTransmission(MPU6050_I2C_ADDRESS);
  n = Wire.write(start);        // write the start address
  if (n != 1)
    return (-20);

  n = Wire.write(pData, size);  // write data bytes
  if (n != size)
    return (-21);

  error = Wire.endTransmission(true); // release the I2C-bus
  if (error != 0)
    return (error);

  return (0);         // return : no error
}

// --------------------------------------------------------
// MPU6050_write_reg
//
// An extra function to write a single register.
// It is just a wrapper around the MPU_6050_write()
// function, and it is only a convenient function
// to make it easier to write a single register.
//
int MPU6050_write_reg(int reg, uint8_t data)
{
  int error;

  error = MPU6050_write(reg, &data, 1);

  return (error);
}
