#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h>
#include <SimpleTimer.h>
#include "utils.h"
 
String myString; // complete message from arduino, which consistors of snesors data
char rdata; // received charactors
 
int rainVal, windVal,tempVal, humVal; // sensors
int rainCount, windCount, windPeak;
String rainStatus;
//Counts how many times the rain sensor value is bellow 1023
int count;
float windSpeed;
boolean avgRdy = false;

// This function sends Arduino's up time every second to Virtual Pin (1).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void sendSensorData()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V6, tempVal);
  Blynk.virtualWrite(V1, humVal);
  Blynk.virtualWrite(V3, windSpeed);
  Blynk.virtualWrite(V2, rainStatus);
}


//Calculates the average of 10 values from the rain and wind sensors
void averageValues()
{
  if (count < 10) {
    rainCount += rainVal;
    windCount += windVal;
    count++;
    avgRdy = false;
  }else if (count == 10) {
    count = 0;
    rainCount = rainCount / count;
    windCount = windCount / count;
    avgRdy = true;
  }
}

String checkRain(int rain) {

  if (rain <= RAIN) {
    return "Raining";
  }else if (rain <= WET){
    return "Started to rain";
  }else if (rain <= HUM) {
    return "Humidity";
  }else if (rain <= DRY) {
    return "No rain";
  }
  
}

// Returns the windSpeed (km/h) correspondent to that lvl (1 m/s = 3.6 km/h)
// This is an approximation from the table provided from the sensor seller
float checkWind(int wind) {
  if (wind > mark11) {
    return (35*3.6);
  }else if (wind <= mark1) {
    return (0.1 *3.6);
  }else if (wind <= mark2) {
    return (3.4*3.6);
  }else if (wind <= mark3) {
    return (5.5*3.6);
  }else if (wind <= mark4) {
    return (8.0*3.6);
  }else if (wind <= mark5) {
    return (10.8*3.6);
  }else if (wind <= mark6) {
    return (13.9*3.6);
  }else if (wind <= mark7) {
    return (17.2*3.6);
  }else if (wind <= mark8) {
    return (20.8*3.6);
  }else if (wind <= mark9) {
    return (24.5*3.6);
  }else if (wind <= mark10) {
    return (28.5*3.6);
  }else if (wind <= mark11) {
    return (32.6*3.6);
  }
}
 
void setup()
{
  // Debug console
  Serial.begin(br);
 
  Blynk.begin(auth, ssid, pass);

  // Every second call the sendSensorData fucntion
  dataTimer.setInterval(1000L, sendSensorData); 

  Serial.println("Weather Station Master Started.");
}
 
void loop()
{
   if (Serial.available() == 0 ) 
   {
  Blynk.run();
  dataTimer.run(); // Initiates Simpletimer
   }
   
  if (Serial.available() > 0 ) 
  {
    rdata = Serial.read(); 
    myString = myString+ rdata; 
    if( rdata == '\n')
    {
        Serial.println(myString); 
      // new code
      String l = getValue(myString, ',', 0);
      String m = getValue(myString, ',', 1);
      String n = getValue(myString, ',', 2);
      String p = getValue(myString, ',', 3);
 
 
      rainVal = l.toInt();
      windVal = m.toInt();
      if (windVal > windPeak) {
        windPeak = windVal;
      }
      tempVal = n.toInt();
      humVal = p.toInt();
      myString = "";
      
      averageValues();
      windSpeed = checkWind(windVal);
      rainStatus = checkRain(rainVal);
 
      // end new code
    }
  }
  delay(100);
}
 
String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;
 
    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
