//-----------------------------------
//LIBRARIES
//-----------------------------------
#include <DallasTemperature.h>
#include <OneWire.h>
#include <ESP8266WiFi.h>
//-----------------------------------
//FUNCTIONS
//-----------------------------------
void temperature_setup();
void temperature_loop();
void client_setup();
void client_loop();
//-----------------------------------
//CONSTANTS
//-----------------------------------
// everything is in seconds
#define ERROR_DEEP_SLEEP_AMOUNT 50
#define DEEP_SLEEP_AMOUNT 60

//#define DINO_DEBUG_ENABLE
#define dbSerial Serial

#ifdef DINO_DEBUG_ENABLE
#define dbSerial1print(a)    dbSerial.print(a)
#define dbSerial1println(a)  dbSerial.println(a)
#define dbSerial1begin(a)    dbSerial.begin(a)
#else
#define dbSerial1print(a)    do{}while(0)
#define dbSerial1println(a)  do{}while(0)
#define dbSerial1begin(a)    do{}while(0)
#endif
#define DEVICEID 8  // Van
// Data wire of the temperature sensor DS18B20 is plugged into port D5 on ESP8266
#define TEMP_SENSOR_PIN D5
char* APssid = "CentralHeating";
char* APpass = "123123123";
IPAddress     server(192,168,4,1);
WiFiClient    client1;
//-----------------------------------
//VARIABLES AND DATATYPES
//-----------------------------------
// OneWire is needed for work with DS18B20 temperature sensor
OneWire oneWire(TEMP_SENSOR_PIN);
// Object for temperature sensor
DallasTemperature sensors(&oneWire);

double CurrTemp = -127;
char* charCurrTemp = "-127";

boolean turnoff = false, error = false;

uint8_t temp_counter = 0, connection_counter = 0;
