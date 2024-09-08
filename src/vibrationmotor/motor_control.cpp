#include "motor_control.h"
#include <Arduino.h>

int motorPin = 12; // motor transistor is connected to pin 3

void setupMotor() {
    pinMode(motorPin, OUTPUT);
}

void runMotor() {
    digitalWrite(motorPin, HIGH); // vibrate
    delay(5000);  // delay five seconds
    digitalWrite(motorPin, LOW);  // stop vibrating
}
