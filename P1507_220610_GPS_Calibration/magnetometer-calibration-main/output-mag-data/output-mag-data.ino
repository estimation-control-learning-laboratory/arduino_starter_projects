#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>

Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);

void setup() {
  Serial.begin(9600);
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
  sensors_event_t event; 
  mag.getEvent(&event);
  Serial.print(event.magnetic.x,6);
  Serial.print(",");
  Serial.print(event.magnetic.y,6);
  Serial.print(",");
  Serial.println(event.magnetic.z,6);
  delay(100);
}
