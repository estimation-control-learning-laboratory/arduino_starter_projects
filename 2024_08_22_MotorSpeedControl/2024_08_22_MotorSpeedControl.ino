const int motorPin1 = 9;
const int motorPin2 = 10;
const int potPin = A0;

void setup() {
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int potValue = analogRead(potPin);  // Read potentiometer value
  int motorSpeed = map(potValue, 0, 1023, 0, 255);  // Map to motor speed range
  
  analogWrite(motorPin1, motorSpeed);
  digitalWrite(motorPin2, LOW);  // Set motor direction
  
  Serial.print("Potentiometer Value: ");
  Serial.print(potValue);
  Serial.print("  Motor Speed: ");
  Serial.println(motorSpeed);
  
  delay(100);
}
