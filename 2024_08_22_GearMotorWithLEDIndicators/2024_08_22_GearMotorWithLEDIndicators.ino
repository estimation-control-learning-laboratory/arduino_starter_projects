int motorPin1 = 5;  // Connected to black (Motor -)
int motorPin2 = 6;  // Connected to red (Motor +)
int enablePin = 9;  // PWM pin for speed control

int ledPins[] = {10, 11, 12, 13}; // Array of LED pins
int numLeds = 4;  // Number of LEDs

void setup() {
  // Set motor control pins as outputs
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(enablePin, OUTPUT);

  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
  }

  Serial.begin(9600);
}

void loop() {
  // Gradually increase motor speed from 0 to 255 (max PWM value)
  for (int speed = 0; speed <= 255; speed += 5) {
    // Set motor direction to forward
    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);

    // Adjust motor speed with PWM
    analogWrite(enablePin, speed);

    // Update LEDs based on motor speed
    updateLeds(speed);

    // Print current speed to Serial Monitor
    Serial.print("Motor Speed: ");
    Serial.println(speed);

    // Delay to control the rate of speed increase
    delay(100);
  }

  // Keep the motor running at full speed for 2 seconds
  delay(2000);

  // Stop the motor
  stopMotor();

  // Keep motor off for 2 seconds before starting again
  delay(2000);
}

// Function to update LEDs based on motor speed
void updateLeds(int speed) {
  int threshold = 255 / numLeds; // Determine speed threshold for each LED
  
  for (int i = 0; i < numLeds; i++) {
    if (speed > (i * threshold)) {
      digitalWrite(ledPins[i], HIGH); // Light up the LED
    } else {
      digitalWrite(ledPins[i], LOW);  // Turn off the LED
    }
  }
}

// Function to stop motor
void stopMotor() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  analogWrite(enablePin, 0);
}
