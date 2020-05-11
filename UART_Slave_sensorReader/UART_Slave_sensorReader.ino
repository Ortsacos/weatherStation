#include <SoftwareSerial.h>
#include <DHT.h>
#include "utils.h"

//Arduino nano UART conn with NodeMCU
SoftwareSerial nodemcu(RX,TX);

int rainData = 0;
int windData = 0;
int tempData = 0;
int humData = 0;

String cdata = "";

void setup() {
  Serial.begin(br);
  Serial.flush();
  nodemcu.begin(br);
  nodemcu.flush();

  pinMode(rainSensor, INPUT);
  pinMode(windSensor, INPUT);
  dht.begin();

  Serial.println("Weather Station Slave Started.");

}

void loop() {
  delay(2000);

  rainData = analogRead(rainSensor);
  windData = analogRead(windSensor);
  tempData = dht.readHumidity();
  humData = dht.readTemperature();

    // Check if any reads failed and exit early (to try again).
  if (isnan(humData) || isnan(tempData)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    //return;
  }

  // format data to be sent to NodeMCU
  cdata = cdata + rainData +","+windData+","+tempData+","+humData;
  //debug
  Serial.println(cdata);
  nodemcu.println(cdata);
  cdata = "";
  
}
