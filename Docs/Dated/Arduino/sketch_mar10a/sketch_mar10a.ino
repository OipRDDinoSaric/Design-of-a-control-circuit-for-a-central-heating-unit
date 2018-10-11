#include <ESP8266WiFi.h>

char *ssid      = "RIGOLGRADNJA";               // Set you WiFi SSID
char *password  = "ezpzlmnsqz123";               // Set you WiFi password
char *espssid   = "CentralnoGrijanje";
IPAddress ip(192,168,69,4);
IPAddress gateway(192,168,69,1);
IPAddress subnet(255,255,255,0);


WiFiServer server(80);

unsigned long time_prev=0, blynk_prev=0, temp0_prev=0, net_prev=0, net_delay=30*1000*1000, reconn_delay=10*1000*1000, time_delay=50*1000*1000, temp0_delay=60*1000*1000, blynk_delay=8*1000*1000;


void setup() {
  Serial.begin(9600);
  WiFi.softAPConfig(ip,gateway,subnet);
  WiFi.softAP(espssid, password);
  server.begin();
}

void loop() {
  unsigned long run_time=micros();
  boolean reconn_active=false;
  if(WiFi.status() != WL_CONNECTED){
      if((run_time>=net_prev+net_delay+reconn_delay) || net_prev==0){
            Serial.println("Pokusajem se spojit");
            WiFi.mode(WIFI_AP_STA);
            WiFi.begin(ssid, password);
            net_prev=run_time;
            reconn_active=true;
        }
      if(run_time>=net_prev+reconn_delay/* && reconn_active*/){
            WiFi.mode(WIFI_AP);
            Serial.println("Nije se spojio");
            reconn_active=false;
      }
    }
}
