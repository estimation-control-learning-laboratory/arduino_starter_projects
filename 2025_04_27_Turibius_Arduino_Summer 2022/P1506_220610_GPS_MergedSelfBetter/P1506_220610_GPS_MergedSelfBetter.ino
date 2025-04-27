float gpsLat;
float gpsLng;
int   gpsSat;
float gpsSpd;

// Libraries
#include "TinyGPS++.h"
#include "SoftwareSerial.h"
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>

// Setup
SoftwareSerial serial_connection(2, 3); // green, yellow
TinyGPSPlus gps;
int gpsPrecision = 8;
int mgnPrecision = 2;
// Calibration values
float declinationAngle = 0.192;
float A11 = 1.048112;
float A12 = -0.030010;
float A13 = 0.020919;
float A21 = -0.030010;
float A22 = 1.045133;
float A23 = -0.019243;
float A31 = 0.020919;
float A32 = -0.019243;
float A33 = 0.953546;
float b1 = 8.847797;
float b2 = 12.277164;
float b3 = -8.164650;

Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);

void setup() {
  Serial.begin(9600);
  serial_connection.begin(9600);
  if(!mag.begin())
  {
    Serial.println("No HMC5883 compass detected!");
    while(1);
  }
  sensor_t sensor;
  mag.getSensor(&sensor);
  Serial.begin(9600);
  delay(500);
}

void loop() {
  // GPS
  while (serial_connection.available()) {
    gps.encode(serial_connection.read());
  }
  if (gps.location.isUpdated()) {
    gpsSat = gps.satellites.value();
    gpsLat = gps.location.lat();
    gpsLng = gps.location.lng();
    gpsSpd = gps.speed.mps();
  }
  // Compass Calculations
  sensors_event_t event; 
  mag.getEvent(&event);
  float m1 = event.magnetic.x;
  float m2 = event.magnetic.y;
  float m3 = event.magnetic.z;
  float mgnX = A11 * (m1-b1) + A12 * (m2-b2) + A13 * (m3-b3);
  float mgnY = A21 * (m1-b1) + A22 * (m2-b2) + A23 * (m3-b3);
  float mgnZ = A31 * (m1-b1) + A32 * (m2-b2) + A33 * (m3-b3);
  float heading = atan2(- mgnX, - mgnY);
  float headingDegrees = heading * 180/M_PI; 
  if (headingDegrees < 0) {
    headingDegrees += 360;
  }
  if (headingDegrees > 360) {
    headingDegrees -= 360;
  }

  // Printing
  Serial.print("(");
  Serial.print(gpsLat, gpsPrecision);
  Serial.print(", ");
  Serial.print(gpsLng, gpsPrecision);
  Serial.print(") | Sat. Available: ");
  Serial.print(gpsSat);
  Serial.print(", Speed: ");
  Serial.print(gpsSpd, gpsPrecision / 2);
  Serial.print(" m/s | X: ");
  Serial.print(mgnX, mgnPrecision); 
  Serial.print(" Y: "); 
  Serial.print(mgnY, mgnPrecision); 
  Serial.print(" Z: "); 
  Serial.print(mgnZ, mgnPrecision);
  Serial.print(" uT");
  Serial.print(" | Bearing (deg): ");
  Serial.println(headingDegrees, mgnPrecision);
  delay(100);
}
