#include <WiFi.h>
#include <WiFiUdp.h>
#include <OneWire.h> 
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 13
#define lv_water_pin 34 
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

const char * ssid = "Enrique174_2.4G";
const char * pwd = "OakSia174";

const char * udpAddress = "52.187.75.76";
const int udpPort = 30000;

int val = 0 ;

WiFiUDP udp;


void setup() {
  Serial.begin(115200);
  pinMode(lv_water_pin,INPUT);
  WiFi.begin(ssid, pwd);
  Serial.println("");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  udp.begin(udpPort);
  Serial.println("Dallas Temperature IC Control Library");
  sensors.begin();
}

void loop() {
  sensors.requestTemperatures();
  uint8_t buffer[50]   ;  
  float f = sensors.getTempCByIndex(0) ;
  String s = String(f);
  val = analogRead(lv_water_pin);
  int p = 0 ;
  if(val > 500){
//    Serial.println(" Normal");
    p = 49 ;
  }
  if(val < 500){
//    Serial.println(" Abnormal");
    p = 48 ;
  }
//  Serial.println(p) ;
  for(int i = 0 ; i < 6 ; i++){
        int k = s[i] ;
        buffer[i] = k ;
  }
  udp.beginPacket(udpAddress, udpPort);
  buffer[6] = p;
  udp.write(buffer,11);
  udp.endPacket();
  delay(1000);
}
