#define encoderPinA 2
#define encoderPinB 3

int lastStateA;
String rotationDirection = "";  

unsigned long previousMillis = 0;  
const long interval = 500;  

void setup() {
  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(encoderPinB, INPUT_PULLUP);

  lastStateA = digitalRead(encoderPinA);
  Serial.begin(9600);
}

void loop() {
  int currentStateA = digitalRead(encoderPinA);

  if (currentStateA != lastStateA) {
    if (digitalRead(encoderPinB) != currentStateA) {
      rotationDirection = "Clockwise";
    } else {
      rotationDirection = "Counterclockwise";
    }
    lastStateA = currentStateA;
    previousMillis = millis();
  }

  unsigned long currentMillis = millis();

  if ((currentMillis - previousMillis >= interval) && rotationDirection != "") {
    Serial.println(rotationDirection);
    rotationDirection = "";
  }
  delay(100);
}
