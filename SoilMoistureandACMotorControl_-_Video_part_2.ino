// This code was done by Ihab Hassoun and Ahmad Zakaria
#define BLYNK_PRINT Serial
#include <SPI.h>;
#include <SimpleTimer.h>;
#include <ESP8266WiFi.h>;
#include <BlynkSimpleEsp8266.h>;

char auth[] = "Enter your Authentication Token here";   // Auth is sent by Blynk to you
char ssid[] = "Your Router Name";   // you can also use your hotspot on phone, then you must write the name of your hotspot here and its password      
char pass[] = "Your Router Password";
SimpleTimer timer;   // Download the SimpleTimer Library and add it to the Arduino IDE. this video was helpful: https://www.youtube.com/watch?v=_MYBoUl1wwg
const int sensorPin = A0;   
int sensorState = 0;
int lastState = 0;
int lastStateWet = 0;

void notification()
{
  if (sensorState >= 51) {         //send notification
  Blynk.notify("Water your plants");
 Serial.println("Water your plants");

    } 
}
void sendSensor(){
 sensorState = analogRead(sensorPin);
 sensorState = map(sensorState, 0, 1023, 0, 100);
Serial.println(sensorState);
Blynk.virtualWrite(A0, sensorState);

if (sensorState >= 51 && lastState == 0) { 
 lastState = 1;                         //toggles message sent state
 lastStateWet = 0;                  //toggles message sent stateWET
 Blynk.notify("Water your plants");
   } 
else if (sensorState <= 49 && lastStateWet == 0)
{
   lastState = 0;
   lastStateWet = 1;
   Blynk.notify("Plants were watered");
 }

}


void setup()
{
 Serial.begin(115200);
 Blynk.begin(auth, ssid, pass);
 pinMode(sensorPin, INPUT);
 timer.setInterval(1000L, sendSensor);   // send data each second   
 timer.setInterval(60000L, notification); // send notification each 1 min (60000 ms = 1 min) 
}

void loop()
{ 
 Blynk.run();
 timer.run();

}
