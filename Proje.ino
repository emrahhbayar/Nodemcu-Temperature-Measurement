#include <DHT.h>
#include <ThingSpeak.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#define DHTPIN D1 

SoftwareSerial BTserial(D3,D4);
DHT dht(DHTPIN, DHT11);
unsigned long kanalNumarasi = 1244892;
const int fieldNumarasi = 1;
const char *agAdi =  "EV";  
const char *sifre =  "wifi_sifre";
const char * apiKey = "thingspeak_apikey";
WiFiClient istemci;

void setup() {
  delay(1000);
  Serial.begin(9600); 
  BTserial.begin(9600); 
  dht.begin();
  ThingSpeak.begin(istemci);
  WiFi.begin(agAdi, sifre);
 
      while (WiFi.status() != WL_CONNECTED) 
     {
            delay(500);
            Serial.print(".");
     }
      Serial.println("");
      Serial.println("WiFi bağlandı.");
}

void loop() {
  
  float sicaklik = dht.readTemperature();
  BTserial.println("Sıcaklık: "+String(sicaklik)+" °C");
  Serial.println("Sıcaklık: "+String(sicaklik)+" °C");
  ThingSpeak.writeField(kanalNumarasi, fieldNumarasi, sicaklik, apiKey);   
 
  
  delay(1000);
}
