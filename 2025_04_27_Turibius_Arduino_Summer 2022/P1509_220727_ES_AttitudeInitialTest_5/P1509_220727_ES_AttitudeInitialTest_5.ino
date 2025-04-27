#include <Wire.h>
#include <TimerOne.h>
#include <RunningMedian.h>

#define   IMU_Address                 0x68
#define   GYRO_FULL_SCALE_250_DPS     0x00
#define   GYRO_FULL_SCALE_500_DPS     0x08
#define   GYRO_FULL_SCALE_1000_DPS    0x10
#define   GYRO_FULL_SCALE_2000_DPS    0x18
#define   OUT_Type                    DEC
#define   baud_rate                   4800
#define   sampleSize                  200
#define   DPS                         1000

float b;
float attitude;

RunningMedian samples = RunningMedian(sampleSize);

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

void setup() {
  Wire.begin();
  Serial.begin(baud_rate);
  I2Cwrite(IMU_Address, 26, 0x06);
  I2Cwrite(IMU_Address, 27, GYRO_FULL_SCALE_1000_DPS);
  // Callibrating bias
  while ((millis() / 1000) < 3) {
    uint8_t Buf[14];
    I2Cread(IMU_Address, 0x3B, 14, Buf);
    float w = Buf[9];
    if (w > 150) {
      w = w - 255;
    }
    samples.add(w);
    b = samples.getAverage();
  }
}

void loop() {
//  long startTime = micros();
  uint8_t Buf[14];
  I2Cread(IMU_Address, 0x3B, 14, Buf);
  float w = Buf[9];
  if (w > 150) {
    w = w - 255.;
  }
  w = w - b;
//  long endTime = micros();
//  float ellapsed = (endTime - startTime) / 1000000.;
//  attitude = attitude + w * ellapsed;
  attitude = attitude + w / baud_rate * DPS;
  Serial.print(w);
//  Serial.print('\t');
//  Serial.print(ellapsed, OUT_Type);
  Serial.print('\t');
  Serial.print(attitude, OUT_Type);
  Serial.println("");
}
