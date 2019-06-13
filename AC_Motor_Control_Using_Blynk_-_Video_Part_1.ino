#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


char auth[] = "Enter your Authentication Token here";   // Auth is sent by Blynk to you
char ssid[] = "Your Router Name";   // you can also use your hotspot on phone, then you must write the name of your hotspot here and its password      
char pass[] = "Your Router Password";

void setup()
{
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
 
}

void loop()
{
  Blynk.run();
                
}
