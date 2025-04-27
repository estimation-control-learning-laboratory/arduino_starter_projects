#include "TinyGPS++.h"
#include "SoftwareSerial.h"
#include <Wire.h>
#include <Adafruit_Sensor.h> 
#include <Adafruit_HMC5883_U.h>

Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);

int deciPoints = 12;
SoftwareSerial serial_connection(2, 3); //RX=pin 10, TX=pin 11 yellow
TinyGPSPlus gps;//This is the GPS object that will pretty much do all the grunt work with the NMEA data
void setup()
{
  Serial.begin(9600);//This opens up communications to the Serial monitor in the Arduino IDE
  serial_connection.begin(9600);//This opens up communications to the GPS
  Serial.println("GPS Start");//Just show to the monitor that the sketch has started
  Serial.println("HMC5883 Magnetometer Test"); Serial.println("");
  Serial.begin(9600);
}

void loop()
{
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
  
}
