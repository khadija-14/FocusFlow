#include <pgmspace.h>
#include <ArduinoJson.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include "WiFi.h"
 
#ifndef AWS_IOT_H
#define AWS_IOT_H
#define THINGNAME "esp32"                        
 
const char WIFI_SSID[] = "***************";               
const char WIFI_PASSWORD[] = "***************";           
const char AWS_IOT_ENDPOINT[] = "***************";       
 
// Amazon Root CA 1                                                //change this
static const char AWS_CERT_CA[] PROGMEM = R"EOF(
 -----BEGIN CERTIFICATE-----
*******************************
-----END CERTIFICATE-----
)EOF";
 
// Device Certificate                                               //change this
static const char AWS_CERT_CRT[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
************************************
-----END CERTIFICATE-----
 )KEY";
 
// Device Private Key                                               //change this
static const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(
 -----BEGIN RSA PRIVATE KEY-----
*****************************************
-----END RSA PRIVATE KEY-----
 
)KEY";

// Declare your functions and variables
extern PubSubClient client;
extern float spo2;
extern float eyemovrate;
extern float hr;
extern int stresslevel;
void connectAWS();
void publishMessage();
void messageHandler(char* topic, byte* payload, unsigned int length);

#endif
