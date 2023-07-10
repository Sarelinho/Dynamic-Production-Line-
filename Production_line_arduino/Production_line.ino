#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiUdp.h>
#include <ESP8266HTTPClient.h>

String prossec ;
unsigned long previousMillis;
unsigned long currentMillis;
unsigned long LightCurrent; 
unsigned long lightPrevius; 
int lightLevel;
int cnt;
double avg;
int num;
#define relayPin D4
#define greenLed D1

void setup() {
  Serial.begin(9600);
   wifi_Setup();
  
   pinMode(relayPin, OUTPUT);
    pinMode(greenLed, OUTPUT);

  num = 1;
  avg = 0;
  cnt = 0;
  previousMillis = 0;
  lightLevel = 0;
  lightPrevius=0;

}
void loop() {
 currentMillis = millis();
     switch (num) {
        case 1:
          relayFunction();
      Serial.println("here");
          
          break;
       case 2:
          LevelOfLight();
                Serial.println("here2");

          break;
        case 3:
          start();
                Serial.println("here3");

          break;
        case 4:
          delayTime();
                Serial.println("here4");

          break;
        default:
          break;
     }
}
  void LevelOfLight() {
    prossec = "setup_time";
    int setupTime = GetData().toInt();
          Serial.println(setupTime);

LightCurrent = millis();
    if(LightCurrent - lightPrevius >=1000)
    {
      cnt++;
      lightLevel += map(analogRead(lightLevel), 0, 1023, 0, 255);
      lightPrevius=LightCurrent;
    }
    if (currentMillis - previousMillis >=setupTime*1000)
    {
      previousMillis = currentMillis;
             avg = lightLevel / cnt;
      num = 3;
      //to next level ,case =3
    } 
    
  }
   void relayFunction() {
    prossec = "heat_time";
     int heatTime = GetData().toInt();
       digitalWrite(relayPin, HIGH);
    if (currentMillis - previousMillis >= heatTime*1000) {
             previousMillis = currentMillis;

       digitalWrite(relayPin, LOW);
       num = 2;
     }  
       //to next level , case = 2
    
   }
   void start() {
     prossec = "test_light";
      int testLight = GetData().toInt();
      //     currentMillis = millis();

     if (currentMillis - previousMillis >= testLight*1000) {
       analogWrite(greenLed, avg);
             previousMillis = currentMillis;
       num = 4;

     } else {
     }
     //to the next level , level = 4 ;
   }
   void delayTime() {

    prossec = "delay";  
     int delayTime = GetData().toInt();

     if (currentMillis - previousMillis >= delayTime*1000) {
             previousMillis = currentMillis;
       avg = 0;
       cnt = 0;
      lightLevel = 0;
             num = 1;
     }
     //to next level , level 1
   }
 