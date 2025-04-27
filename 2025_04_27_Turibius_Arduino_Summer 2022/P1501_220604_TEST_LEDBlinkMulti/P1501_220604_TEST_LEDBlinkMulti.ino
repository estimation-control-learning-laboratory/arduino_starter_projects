void setup() {
  pinMode(13,OUTPUT); // LED pin
  pinMode(8,OUTPUT);
}

void loop() {
  digitalWrite(13,HIGH);
  delay(100);
  digitalWrite(8,HIGH);
  delay(100);
  digitalWrite(13,LOW);
  delay(100);
  digitalWrite(8,LOW);
  delay(100);
}
