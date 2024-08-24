const int POTENTIOMETER_PIN = A0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorValue = analogRead(POTENTIOMETER_PIN);
  Serial.println(sensorValue);
  delay(1000);

}