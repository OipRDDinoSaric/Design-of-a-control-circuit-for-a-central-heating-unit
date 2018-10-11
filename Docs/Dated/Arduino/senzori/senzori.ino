#include <OneWire.h>
#include <DallasTemperature.h>
#include <ESP8266WiFi.h>

//gdje se nalazi senzor?
const uint8_t SENZOR_ID = 2; //Plava Soba
 
// Senzor je spojen na D5 od esp-a
#define ONE_WIRE_BUS 14

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
char *ssid      = "CentralnoGrijanje";
char *password  = "ezpzlmnsqz123";

WiFiClient client;
 
void setup(void)
{
  uint8_t flag=0;
  Serial.begin(9600);
  sensors.begin();
  WiFi.mode(WIFI_STA);
  WiFi.begin (ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
    flag++;
    if(flag>20){
      Serial.println("Nema interneta, spavam 10 sekundi");
      ESP.deepSleep(10e6); 
    }
  }
}
 
 
void loop(void)
{
 float Trenutna_Temp;
 const char* host ="192.168.69.4";
 //spajam se na server od centralnog
  Serial.print("connecting to ");
  Serial.println(host);

  if (!client.connect(host, 80)) {
        Serial.println("connection failed");
        Serial.println("wait 1 sec...");
        delay(1e3);
        return;
  }
  //citam temperaturu sa senzora
  sensors.requestTemperatures();
	Trenutna_Temp=sensors.getTempCByIndex(0);
  
  client.println(SENZOR_ID);
  client.println(Trenutna_Temp);

  Serial.println("closing connection");
  //client.stop();
  
  Serial.print("Trenutna temperatura je: ");
  Serial.println(Trenutna_Temp);
  ESP.deepSleep(40e6); 
}


