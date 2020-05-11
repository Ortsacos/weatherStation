#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h>
#include <SimpleTimer.h>

//Blink authentication
char auth[] = "i4bpEO9GX8ArXqBu_i0doquzUOVJLMUv";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "YourWIFIName";
char pass[] = "YourWIFIPassword";

//Serial Communication
int br = 9600;

// Timers
SimpleTimer dataTimer;

//Data constants

//Rain sensor
#define DRY 1023
#define WET 555
#define RAIN 350
