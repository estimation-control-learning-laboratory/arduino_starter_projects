int motorPin1 = 5;  // Connected to black (Motor -)
int motorPin2 = 6;  // Connected to red (Motor +)
int enablePin = 9;  // PWM pin for speed control

int joystickPin = A0;  // Joystick X-axis connected to A0

void setup() {
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(enablePin, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  int joystickValue = analogRead(joystickPin);

  int speed = map(abs(joystickValue - 512), 0, 512, 0, 255);  // Map to speed 0-255
  int direction = joystickValue - 512;  // Negative for left (CCW), positive for right (CW)

  if (direction > 0) {
    // Turn motor clockwise (right movement)
    runMotorClockwise(speed);
  } else if (direction < 0) {
    // Turn motor counterclockwise (left movement)
    runMotorCounterclockwise(speed);
  } else {
    // Stop motor if joystick is centered
    stopMotor();
  }

  Serial.print("Joystick Value: ");
  Serial.print(joystickValue);
  Serial.print(" | Motor Speed: ");
  Serial.println(speed);

  delay(100);  // Small delay to smooth the operation
}

void runMotorClockwise(int speed) {
  digitalWrite(motorPin1, HIGH);  // Set Motor + (red) to HIGH
  digitalWrite(motorPin2, LOW);   // Set Motor - (black) to LOW
  analogWrite(enablePin, speed);  // Control speed using PWM
}

// Function to run motor counterclockwise
void runMotorCounterclockwise(int speed) {
  digitalWrite(motorPin1, LOW);   // Set Motor + (red) to LOW
  digitalWrite(motorPin2, HIGH);  // Set Motor - (black) to HIGH
  analogWrite(enablePin, speed);  // Control speed using PWM
}

// Function to stop motor
void stopMotor() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  analogWrite(enablePin, 0);      // Set speed to 0
}
