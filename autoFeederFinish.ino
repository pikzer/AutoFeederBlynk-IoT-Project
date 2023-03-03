#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <ESP32Servo.h>
Servo servo ;
#define BLYNK_TEMPLATE_ID           "TMPLxxxxxx"
#define BLYNK_DEVICE_NAME           "Auto Feeder"
#define BLYNK_AUTH_TOKEN            ""
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Enrique174_2.4G";
char pass[] = "OakSia174";

void feed(){
  servo.write(50);
  delay(175) ;
  servo.write(0) ;
}

BLYNK_WRITE(V1)
{
  int pinValue = param.asInt();
  // assigning incoming value from pin V1 to a variable
  Serial.println(pinValue) ;
  if(pinValue == 1){
    feed();
  }
}
void setup() {
  Serial.begin(115200);
  servo.attach(13) ;
  servo.write(0) ;
  pinMode(15,INPUT);
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  Blynk.run();
  if(digitalRead(15)==LOW){
    feed();
  }
}
