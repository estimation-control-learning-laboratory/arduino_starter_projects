// Pin definitions
const int pinOUTA = 2;
const int pinOUTB = 3;

// Variables
volatile int encoderValue = 0;
volatile int lastEncoded = 0;

void setup() {
  // Set pins as inputs
  pinMode(pinOUTA, INPUT);
  pinMode(pinOUTB, INPUT);
  
  // Enable pull-up resistors (optional if encoder doesn't have them)
  digitalWrite(pinOUTA, HIGH);
  digitalWrite(pinOUTB, HIGH);

  // Attach interrupts
  attachInterrupt(digitalPinToInterrupt(pinOUTA), updateEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pinOUTB), updateEncoder, CHANGE);

  // Start serial communication
  Serial.begin(9600);
}

void loop() {
  // Print the encoder value
  Serial.print("Encoder Value: ");
  Serial.println(encoderValue);
  delay(100);  // Update every 100ms
}

void updateEncoder() {
  // Read the two pins
  int MSB = digitalRead(pinOUTA);  // Most significant bit
  int LSB = digitalRead(pinOUTB);  // Least significant bit

  int encoded = (MSB << 1) | LSB;  // Create a binary number
  int sum = (lastEncoded << 2) | encoded;

  // Update encoderValue based on the direction of rotation
  if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue++;
  if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue--;

  lastEncoded = encoded;  // Store this value for next time
}
