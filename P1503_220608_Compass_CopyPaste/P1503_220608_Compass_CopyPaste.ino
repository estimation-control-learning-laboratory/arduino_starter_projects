#include <Wire.h>
//Address map for registers
#define configA 0x00
#define configB 0x01
#define mode 0x02
#define dataOutX_U 0x03
#define dataOutX_L 0x04
#define dataOutZ_L 0x05
#define dataOutZ_L 0x06
#define dataOutY_L 0x07
#define dataOutY_L 0x08
#define statusReg 0x09
//Operating modes sent to Mode register (0x02)
#define continuous 0x00
#define single 0x01
#define idle 0x02
#define i2c_addr 0x1E
#define gain 1090
int16_t x = 0;
int16_t y = 0;
int16_t z = 0;
float heading;
float gaussX;
float gaussY;
float gaussZ;
void setup() {
 Wire.begin();
 Serial.begin(9600);
 setOperatingMode(continuous);
 setSamples();
}
void loop() {
 getXYZ();
 convert(x,y,z);
 getHeading(gaussX,gaussY,gaussZ);
 Serial.print("X: ");
 Serial.print(gaussX);
 Serial.print(" Y: ");
 Serial.print(gaussY);
 Serial.print(" Z: ");
 Serial.print(gaussZ);
 Serial.print(" Heading: ");
 Serial.println(heading);
 delay(500);
}
//Convert the raw X, Y, Z counts to Gauss
void convert(int16_t rawX, int16_t rawY, int16_t rawZ){
 gaussX = (float)rawX/gain;
 gaussY = (float)rawY/gain;
 gaussZ = (float)rawZ/gain;    
}
//accounts for declination (error in magnetic field which is dependent on location)
void getHeading(float X, float Y, float Z){
 heading = ((atan2(Y,X)) * 180 - 294) / PI;
 if (heading < 0) heading += 360;
 if (heading > 360) heading -= 360;
}
void setSamples(void){
 Wire.beginTransmission(i2c_addr);
 Wire.write(configA);        //write to config A register
 Wire.write(0x70);           //8 samples averaged, 15Hz output rate, normal measurement
 Wire.endTransmission();
 delay(10);
}
void setOperatingMode(uint8_t addr){
 Wire.beginTransmission(i2c_addr);
 Wire.write(mode);           //write to mode register
 Wire.write(addr);           //set measurement mode
 Wire.endTransmission();
 delay(10);
}
//get the raw counts of X, Y, Z from registers 0x03 to 0x08
void getXYZ(void){
 Wire.beginTransmission(i2c_addr);
 Wire.write(0x03);
 Wire.endTransmission();
 Wire.requestFrom(i2c_addr, 6);
 if (Wire.available() >= 6){
   int16_t temp = Wire.read();     //read upper byte of X
   x = temp << 8;
   temp = Wire.read();             //read lower byte of X
   x = x | temp;
   temp = Wire.read();             //read upper byte of Z
   z = temp << 8;
   temp = Wire.read();             //read lower byte of Z
   z = z | temp;
   temp = Wire.read();             //read upper byte of Y
   y = temp << 8;
   temp = Wire.read();             //read lower byte of Y
   y = y | temp;
 }
}
