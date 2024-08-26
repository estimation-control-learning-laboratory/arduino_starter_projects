// Define joystick pins
const int VRx = A0;
const int VRy = A1;
const int SW = 2;

// Define 7-segment display pins
const int segPins[] = {3, 4, 5, 6, 7, 8, 9, 10};
const int digitPins[] = {11, 12, 13, 0}; // D0 (RX)

// Define digit segments (for common cathode)
const byte digits[10] = {
  0b00111111, // 0
  0b00000110, // 1
  0b01011011, // 2
  0b01001111, // 3
  0b01100110, // 4
  0b01101101, // 5
  0b01111101, // 6
  0b00000111, // 7
  0b01111111, // 8
  0b01101111  // 9
};

// Initialize counter
int counter = 0;
bool lastUpState = HIGH;
bool lastDownState = HIGH;

void setup() {
  // Initialize joystick pins
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(SW, INPUT_PULLUP);
  
  // Initialize 7-segment display pins
  for (int i = 0; i < 8; i++) {
    pinMode(segPins[i], OUTPUT);
  }
  for (int i = 0; i < 4; i++) {
    pinMode(digitPins[i], OUTPUT);
    digitalWrite(digitPins[i], HIGH); // Turn off all digits initially
  }
}

void loop() {
  // Read joystick values
  int yVal = analogRead(VRy);

  // Check if joystick is pushed up and debounce
  if (yVal < 300) {
    if (lastUpState == HIGH) {
      counter++;
      if (counter > 9999) counter = 0;
      lastUpState = LOW;
    }
  } else if (yVal > 700) { // Check if joystick is pushed down and debounce
    if (lastDownState == HIGH) {
      counter--;
      if (counter < 0) counter = 9999;
      lastDownState = LOW;
    }
  } else {
    lastUpState = HIGH;
    lastDownState = HIGH;
  }

  // Display the counter value
  displayNumber(counter);
}

void displayNumber(int number) {
  for (int i = 3; i >= 0; i--) {  // Changed the loop to start from the last digit
    int digit = number % 10;
    number /= 10;

    digitalWrite(digitPins[i], LOW); // Activate the current digit
    for (int j = 0; j < 8; j++) {
      digitalWrite(segPins[j], (digits[digit] >> j) & 0x01);
    }
    delay(5); // Short delay to stabilize the display
    digitalWrite(digitPins[i], HIGH); // Deactivate the current digit
  }
}
