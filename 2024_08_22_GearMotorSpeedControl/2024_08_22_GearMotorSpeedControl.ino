// Motor control pins
int motorPin1 = 5; // Connected to black (Motor -)
int motorPin2 = 6; // Connected to red (Motor +)
int enablePin = 9; // PWM pin for speed control

void setup() {
  // Set motor pins as outputs
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(enablePin, OUTPUT);

  // Initialize Serial Monitor for feedback
  Serial.begin(9600);
}

void loop() {
  // Example: Spin motor at 25% speed
  Serial.println("Motor running at 25% speed");
  runMotor(64);  // 64 out of 255 is approximately 25% speed
  delay(2000);   // Run for 2 seconds

  // Example: Spin motor at 50% speed
  Serial.println("Motor running at 50% speed");
  runMotor(128); // 128 out of 255 is 50% speed
  delay(2000);   // Run for 2 seconds

  // Example: Spin motor at 75% speed
  Serial.println("Motor running at 75% speed");
  runMotor(192); // 192 out of 255 is 75% speed
  delay(2000);   // Run for 2 seconds

  // Example: Spin motor at full speed
  Serial.println("Motor running at 100% speed");
  runMotor(255); // 255 out of 255 is full speed
  delay(2000);   // Run for 2 seconds
  
  // Stop the motor
  stopMotor();
  Serial.println("Motor stopped");
  delay(2000);   // Pause for 2 seconds
}

// Function to run motor in one direction with specified speed
void runMotor(int speed) {
  digitalWrite(motorPin1, HIGH);  // Set Motor + (red) to HIGH
  digitalWrite(motorPin2, LOW);   // Set Motor - (black) to LOW
  analogWrite(enablePin, speed);  // Control speed using PWM
}

// Function to stop motor
void stopMotor() {
  digitalWrite(motorPin1, LOW);   // Stop motor by setting both motor pins LOW
  digitalWrite(motorPin2, LOW);
  analogWrite(enablePin, 0);      // Set speed to 0
}
