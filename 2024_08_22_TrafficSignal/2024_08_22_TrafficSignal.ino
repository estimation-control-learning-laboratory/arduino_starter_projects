void setup() {
  // put your setup code here, to run once:
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(4, HIGH);
  delay(5000); // Wait for 5000 millisecond(s)
  digitalWrite(4, LOW);
  digitalWrite(3, HIGH);
  delay(1000); // Wait for 1000 millisecond(s)
  digitalWrite(3, LOW);
  digitalWrite(2, HIGH);
  delay(5000); // Wait for 5000 millisecond(s)
  digitalWrite(2, LOW);
}
