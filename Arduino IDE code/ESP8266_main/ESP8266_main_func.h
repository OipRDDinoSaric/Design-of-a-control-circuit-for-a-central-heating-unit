//-----------------------------------
//LIBRARIES
//-----------------------------------
#include <DallasTemperature.h>
#include <OneWire.h>
#include "Nextion.h"
#include <ESP8266WiFi.h>
#include <Ticker.h>
//-----------------------------------
//FUNCTIONS
//-----------------------------------
void temperature_setup();
void temperature_loop();

void nextion_setup();
void nextion_ticker();
void nextion_loop();

void manage_relay_setup();
void manage_relay_ticker();
void manage_relay_loop();

void accesspoint_setup();
void accesspoint_loop();
void reset_current_temperature();
//-----------------------------------
//CONSTANTS
//-----------------------------------
#define dbSerial1 Serial1
  // ##########################
  // ####TEMPERATURE SENSOR####
  // ##########################
// Data wire of the temperature sensor DS18B20 is plugged into port D5 on ESP8266
#define TEMP_SENSOR_PIN D5
#define RELAY_PIN D6
  // ##########################
  // ####      TICKER      ####
  // ##########################
// everything is in seconds
#define RESET_CURRENT_TEMPERATURE_AFTER 5*60
#define CALL_NEXTION_EVERY 15
#define CALL_RELAY_EVERY 50
  // ##########################
  // ####   ACCESS POINT   ####
  // ##########################
#define MAXCLIENTS 5
char* APssid = "CentralHeating";
char* APpass = "123123123";
WiFiServer server1(9001);
WiFiClient clients1[MAXCLIENTS];  // Maximum of MAXCLIENTS clients
//-----------------------------------
//VARIABLES AND DATATYPES
//-----------------------------------
  // ##########################
  // ####TEMPERATURE SENSOR####
  // ##########################
// OneWire is needed for work with DS18B20 temperature sensor
OneWire oneWire(TEMP_SENSOR_PIN);
// Object for temperature sensor
DallasTemperature sensors(&oneWire);
  // ##########################
  // ####     NEXTION      ####
  // ##########################
NexVariable tr[9] = {{0, 28, "tr0"}, {0, 29, "tr1"}, {0, 30, "tr2"}, {0, 31, "tr3"}, {0, 32, "tr4"}, 
                      {0, 33, "tr5"}, {0, 34, "tr6"}, {0, 35, "tr7"}, {0, 36, "tr8"}};
                      
NexVariable p[8] = {{0, 20, "p0"}, {0, 21, "p1"}, {0, 22, "p2"}, {0, 23, "p3"}, 
                    {0, 23, "p4"}, {0, 24, "p5"}, {0, 25, "p6"}, {0, 26, "p7"}};

NexVariable pows[8] = {{0, 37, "pows0"}, {0, 38, "pows1"}, {0, 39, "pows2"}, {0, 40, "pows3"}, 
                    {0, 41, "pows4"}, {0, 42, "pows5"}, {0, 43, "pows6"}, {0, 44, "pows7"}};                    
                    
NexVariable mpows = NexVariable(0, 65, "pows");

char buffer[4] = {0};
uint32_t nbuff = 0;
  // ##########################
  // ####    MANAGEMENT    ####
  // ##########################
// powz contains if the room needs heating
// ps contains set temperature for a room
// trs contains current temperature in a room, if a value is not accesible it is -127 
boolean powz[8] = {false}, mpow = false;
float ps[8] = {0}, trs[9] = {-127, -127, -127, -127, -127, -127, -127, -127, -127};  // load before using
  // ##########################
  // ####      TICKER      ####
  // ##########################
Ticker resetter[9], _nextion, _relay;
  // ##########################
  // ####    LOOP FLAGS    ####
  // ##########################
boolean _nextionflag = true, _relayflag = true;
