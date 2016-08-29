/* ADXL345 Interface
 *  
 *  Loveread Lamp project prototype
 *  
 *  I2C interface with accelerometer ADXL345 using low power operation
 *  reduced output rate
 *  
 *  Pero, September 2015
 */


#include <Wire.h>

#define ADXL345_ADDRESS (0xA6 >> 1)         // I2C uses 7-bit addres which is 0x53 for this device and it's got by shifting 0xA6 one bit right

// ADXL345 Registers
#define ADXL345_REGISTER_XLSB (0x32)        // Register of lower byte of X data (first in the row in x,y,z)
#define ADXL_REGISTER_PWRCTL (0x2D)         // Power control register
#define ADXL_REGISTER_BWRATE (0x2C)         // Bandwidth control register

// Control words
#define ADXL_LOW_POWER_12HZ (0x17)          // setting the low power mode (bit 4 and choosing 12.5Hz outputrate
#define ADXL_PWRCTL_MEASURE (1 << 3)        // 3rd bit puts device in measurement or sleaping mode

// Constants
#define INCLINED_15DEG (245)                // Value of z-component at 15° inclination (256*cos(15°)=247) ( Range +/- 2g, resolution 10 bits, signed -> 2^9 = 2g, 2^8 = 1g )

int accelerometer_data[3];
char c;
int LampIntensity = 0;

void setup() {
  Wire.begin();
  Serial.begin(9600);

  for(int i = 0; i < 3; ++i) {
    accelerometer_data[i]  = 0;
  }
  
  init_adxl345();
}

void loop() {
   //walk_through_registers();
   read_adxl345();

   Serial.print("ACCEL: ");
   Serial.print(accelerometer_data[0]);
   Serial.print("\t");
   Serial.print(accelerometer_data[1]);
   Serial.print("\t");
   Serial.print(accelerometer_data[2]);
   Serial.print("\t");
   Serial.print("\n");
  
   TurnLampOn(accelerometer_data[1]);

delay(1000);
}

void TurnLampOn(int angle){
/*  Lamp turns on when inclined more than 15° with the dimmed light. 
 *  Light intensifies to 50% as the lamp comes to vertical position */
 
  if ((angle <= INCLINED_15DEG) && (angle >= 0))
     LampIntensity = 256 - angle;
  else 
    LampIntensity = 0;     

  Serial.print("Light Intensity: ");
  Serial.print(LampIntensity);
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
  byte data = 0;

  i2c_write(ADXL345_ADDRESS, ADXL_REGISTER_PWRCTL, ADXL_PWRCTL_MEASURE);  // write control word (0x04) into the power register to bring the device to measurement mode
  i2c_write(ADXL345_ADDRESS, ADXL_REGISTER_BWRATE, ADXL_LOW_POWER_12HZ);  // write control word (0x17) into the bandwidth register to bring the device to low power  mode

  i2c_read(ADXL345_ADDRESS, ADXL_REGISTER_PWRCTL, 1, &data);          // read the power control register and print it on serial port
  Serial.println((unsigned int)data);
}

void read_adxl345() {
   byte bytes[6];
   memset(bytes,0,6);
  
   i2c_read(ADXL345_ADDRESS, ADXL345_REGISTER_XLSB, 6, bytes);          //read 6 bytes from the ADXL345
  
   for (int i=0;i<3;++i) {
   accelerometer_data[i] = (int)bytes[2*i] + (((int)bytes[2*i + 1]) << 8);  // set up the data from lower and higher byte for each axis
   }
}

void walk_through_registers(){
    byte data = 0;
    for (int i = 29; i<58; i++){
      i2c_read(ADXL345_ADDRESS, i, 1, &data);
      Serial.print("Register ");
      Serial.print(i, HEX);
      Serial.print(" : 0x");
      Serial.println(data, HEX);
      }  
}
