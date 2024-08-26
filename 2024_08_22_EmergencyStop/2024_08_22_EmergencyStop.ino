bool motorRunning = false;
bool lastButtonState = LOW;
bool currentButtonState = LOW;

void setup() {
  pinMode(motorPin, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
  currentButtonState = digitalRead(buttonPin);

  if (currentButtonState == HIGH && lastButtonState == LOW) {
    motorRunning = !motorRunning; 
    delay(50); 
  }

  lastButtonState = currentButtonState;

  if (motorRunning) {
    digitalWrite(motorPin, HIGH);
  } else {
    digitalWrite(motorPin, LOW);
  }
}
