int motorPin1 = 5; // Connected to black (Motor -)
int motorPin2 = 6; // Connected to red (Motor +)
int enablePin = 9; // PWM pin for speed control

// Encoder pins
int encoderPinA = 2; // Connected to yellow (OUTA)
int encoderPinB = 3; // Connected to white (OUTB)

volatile int encoderPos = 0; // Variable to store encoder position

void setup() {
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(enablePin, OUTPUT);

  pinMode(encoderPinA, INPUT);
  pinMode(encoderPinB, INPUT);

  attachInterrupt(digitalPinToInterrupt(encoderPinA), updateEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderPinB), updateEncoder, CHANGE);
  
  Serial.begin(9600);
    stopMotor();
}

void loop() {
  // Example: Run motor forward at half speed
  runMotor(128);
  delay(2000); // Run for 2 seconds

  // Print encoder position
  Serial.print("Encoder Position: ");
  Serial.println(encoderPos);

  // Stop motor
  stopMotor();
  delay(1000); // Wait for 1 second

  // Run motor backward at full speed
  runMotor(-255);
  delay(2000); // Run for 2 seconds

  // Print encoder position
  Serial.print("Encoder Position: ");
  Serial.println(encoderPos);

  // Stop motor
  stopMotor();
  delay(1000); // Wait for 1 second
}

void runMotor(int speed) {
  if (speed > 0) {
    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);
  } else if (speed < 0) {
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, HIGH);
    speed = -speed; // Convert speed to positive for PWM
  }
  analogWrite(enablePin, speed);
}

void stopMotor() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  analogWrite(enablePin, 0);
}

// Interrupt service routine for encoder
void updateEncoder() {
  int stateA = digitalRead(encoderPinA);
  int stateB = digitalRead(encoderPinB);
  
  // Determine the direction of rotation
  if (stateA == stateB) {
    encoderPos++;
  } else {
    encoderPos--;
  }
}
