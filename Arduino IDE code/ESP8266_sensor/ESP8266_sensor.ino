#include "ESP8266_sensor_func.h"

void setup(void)
{
  Serial.begin(115200);
  dbSerial1println("");
  temperature_setup();
  client_setup();
  dbSerial1println("");
}

void loop(void)
{
  
  if(CurrTemp > -30 && CurrTemp < 50)
  {
    client_loop();
  } else if(++temp_counter > 5)
  {
    dbSerial1println("Can't get temperature in 5 tries, setting turn off flag");
    turnoff = true;
    error = true;
  }else{
    temperature_loop();
  }
  
  if(turnoff)
  {
    Serial.println("");
    if(error)
    {
      
      Serial.println(String("ERROR - Deep sleep for " + String(ERROR_DEEP_SLEEP_AMOUNT) + " seconds!") + String("Running time: ") + String(micros() / 1e6));
      ESP.deepSleep(ERROR_DEEP_SLEEP_AMOUNT * 1e6);
    }else
    {
      Serial.println(String("Deep sleep for " + String(DEEP_SLEEP_AMOUNT) + " seconds!") + String("Running time: ") + String(micros() / 1e6));
      ESP.deepSleep(DEEP_SLEEP_AMOUNT * 1e6);
    }
  }
}

