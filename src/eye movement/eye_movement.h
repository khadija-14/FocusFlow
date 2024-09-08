#ifndef EYE_MOVEMENT_H
#define EYE_MOVEMENT_H

// Define pins for the IR sensors
const int IR_SENSOR_LEFT_PIN = 27;
const int IR_SENSOR_RIGHT_PIN = 4;

// Function declarations
void setupSensors();
float calculateEyeMovementRate();

#endif
