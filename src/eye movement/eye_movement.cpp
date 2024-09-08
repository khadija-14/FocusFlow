#include "eye_movement.h"
#include <Arduino.h>

unsigned long lastTime = 0;
unsigned int eyeMovementCount = 0;
unsigned long interval = 1000; // 1 second

void setupSensors() {
    pinMode(IR_SENSOR_LEFT_PIN, INPUT);
    pinMode(IR_SENSOR_RIGHT_PIN, INPUT);
}

float calculateEyeMovementRate() {
    int leftSensorValue = analogRead(IR_SENSOR_LEFT_PIN);
    int rightSensorValue = analogRead(IR_SENSOR_RIGHT_PIN);

    bool leftEyeMovement = leftSensorValue > 140;
    bool rightEyeMovement = rightSensorValue > 140;

    if (leftEyeMovement || rightEyeMovement) {
        eyeMovementCount++;
    }

    if (millis() - lastTime >= interval) {
        float eyeMovementRate = (float)eyeMovementCount / (interval / 1000.0);
        eyeMovementCount = 0;
        lastTime = millis();
        return eyeMovementRate;
    }
    return 0;
}
