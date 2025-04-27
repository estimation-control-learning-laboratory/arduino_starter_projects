int dot = 100;
int dash = 400;
int smallPause = 200;
int bigPause = 600;
int pinName = 8;

void setup() {
  // put your setup code here, to run once:
  pinMode(pinName, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  //S
  digitalWrite(pinName,HIGH);
  delay(dot);
  digitalWrite(pinName,LOW);
  delay(smallPause);

  digitalWrite(pinName,HIGH);
  delay(dot);
  digitalWrite(pinName,LOW);
  delay(smallPause);

  digitalWrite(pinName,HIGH);
  delay(dot);
  digitalWrite(pinName,LOW);
  delay(smallPause);

  delay(bigPause);

  //O
  digitalWrite(pinName,HIGH);
  delay(dash);
  digitalWrite(pinName,LOW);
  delay(smallPause);

  digitalWrite(pinName,HIGH);
  delay(dash);
  digitalWrite(pinName,LOW);
  delay(smallPause);

  digitalWrite(pinName,HIGH);
  delay(dash);
  digitalWrite(pinName,LOW);
  delay(smallPause);

  delay(bigPause);

  //S
  digitalWrite(pinName,HIGH);
  delay(dot);
  digitalWrite(pinName,LOW);
  delay(smallPause);

  digitalWrite(pinName,HIGH);
  delay(dot);
  digitalWrite(pinName,LOW);
  delay(smallPause);

  digitalWrite(pinName,HIGH);
  delay(dot);
  digitalWrite(pinName,LOW);
  delay(smallPause);

  delay(bigPause);
  delay(bigPause);
  delay(bigPause);
}
