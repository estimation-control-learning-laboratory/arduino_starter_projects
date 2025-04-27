#include <Wire.h>
#include <TimerOne.h>

#define   IMU_Address                 0x68
#define   GYRO_FULL_SCALE_250_DPS     0x00  
#define   GYRO_FULL_SCALE_500_DPS     0x08
#define   GYRO_FULL_SCALE_1000_DPS    0x10
#define   GYRO_FULL_SCALE_2000_DPS    0x18
#define   ACC_FULL_SCALE_2_G          0x00  
#define   ACC_FULL_SCALE_4_G          0x08
#define   ACC_FULL_SCALE_8_G          0x10
#define   ACC_FULL_SCALE_16_G         0x18
#define   OUT_Type                    DEC

void I2Cwrite(uint8_t Address, uint8_t Register, uint8_t Data) {
  Wire.beginTransmission(Address);
  Wire.write(Register);
  Wire.write(Data);
  Wire.endTransmission();
}

void I2Cread(uint8_t Address, uint8_t Register, uint8_t nBytes, uint8_t* Data) {
  Wire.beginTransmission(Address);
  Wire.write(Register);
  Wire.endTransmission();
  Wire.requestFrom(Address, nBytes);
  uint8_t index = 0;
  while (Wire.available())
    Data[index++] = Wire.read();
}

long int ti;
volatile bool intFlag=false;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  I2Cwrite(IMU_Address,29,0x06);
  I2Cwrite(IMU_Address,26,0x06);
  I2Cwrite(IMU_Address,27,GYRO_FULL_SCALE_1000_DPS);
  I2Cwrite(IMU_Address,28,ACC_FULL_SCALE_4_G);
  I2Cwrite(IMU_Address,0x37,0x02);
//  pinMode(13, OUTPUT);
//  Timer1.initialize(10000);
//  Timer1.attachInterrupt(callback);
  ti = millis();
}

//long int cpt = 0;
//
//void callback() { 
//  intFlag = true;
//  digitalWrite(13, digitalRead(13) ^ 1);
//}

void loop() {
//  while (!intFlag);
//  intFlag=false;
  uint8_t Buf[14];
  I2Cread(IMU_Address,0x3B,14,Buf);
  int16_t ax=-(Buf[0]<<8 | Buf[1]);
  int16_t ay=-(Buf[2]<<8 | Buf[3]);
  int16_t az=Buf[4]<<8 | Buf[5];
  int16_t gx=-(Buf[8]<<8 | Buf[9]);
  int16_t gy=-(Buf[10]<<8 | Buf[11]);
  int16_t gz=Buf[12]<<8 | Buf[13];

  Serial.print (ax, OUT_Type); 
  Serial.print ("\t");
  Serial.print (ay, OUT_Type);
  Serial.print ("\t");
  Serial.print (az, OUT_Type);  
  Serial.print ("\t");
  Serial.print (gx, OUT_Type); 
  Serial.print ("\t");
  Serial.print (gy, OUT_Type);
  Serial.print ("\t");
  Serial.print (gz, OUT_Type);  
  Serial.print ("\t");
  Serial.println("");
}
