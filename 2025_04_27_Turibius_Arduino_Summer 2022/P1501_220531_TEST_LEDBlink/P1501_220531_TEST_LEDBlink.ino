void setup() {
  pinMode(13,OUTPUT); // LED pin
}

void loop() {
  // Simple LED blink if on
  digitalWrite(13,HIGH);
  delay(900);
  digitalWrite(13,LOW);
  delay(900);
}
