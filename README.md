# FocusFlow

FocusFlow is a wearable device designed to monitor stress levels using heart rate, SpO2, and eye movement data. The device classifies the wearer's stress into five levels (0-4) and triggers specific actions based on the stress level detected.

## Features
- **Stress Level Monitoring:** Classifies stress levels from 0 to 4.
  - **Level 0 & 1:** No action.
  - **Level 2:** Device vibrates for 5 seconds.
  - **Level 3:** Vibration and a melody plays.
  - **Level 4:** Vibration, melody, and a text message is sent to a relative via AWS.
- **AWS Cloud Integration:** Data is uploaded to the cloud every 30 seconds for real-time monitoring and notifications.

## System Workflow
![FocusFlow System Flowchart](images/flowchart.png)

## Repository Contents
- **/src**: Source code for the wearable device.
  - Contains the main code for sensor data collection, stress level classification, and AWS integration.
- **/images**: Contains the flowchart of the system.
- **README.md**: Documentation of the project (this file).
- **LICENSE**: License for the project.

## Setup Instructions

1. **Clone this repository:**
   ```bash
   git clone https://github.com/khadija-14/FocusFlow.git

1. **Install Dependencies:**
   Use the Arduino Library Manager to install the required libraries:
   - [ArduinoJson](https://github.com/bblanchon/ArduinoJson)
   - [PubSubClient](https://github.com/knolleary/pubsubclient)
   - [PulseSensorPlayground](https://github.com/WorldFamousElectronics/PulseSensorPlayground)
   - [Arduino Tone Library](https://www.arduino.cc/reference/en/libraries/tone/)


2. **Upload Code:**
   Use the Arduino IDE to upload the code to your ESP32 microcontroller.

3. **Configure AWS IoT:**
   Set up AWS IoT Core to receive data and trigger notifications for stress level 4.

## Acknowledgements
- **SparkFun:** For the [MAX30105 Library](https://github.com/sparkfun/SparkFun_MAX3010x_Sensor_Library).
- **Arduino:** For the [Tone library](https://www.arduino.cc/reference/en/libraries/tone/).
- **Espressif:** For the [ESP-AWS SDK](https://github.com/espressif/esp-aws-iot).
- **PubSubClient:** For the [PubSubClient library](https://github.com/knolleary/pubsubclient), used for MQTT communication with AWS IoT.

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
