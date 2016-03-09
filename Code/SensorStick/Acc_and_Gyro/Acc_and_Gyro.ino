/*  ADXL345 & ITG-3200 Interface
 *  
 *  Loveread Lamp project prototype
 *  
 *  I2C interface with gyroscope ITG-3200 and accelerometer ADXL345 using low power operation
 *  and reduced output rate. Simulation of the turning lamp is provided.
 *  
 *  Pero, September 2015
 */

#include <Wire.h>                           // I2C library

#define ADXL345_ADDRESS (0xA6 >> 1)         // I2C uses 7-bit addres which is 0x53 for this device and it's got by shifting 0xA6 one bit right
#define ITG3200_ADDRESS (0xD0 >> 1)         // The same for gyro, where address is 0x68

//  Registers
#define ADXL345_REGISTER_XLSB (0x32)        // Register of lower byte of X data (first in the row in x,y,z)
#define ADXL_REGISTER_PWRCTL (0x2D)         // Power control register
#define ADXL_REGISTER_BWRATE (0x2C)         // Bandwidth control register
#define ITG3200_REGISTER_XMSB (0x1D)        // Data register MSB of X data (first in the row in x,y,z)
#define ITG3200_REGISTER_DLPF_FS (0x16)     // Full scale and bandwidth selection
#define ITG3200_REGISTER_PWRMGM (0x3E)      // Power management register

// Control words
#define ADXL_LOW_POWER_12HZ (0x17)          // setting the low power mode (bit 4 and choosing 12.5Hz outputrate
#define ADXL_PWRCTL_MEASURE (1 << 3)        // 3rd bit puts device in measurement or sleaping mode
#define ITG3200_FULLSCALE (0x03 << 3)       // It is necessary to set bits 3 and 4 of DLPF register to 1 for proper operation
#define ITG3200_42HZ (0x03)                 // 42Hz BW LP filter at 1kHz sampling rate
#define ITG3200_STBY_XG (1 << 5)            // Stand-by for x-axis gyro
#define ITG3200_STBY_YG (1 << 4)            // Stand-by for y-axis gyro
#define ITG3200_STBY_ZG (1 << 3)            // Stand-by for z-axis gyro

// Constants
#define INCLINED_15DEG (245)                // Value of z-component at 15° inclination (256*cos(15°)=247) ( Range +/- 2g, resolution 10 bits, signed -> 2^9 = 2g, 2^8 = 1g )

int accelerometer_data[3];      // As the name says - acc data    
int gyro_data[3];

char c;
int LampIntensity = 0;         // Lamp intensity control
int plane_position = 0;        // Rotation angle in x-y plane
boolean ColorLED = 0;          // Color LEDs

void setup() {
  Wire.begin();
  Serial.begin(9600);

  for(int i = 0; i < 3; ++i) {
    accelerometer_data[i] =  gyro_data[i] = 0;
  }
  
  init_adxl345();
  init_itg3200();
}

void loop() {
  
   read_adxl345();
   read_itg3200();

   PrintStuff();

   TurnLampOn(accelerometer_data[1]);  // y- component of acc is the one in prototyping test
   RotateLamp(gyro_data[2]);           // z- component of the gyro in prototype
 
   Serial.print("Light Intensity: ");
   Serial.print(LampIntensity);
   Serial.print("\n");
   Serial.print("Position in plane: ");
   Serial.print(plane_position);
   Serial.print("\n");
   
   delay(500);
}

void TurnLampOn(int angle){
/*  Lamp turns on when inclined more than 15° with the dimmed light. 
 *  Light intensifies to 50% as the lamp comes to vertical position */
 
    if ((angle <= INCLINED_15DEG) && (angle > 0))         // When lamp is moving from horizontal to vertical position, light intensity rises proportionally to 50% of the maximum
       LampIntensity = 256 - angle;
    else if ((angle >= -30) && (angle <= 30)){            // When lamp is more or less vertically positioned, light intensity is regulated by rotation
      plane_position = 0;
      LampIntensity = 256 + (plane_position<<4);
    }   
    else if ((angle >= ~INCLINED_15DEG+1) && (angle < 0)) // when lamp goes from vertical to horizontal, the light dims  
       LampIntensity = 256 + angle; 
    else if((angle >= -270) && (angle <= -230) )           // when the lamp is upside down, it's time to turn on the colored LEDs
        ColoredLamp();
    else 
      LampIntensity = 0;     
}

void RotateLamp(int omega){
/* In vertical position (along the z axis) the gyro measures
 *  angular velocity in about the z-axis and this function calculates 
 *  rotation angle in x-y plane
 */
  int offset = 30;      // There is non-zero sensor output when the lamp is not rotating.
    if(( omega > offset) || (omega < (~offset+1)))
        plane_position += omega;
}

void ColoredLamp(){
/* In the upside down position, power LED turns off and colored LED turns on  
 *  The color is regulated by rotation in x-y plane.
 */
    LampIntensity = 0;  // Turn the power LED off.
    ColorLED = 1;       // Turn the colored LED on.
    Serial.println("Color LED Mode!");
}

void PrintStuff(){
//  walk_through_registers_acc();
//  walk_through_registers_gyro();
  
   Serial.print("ACCEL: ");
   Serial.print(accelerometer_data[0]);
   Serial.print("\t");
   Serial.print(accelerometer_data[1]);
   Serial.print("\t");
   Serial.print(accelerometer_data[2]);
   Serial.print("\t");
   
   Serial.print("GYRO: ");
   Serial.print(gyro_data[0]);
   Serial.print("\t");
   Serial.print(gyro_data[1]);
   Serial.print("\t");
   Serial.print(gyro_data[2]);
   Serial.print("\n");

}

void i2c_write(int address, byte reg, byte data) {
    Wire.beginTransmission(address);
    Wire.write(reg);
    Wire.write(data);
    Wire.endTransmission();
}


void i2c_read(int address, byte reg, int count, byte* data) {
   int i = 0;
  
   Wire.beginTransmission(address);
   Wire.write(reg);
   Wire.endTransmission();
   Wire.beginTransmission(address);
   Wire.requestFrom(address,count);
   while(Wire.available()){
     c = Wire.read();
     data[i] = c;
     i++;
   }
   Wire.endTransmission();
} 

void init_adxl345() {
    i2c_write(ADXL345_ADDRESS, ADXL_REGISTER_PWRCTL, ADXL_PWRCTL_MEASURE);  // write control word (0x04) into the power register to bring the device to measurement mode
    i2c_write(ADXL345_ADDRESS, ADXL_REGISTER_BWRATE, ADXL_LOW_POWER_12HZ);  // write control word (0x17) into the bandwidth register to bring the device to low power  mode
}

void read_adxl345() {
   byte bytes[6];
   memset(bytes,0,6);
  
   i2c_read(ADXL345_ADDRESS, ADXL345_REGISTER_XLSB, 6, bytes);
  
   for (int i=0;i<3;++i)
     accelerometer_data[i] = (int)bytes[2*i] + (((int)bytes[2*i + 1]) << 8);
}

void init_itg3200() {
    i2c_write(ITG3200_ADDRESS, ITG3200_REGISTER_DLPF_FS, ITG3200_FULLSCALE | ITG3200_42HZ);  // Set full scale range and 42Hz LP filter
    i2c_write(ITG3200_ADDRESS, ITG3200_REGISTER_PWRMGM, ITG3200_STBY_XG | ITG3200_STBY_YG);  // Set two inactive gyros in standby   
}

void read_itg3200() {
    byte bytes[6];
    memset(bytes,0,6);
  
    i2c_read(ITG3200_ADDRESS, ITG3200_REGISTER_XMSB, 6, bytes);
    for (int i=0;i<3;++i) 
      gyro_data[i] = (int)bytes[2*i + 1] + (((int)bytes[2*i]) << 8);
}

void walk_through_registers_acc(){
    byte data = 0;
    Serial.println("ADXL345 Registers: \n");
    for (int i = 29; i<58; i++){
      i2c_read(ADXL345_ADDRESS, i, 1, &data);
      Serial.print("Register ");
      Serial.print(i, HEX);
      Serial.print(" : 0x");
      Serial.println(data, HEX);
      }  
}


void walk_through_registers_gyro(){
    byte data = 0;
    Serial.println("ITG3200 Registers: \n");
    for (int i = 21; i<35; i++){
      i2c_read(ITG3200_ADDRESS, i, 1, &data);
      Serial.print("Register ");
      Serial.print(i, HEX);
      Serial.print(" : 0x");
      Serial.println(data, HEX);
      }  
      i2c_read(ITG3200_ADDRESS, 62, 1, &data);
      Serial.print("Register ");
      Serial.print(62, HEX);
      Serial.print(" : 0x");
      Serial.println(data, HEX);
}


