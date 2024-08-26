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
  int motorSpeed = map(abs(potValue - 512), 0, 512, 0, 255);  // Map to motor speed range

  if (potValue > 530) {
    analogWrite(motorPin1, motorSpeed);
    digitalWrite(motorPin2, LOW);  // Set motor direction one way
  } else if (potValue < 490) {
    analogWrite(motorPin2, motorSpeed);
    digitalWrite(motorPin1, LOW);  // Set motor direction the other way
  } else {
    analogWrite(motorPin1, 0);
    analogWrite(motorPin2, 0);  // Stop the motor if the potentiometer is centered
  }

