  // ##########################
  // ####TEMPERATURE SENSOR####
  // ##########################
void temperature_setup()
{
 sensors.begin();
 sensors.getDeviceCount() == 0?Serial.println("WARNING - No temperature sensor connected!"):Serial.print("");
}
void temperature_loop()
{
  sensors.requestTemperatures();
  trs[0] = sensors.getTempCByIndex(0);
  if(trs[0] == -127)
  dbSerial1.println("WARNING - No temperature sensor connected!");
}
  // ##########################
  // ####     NEXTION      ####
  // ##########################
void nextion_setup()
{
  nexInit();
  _nextion.attach(CALL_NEXTION_EVERY, nextion_ticker);
}

void nextion_ticker()
{
  _nextionflag = true;
}

void nextion_loop()
{
  _nextionflag = false;
  // getting set temperatures
  for(int i = 0; i < 8; i++)
  {
    memset(buffer, 0, 4);
    if(p[i].getText(buffer, sizeof(buffer)) != 0)
    {
      ps[i] = (float)atof(buffer);
    }else
    {
      ps[i] = (float)0;
      dbSerialPrintln("WARNING - RESETED ps[" + String(i) + "]\n");
    }
    
  // getting power button value
    nbuff = -1;
    if(pows[i].getValue(&nbuff) != 0)
    {
      powz[i] = (boolean)nbuff;
    }else
    {
      powz[i] = false;
      dbSerialPrintln("WARNING - RESETED powz[" + String(i) + "]\n");
    }
    
  }
  nbuff = -1;
  if(mpows.getValue(&nbuff) != 0)
  {
    mpow = (boolean)nbuff;
  }else
  {
    mpow = false;
    dbSerialPrintln("WARNING - RESETED mpow\n");
  }
  
  temperature_loop();
  
  // Setting current temperature
  for(int i = 0; i<9; i++)
  {
    if(trs[i]==-127)
    {
      strncpy(buffer, "Err\0", 4);
    }else if(trs[i] > -10)
    {
      dtostrf(trs[i],4, 1, buffer);
    }else
    {
      dtostrf(trs[i],3, 1, buffer);
      buffer[3] = '\0';
    }
    tr[i].setText(buffer);
  }
}


  // ##########################
  // ####    MANAGEMENT    ####
  // ##########################

void manage_relay_setup()
{
  pinMode(RELAY_PIN, OUTPUT);
  _relay.attach(CALL_RELAY_EVERY, manage_relay_ticker);
}

void manage_relay_ticker()
{
  _relayflag = true;
}

void manage_relay_loop()
{
  _relayflag = false;
  boolean turnoff = true, turnon = false;
  for(int i; i<9; i++)
  {
    // mpow - master power switch, trs == 127 sensor not connected, ps(set temperature) musr be between 15 and 26
    if(powz[i] && mpow && trs[i] != 127 && ps[i] > 14 && ps[i] < 27)
    {
      if(trs[i] < (ps[i]-2))
      {
        turnon = true;
        break;
      }
      else if(trs[i] < (ps[i]+1))
        turnoff = false;
    }
  }
  if(turnon && digitalRead(RELAY_PIN) == LOW)
  {
    digitalWrite(RELAY_PIN, HIGH);
    dbSerial1.println("Turning relay ON");
  }
  else if(turnoff && digitalRead(RELAY_PIN) == HIGH)
  {
    dbSerial1.println("Turning relay OFF");
    digitalWrite(RELAY_PIN, LOW);
  }
}


  // ##########################
  // ####   ACCESS POINT   ####
  // ##########################

void accesspoint_setup()
{
  // Stop Any Previous WIFI
  WiFi.disconnect();

  // Setting The Wifi Mode
  WiFi.mode(WIFI_AP);
  dbSerial1.println("WIFI Mode : AccessPoint");

  WiFi.softAP(APssid, APpass);
  delay(800);
  // Printing The Server IP Address
  dbSerial1.print("AccessPoint IP : ");
  dbSerial1.println(WiFi.softAPIP());

  server1.begin();
  dbSerial1.println("Server started");
}

void accesspoint_loop()
{
  if(server1.hasClient())
  {
    for(int i = 0; i < MAXCLIENTS; i++)
    {
      if(!clients1[i] || !clients1[i].connected())
      {
        if(clients1[i]) clients1[i].stop();
        clients1[i] = server1.available();
      }
    }
    // If there is no free spots reject incoming client
    WiFiClient rejected = server1.available();
    if(rejected)
    {
      dbSerial1.println("WARNING - Rejected a connection!");
    } else {
      dbSerial1.println("New client");
    }
    rejected.stop();
  }

  for(int i = 0; i < MAXCLIENTS; i++)
  {
    if(clients1[i] && clients1[i].connected())
    {
      while(clients1[i].available()) 
      {
        // Read From Client
        String message = clients1[i].readStringUntil('\n');
        dbSerial1.println("Message from sensor: " + message);
        // Parse message
        int sensorid = message[0] - '0';
        message.remove(0, 1);
        if(sensorid < 9 && sensorid > 0)
        {
          trs[sensorid] = message.toFloat();
          // Resets temperature to -127 if the sensor doesn't update the temperature in 2 minutes (120 seconds)
          resetter[sensorid].detach();
          resetter[sensorid].once(RESET_CURRENT_TEMPERATURE_AFTER, reset_current_temperature, uint32_t(sensorid));
        }else{
          dbSerial1.println("WARNING - Bad sensorID");
        }
        
        // Reply To Client
        clients1[i].print("<OK>\n");
        clients1[i].flush();
        clients1[i].stop();
      }
    }
  }
}

void reset_current_temperature(uint32_t i)
{
  trs[i] = -127;
  dbSerial1.println("WARNING - Resetted temperature " + String(i));
}


