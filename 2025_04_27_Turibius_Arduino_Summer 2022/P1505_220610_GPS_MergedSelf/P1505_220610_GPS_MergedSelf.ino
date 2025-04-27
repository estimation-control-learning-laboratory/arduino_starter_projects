// GPS Libraries
#include "TinyGPS++.h"
#include "SoftwareSerial.h"

// Compass Libraries
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>

// GPS Setup
SoftwareSerial serial_connection(2, 3); // (RX, TX) = (yellow, green)
TinyGPSPlus gps;
int precisionGPS = 8;

// Compass Setup
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);

void displaySensorDetails(void)
{
  sensor_t sensor;
  mag.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" uT");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" uT");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" uT");  
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  serial_connection.begin(9600);
  if(!mag.begin())
  {
    Serial.println("Ooops, no HMC5883 detected ... Check your wiring!");
    while(1);
  }
  displaySensorDetails();
  Serial.begin(9600);
}

void loop() {
  // GPS
  while (serial_connection.available()) {
    gps.encode(serial_connection.read());
  }
  if (gps.location.isUpdated()) {
    Serial.print("Latitude:  ");
    Serial.print(gps.location.lat(), precisionGPS);

    // Compass
    sensors_event_t event; 
    mag.getEvent(&event);
    float heading = atan2(event.magnetic.y, event.magnetic.x);
    float declinationAngle = 0.192;
    heading += declinationAngle;
    if (heading < 0) {
      heading += 2*PI;
    }
    if (heading > 2*PI) {
      heading -= 2*PI;
    }
    float headingDegrees = heading * 180/M_PI; 
    Serial.print("   ");
    Serial.print("Heading:      "); 
    Serial.print(headingDegrees);
    Serial.println(" degrees");

    // GPS
    Serial.print("Longitude: ");
    Serial.print(gps.location.lng(), precisionGPS);

    // Compass
    Serial.print("  X: "); 
    Serial.print(event.magnetic.x); 
    Serial.print(" Y: "); 
    Serial.print(event.magnetic.y); 
    Serial.print(" Z: "); 
    Serial.print(event.magnetic.z);
    Serial.println(" uT");

    delay(1000);
  }
}
