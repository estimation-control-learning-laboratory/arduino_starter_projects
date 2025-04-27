#include "TinyGPS++.h"
#include "SoftwareSerial.h"
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>
#define configA 0x00
#define configB 0x01
#define mode 0x02
#define statusReg 0x09
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

Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);

int deciPoints = 12;
SoftwareSerial serial_connection(3, 2); //RX=pin 3 yellow, TX=pin 2
TinyGPSPlus gps;//This is the GPS object that will pretty much do all the grunt work with the NMEA data

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600);//This opens up communications to the Serial monitor in the Arduino IDE
  setOperatingMode(continuous);
  setSamples();
  serial_connection.begin(9600);//This opens up communications to the GPS
  Serial.println("GPS Start");//Just show to the monitor that the sketch has started
  Serial.println("HMC5883 Magnetometer Test"); Serial.println("");
  Serial.begin(9600);
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
 Serial.println(gaussZ);
 Serial.print("Heading: ");
 Serial.println(heading);
 while(serial_connection.available())//While there are characters to come from the GPS
  {
    gps.encode(serial_connection.read());//This feeds the serial NMEA data into the library one char at a time
  }
  if(gps.location.isUpdated())//This will pretty much be fired all the time anyway but will at least reduce it to only after a package of NMEA data comes in
  {
    //Get the latest info from the gps object which it derived from the data sent by the GPS unit
    Serial.println("Satellite Count:");
    Serial.println(gps.satellites.value());
    Serial.println("Latitude:");
    Serial.println(gps.location.lat(), deciPoints);
    Serial.println("Longitude:");
    Serial.println(gps.location.lng(), deciPoints);
    Serial.println("Speed MPH:");
    Serial.println(gps.speed.mph(), deciPoints);
    Serial.println("Altitude Feet:");
    Serial.println(gps.altitude.feet(),deciPoints);
    Serial.println("");
  }
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
 heading = (atan2(Y,X) * 180 / PI) + 315;
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
