#define ENA 3    // L293D Enable 1 pin (PWM control for speed)
#define IN1 9    // L293D Input 1 (controls motor direction)
#define IN2 10   // L293D Input 2 (controls motor direction)
#define OUTA 2   // Rotary Encoder OUTA pin (equivalent to CLK)
#define OUTB 4   // Rotary Encoder OUTB pin (equivalent to DT)

int currentStateOUTA;
int lastStateOUTA;
int motorSpeed = 0; // Initialize motor speed

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(OUTA, INPUT);
  pinMode(OUTB, INPUT);
  
  lastStateOUTA = digitalRead(OUTA);
  Serial.begin(9600);
}

void loop() {
  currentStateOUTA = digitalRead(OUTA);

  // If the state of OUTA has changed, we can determine the direction
  if (currentStateOUTA != lastStateOUTA) {
    // Check the direction of rotation
    if (digitalRead(OUTB) != currentStateOUTA) {
      // Encoder is rotating clockwise
      motorSpeed = 150; // Set a forward speed (adjust value as needed)
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
    } else {
      // Encoder is rotating counterclockwise
      motorSpeed = 150; // Set a reverse speed (adjust value as needed)
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
    }
    analogWrite(ENA, motorSpeed); // Apply the speed to the motor
  }

  lastStateOUTA = currentStateOUTA; // Update the last state
}
