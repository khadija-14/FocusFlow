#if (ARDUINO >= 100)
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif
#include "MAX30105.h"
#ifndef HEARTRATESPO2_H_
#define HEARTRATESPO2_H_

bool checkForBeat(int32_t sample);
int16_t averageDCEstimator(int32_t *p, uint16_t x);
int16_t lowPassFIRFilter(int16_t din);
int32_t mul16(int16_t x, int16_t y);

#define FreqS 25    // Sampling frequency
#define BUFFER_SIZE (FreqS * 4) 
#define MA4_SIZE 4  // DONOT CHANGE

// uch_spo2_table is approximated as -45.060*ratioAverage*ratioAverage + 30.354*ratioAverage + 94.845
const uint8_t uch_spo2_table[184] = { 
    95, 95, 95, 96, 96, 96, 97, 97, 97, 97, 97, 98, 98, 98, 98, 98, 99, 99, 99, 99, 
    99, 99, 99, 99, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 
    100, 100, 100, 100, 99, 99, 99, 99, 99, 99, 99, 99, 98, 98, 98, 98, 98, 98, 97, 97, 
    97, 97, 96, 96, 96, 96, 95, 95, 95, 94, 94, 94, 93, 93, 93, 92, 92, 92, 91, 91, 
    90, 90, 89, 89, 89, 88, 88, 87, 87, 86, 86, 85, 85, 84, 84, 83, 82, 82, 81, 81, 
    80, 80, 79, 78, 78, 77, 76, 76, 75, 74, 74, 73, 72, 72, 71, 70, 69, 69, 68, 67, 
    66, 66, 65, 64, 63, 62, 62, 61, 60, 59, 58, 57, 56, 56, 55, 54, 53, 52, 51, 50, 
    49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 31, 30, 29, 
    28, 27, 26, 25, 23, 22, 21, 20, 19, 17, 16, 15, 14, 12, 11, 10, 9, 7, 6, 5, 
    3, 2, 1 
};

static int32_t an_x[BUFFER_SIZE]; // IR
static int32_t an_y[BUFFER_SIZE]; // Red

#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)
// Arduino Uno doesn't have enough SRAM to store 100 samples of IR and Red LED data in 32-bit format.
// To solve this problem, 16-bit MSB of the sampled data will be truncated. Samples become 16-bit data.
void maxim_heart_rate_and_oxygen_saturation(uint16_t *pun_ir_buffer, int32_t n_ir_buffer_length, uint16_t *pun_red_buffer, int32_t *pn_spo2, int8_t *pch_spo2_valid, int32_t *pn_heart_rate, int8_t *pch_hr_valid);
#else
void maxim_heart_rate_and_oxygen_saturation(uint32_t *pun_ir_buffer, int32_t n_ir_buffer_length, uint32_t *pun_red_buffer, int32_t *pn_spo2, int8_t *pch_spo2_valid, int32_t *pn_heart_rate, int8_t *pch_hr_valid);
#endif

void maxim_find_peaks(int32_t *pn_locs, int32_t *n_npks, int32_t *pn_x, int32_t n_size, int32_t n_min_height, int32_t n_min_distance, int32_t n_max_num);
void maxim_peaks_above_min_height(int32_t *pn_locs, int32_t *n_npks, int32_t *pn_x, int32_t n_size, int32_t n_min_height);
void maxim_remove_close_peaks(int32_t *pn_locs, int32_t *pn_npks, int32_t *pn_x, int32_t n_min_distance);
void maxim_sort_ascend(int32_t *pn_x, int32_t n_size);
void maxim_sort_indices_descend(int32_t *pn_x, int32_t *pn_indx, int32_t n_size);

class SensorReader {
public:
    SensorReader();  // Constructor to initialize the sensor
    void begin();    // Method to start the sensor
    void update();   // Method to read data and update heart rate and SpO2 values
    int getHeartRate();  // Get the latest valid heart rate
    int getSpO2();       // Get the latest valid SpO2 value
    bool isHeartRateValid();  // Check if the heart rate is valid
    bool isSpO2Valid();       // Check if the SpO2 value is valid

private:
    MAX30105 particleSensor;
    const byte RATE_SIZE = 4;
    byte rates[4];
    byte rateSpot;
    long lastBeat;
    float beatsPerMinute;
    int beatAvg;

    uint32_t irBuffer[100];
    uint32_t redBuffer[100];
    int32_t bufferLength;
    int32_t spo2;
    int8_t validSPO2;
    int32_t heartRate;
    int8_t validHeartRate;

    void calculateHeartRateAndSpO2();
};

#endif /* HEARTRATESPO2_H_ */