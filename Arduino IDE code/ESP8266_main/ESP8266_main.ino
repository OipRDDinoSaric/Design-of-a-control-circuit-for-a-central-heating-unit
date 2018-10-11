#include "ESP8266_main_func.h"

void setup(void)
{
  nextion_setup();
  dbSerial1.begin(115200);  // NexConfig.h #define dbSerial Serial1, currently disabled
  nexSerial.begin(115200);  // NexConfig.h #define nexSerial Serial
  dbSerial1.println();
  dbSerial1.println("Setting up...");
  temperature_setup();
  manage_relay_setup();
  accesspoint_setup();
  nextion_loop();
}

void loop(void)
{
  accesspoint_loop();
  if(_nextionflag) nextion_loop();
  if(_relayflag) manage_relay_loop();
}

