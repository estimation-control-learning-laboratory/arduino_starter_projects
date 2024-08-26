#include <Stepper.h>

#define STEPS_PER_REV 2048  // Number of steps per revolution for the stepper motor

#define IN1 8  // ULN2003 IN1 to Arduino pin 8
#define IN2 9  // ULN2003 IN2 to Arduino pin 9
#define IN3 10 // ULN2003 IN3 to Arduino pin 10
#define IN4 11 // ULN2003 IN4 to Arduino pin 11
#define OUTA 2 // Rotary Encoder OUTA pin
#define OUTB 3 // Rotary Encoder OUTB pin

Stepper stepperMotor(STEPS_PER_REV, IN1, IN2, IN3, IN4);

int lastStateOUTA;
int currentStateOUTA;

void setup() {
  pinMode(OUTA, INPUT);
  pinMode(OUTB, INPUT);

  lastStateOUTA = digitalRead(OUTA);

  Serial.begin(9600);
}

void loop() {
  currentStateOUTA = digitalRead(OUTA);

  // If the state of OUTA has changed, determine the direction
  if (currentStateOUTA != lastStateOUTA) {
    // Check the direction of rotation
    if (digitalRead(OUTB) != currentStateOUTA) {
      // Encoder is rotating clockwise
      stepperMotor.step(1000); // Move one step clockwise
      Serial.println("Step Clockwise");
    } else {
      // Encoder is rotating counterclockwise
      stepperMotor.step(-1000); // Move one step counterclockwise
      Serial.println("Step Counterclockwise");
    }
  }

  lastStateOUTA = currentStateOUTA; // Update the last state
}
