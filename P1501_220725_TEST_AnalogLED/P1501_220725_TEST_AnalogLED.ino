int pin = 10;
float power = 50; // number %
uint8_t outputLED = (power / 100) * 255;

void setup() {
  pinMode(pin, OUTPUT);
//  Serial.begin(9600);
}

void loop() {
  analogWrite(pin, outputLED);
//  Serial.print(power);
//  Serial.print('\t');
//  Serial.println(outputLED);
}
