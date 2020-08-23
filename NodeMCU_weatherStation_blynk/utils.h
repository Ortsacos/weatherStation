#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h>
#include <SimpleTimer.h>

//Blink authentication
char auth[] = "i4bpEO9GX8ArXqBu_i0doquzUOVJLMUv";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "ssid";
char pass[] = "password";

//Serial Communication
int br = 9600;

// Timers
SimpleTimer dataTimer;

//Data constants
#define WIND_DIVISER 23
typedef enum {
  mark1 = 1 * WIND_DIVISER,
  mark2,
  mark3,
  mark4,
  mark5,
  mark6,
  mark7,
  mark8,
  mark9,
  mark10,
  mark11,
};

//Rain sensor
#define DRY 1023
#define HUM 750
#define WET 555
#define RAIN 350
