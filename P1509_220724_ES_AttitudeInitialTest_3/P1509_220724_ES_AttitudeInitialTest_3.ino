#include <Wire.h>
#include <TimerOne.h>
#define   IMU_Address                 0x68
#define   GYRO_FULL_SCALE_250_DPS     0x00
#define   GYRO_FULL_SCALE_500_DPS     0x08
#define   GYRO_FULL_SCALE_1000_DPS    0x10
#define   GYRO_FULL_SCALE_2000_DPS    0x18
#define   OUT_Type                    DEC

int weight = 1;
float b = 0;
float startTime;
float endTime;
float attitude;

void I2Cwrite(uint8_t Address, uint8_t Register, uint8_t Data) {
  Wire.beginTransmission(Address);
  Wire.write(Register);
  Wire.write(Data);
  Wire.endTransmission();
}

void I2Cread(uint8_t Address, uint8_t Register, uint8_t nBytes, uint8_t* Data) {
  startTime = micros();
  Wire.beginTransmission(Address);
  Wire.write(Register);
  Wire.endTransmission();
  Wire.requestFrom(Address, nBytes);
  uint8_t index = 0;
  while (Wire.available())
    Data[index++] = Wire.read();
  endTime = micros();
}

void setup() {
  Wire.begin();
  Serial.begin(9600);
  I2Cwrite(IMU_Address, 26, 0x06);
  I2Cwrite(IMU_Address, 27, GYRO_FULL_SCALE_2000_DPS);
}

void loop() {
  uint8_t Buf[14];
  I2Cread(IMU_Address, 0x3B, 14, Buf);
  float ellapsed = (endTime - startTime) / 1000000;
  float w = (Buf[9] + b) * weight;
  attitude = attitude + w * ellapsed;
  Serial.print(startTime / 1000000);
  Serial.print(',');
  Serial.print(ellapsed,DEC);
  Serial.print(',');
  Serial.print(w);
  Serial.print(',');
  Serial.print(attitude,DEC);
  Serial.println("");
}
