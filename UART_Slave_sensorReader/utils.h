#include <SoftwareSerial.h>
#include <DHT.h>

//Arduino nano UART conn with NodeMCU
#define RX 2
#define TX 3

//Rain, wind and DHT11 sensor PIN
//TODO: Inlcude moister sensor for future projects
int rainSensor = A0;
int windSensor = A1;
int dhtSensor = 4;  //digital 4

//define temp sensor type
#define DHTTYPE DHT11

DHT dht(dhtSensor, DHTTYPE);

//Serial Communication
int br = 9600;
