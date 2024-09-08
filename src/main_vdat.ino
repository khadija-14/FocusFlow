#include "eye_movement.h"
#include "HeartrateSpo2.h"
#include "AwsIoT.h"
#include "motor_control.h"
#include "melody.h"

SensorReader sensorReader;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  sensorReader.begin();
  setupSensors();
  connectAWS();
  setupMotor();
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  eyemovrate = calculateEyeMovementRate();
  hr = sensorReader.getHeartRate();
  spo2 = sensorReader.getSpO2();

  if ((95<=spo2<=97)&&(60<=eyemovrate<=80)&&(50<=hr<=55)) {
    stresslevel = 0;
  } 
  else if ((92<=spo2<=95)&&(80<=eyemovrate<=85)&&(55<=hr<=60)) {
    stresslevel = 1;
  } 
  else if ((90<=spo2<=92)&&(85<=eyemovrate<=95)&&(60<=hr<=65)) {
    stresslevel = 2;
  }
  else if ((88<=spo2<=90)&&(95<=eyemovrate<=100)&&(65<=hr<=75)) {
    stresslevel = 3;
  }
  else if ((82<=spo2<=88)&&(100<=eyemovrate<=105)&&(75<=hr<=85)) {
    stresslevel = 4;
  }
  else {
    Serial.println("Stress level can't be determined.");
  }

  Serial.println("Eye movement rate: ");
  Serial.print(eyemovrate);

  Serial.print(F("SpO2: "));
  Serial.print(spo2);
  Serial.print(F("%  Eye Movement Rate: "));
  Serial.print(eyemovrate);
  Serial.print(F("  Heart Rate: "));
  Serial.println(hr);
  Serial.print(F("  Stress Level: "));
  Serial.println(stresslevel);
  publishMessage();
  client.loop();

  switch(stresslevel){
      case 2:

         runMotor();
         break;

      case 3:
         runMotor();
         playMelody();
         break;

      case 4:
         runMotor();
         playMelody();
         break;

      default:
         break;
   }
  delay(20000);  
}
