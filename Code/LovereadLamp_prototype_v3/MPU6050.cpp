#include "MPU6050.h"   // Here is where all registers and control words for MPU6050 are stored

accel_t_gyro_union accel_t_gyro = {0};
int16_t int_gyro_z = 0;
int16_t int_acc_z = 0;

// Method to set-up the data from MPU-6050
uint8_t swap;
#define SWAP(x,y) swap = x; x = y; y = swap


void MPU6050_init(){
  Wire.begin(MPU6050_I2C_ADDRESS);
  // default at power-up:
  //    Gyro at 250 degrees second
  //    Acceleration at 2g
  //    Clock source at internal 8MHz
  //    The device is in sleep mode  
  MPU6050_write_reg (MPU6050_PWR_MGMT_1, 0);  // Clear the 'sleep' bit to start the sensor.
  MPU6050_write_reg (MPU6050_CONFIG, MPU6050_DLPF_5HZ);          // Configure DLPF (digital low pass filter to 5Hz bandwidth
  MPU6050_write_reg (MPU6050_ACCEL_CONFIG, MPU6050_AFS_SEL_16G);      // Configure Accelerometer to +/- 16g.
  MPU6050_write_reg (MPU6050_GYRO_CONFIG, MPU6050_FS_SEL_2000);       // full scale gyro at 2000°/s
}

void MPU6050_readOut(){
    // Read the raw values and average them 16 times
  
  int error = 0;

  for (int i = 0; i <15; i++) {
    
  // Read 14 bytes at once, containing acceleration, temperature and gyro.
  error = MPU6050_read (MPU6050_ACCEL_XOUT_H, (uint8_t *) &accel_t_gyro, sizeof(accel_t_gyro));

  // Swap all high and low bytes. After this, the registers values are swapped,
  // so the structure name like x_accel_l does no longer contain the lower byte.

  SWAP (accel_t_gyro.reg.x_accel_h, accel_t_gyro.reg.x_accel_l);
  SWAP (accel_t_gyro.reg.y_accel_h, accel_t_gyro.reg.y_accel_l);
  SWAP (accel_t_gyro.reg.z_accel_h, accel_t_gyro.reg.z_accel_l);
  SWAP (accel_t_gyro.reg.t_h, accel_t_gyro.reg.t_l);
  SWAP (accel_t_gyro.reg.x_gyro_h, accel_t_gyro.reg.x_gyro_l);
  SWAP (accel_t_gyro.reg.y_gyro_h, accel_t_gyro.reg.y_gyro_l);
  SWAP (accel_t_gyro.reg.z_gyro_h, accel_t_gyro.reg.z_gyro_l);
  //accel_t_gyro.value.z_accel -= 200;  // Compensate for the offset of accellerometer
  int_acc_z += ((-1*accel_t_gyro.value.z_accel) >> 4);
  int_gyro_z += (accel_t_gyro.value.z_gyro >> 4);
  }
}

int MPU6050_read(int start, uint8_t *buffer, int size){
 /*--------------------------------------------------------
 MPU6050_read

 This is a common function to read multiple bytes
 from an I2C device.

 It uses the boolean parameter for Wire.endTransMission()
 to be able to hold or release the I2C-bus.
 This is implemented in Arduino 1.0.1.

 Only this function is used to read.
 There is no function for a single byte.*/
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
  while (Wire.available() && i < size)
  {
    buffer[i++] = Wire.read();
  }
  if ( i != size)
    return (-11);

  return (0);  // return : no error
}

int MPU6050_write(int start, const uint8_t *pData, int size){
 /* --------------------------------------------------------
 MPU6050_write

 This is a common function to write multiple bytes to an I2C device.

 If only a single register is written,
 use the function MPU_6050_write_reg().

 Parameters:
   start : Start address, use a define for the register
   pData : A pointer to the data to write.
   size  : The number of bytes to write.

 If only a single register is written, a pointer
 to the data has to be used, and the size is
 a single byte:
   int data = 0;        // the data to write
   MPU6050_write (MPU6050_PWR_MGMT_1, &c, 1);*/
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

int MPU6050_write_reg(int reg, uint8_t data){
  
// --------------------------------------------------------
// MPU6050_write_reg
//
// An extra function to write a single register.
// It is just a wrapper around the MPU_6050_write()
// function, and it is only a convenient function
// to make it easier to write a single register.
//
  int error;

  error = MPU6050_write(reg, &data, 1);

  return (error);
}
