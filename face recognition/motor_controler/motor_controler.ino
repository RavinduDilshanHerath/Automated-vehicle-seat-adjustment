#include <Servo.h>
#include <Stepper.h>

// ----- Servo Setup -----
Servo restServo;      // Rest position servo (pin 3)
Servo verticalServo;  // Vertical position servo (pin 4)

// ----- Stepper Setup -----
const int stepsPerRevolution = 2048;
Stepper myStepper(stepsPerRevolution, 8, 6, 7, 5);  // IN1, IN3, IN2, IN4

// ----- Input and Flag -----
const int signalPin = 2;      // Input pin for signal (button or sensor)
bool signalDetected = false;  // Prevent multiple triggers

// ----- Initial Servo Setup -----
void initialRestSetup() {
  for (int pos = 110; pos <= 130; pos++) {
    restServo.write(pos);
    delay(100);
  }
}

void initialVerticalSetup() {
  for (int angle = 130; angle <= 180; angle++) {
    verticalServo.write(angle);
    delay(100);
  }
}

// ----- Servo Motion After Signal -----
void moveToRestPosition() {
  for (int pos = 130; pos >= 110; pos--) {
    restServo.write(pos);
    delay(100);
  }
}

void moveToVerticalPosition() {
  for (int angle = 180; angle >= 130; angle--) {
    verticalServo.write(angle);
    delay(100);
  }
}

// ----- Stepper Initial and Forward Motion -----
void initialStepperSetup() {
  myStepper.setSpeed(10);
  myStepper.step(-700);  // Move backward initially to set start position
}

void performForwardStepperMotion() {
  myStepper.setSpeed(10);
  myStepper.step(700);   // Move forward on signal detection
}

// ----- Setup -----
void setup() {
  pinMode(signalPin, INPUT);

  restServo.attach(3);
  verticalServo.attach(4);

  // Run initial setups sequentially
  initialRestSetup();
  delay(3000);                 // Small delay between motions
  initialVerticalSetup();
  delay(3000);
  initialStepperSetup();
}

// ----- Loop -----
void loop() {
  if (!signalDetected && digitalRead(signalPin) == HIGH) {
    signalDetected = true;    // Avoid multiple triggers

    moveToRestPosition();
    delay(3000);               // Small delay for smoothness
    moveToVerticalPosition();
    delay(3000);
    performForwardStepperMotion();
  }

  // Otherwise do nothing
}
