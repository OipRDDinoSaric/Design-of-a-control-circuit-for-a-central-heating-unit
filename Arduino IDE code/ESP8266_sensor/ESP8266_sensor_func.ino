
void temperature_setup()
{
  sensors.begin();
  sensors.getDeviceCount() == 0 ? Serial.println("WARNING - No temperature sensor connected!") : Serial.print("");
}

void temperature_loop()
{
  CurrTemp = sensors.getTempCByIndex(0);
  dtostrf(CurrTemp, 4, 1, charCurrTemp);
  sensors.requestTemperatures();
  delay(0);
  if (CurrTemp == -127)
  {
    dbSerial1println("WARNING - No temperature sensor connected!");
  } else
  {
    dbSerial1print("Current temperature is: ");
    dbSerial1println(CurrTemp);
  }
}

void client_setup()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(APssid, APpass);
  dbSerial1println("!--- Connecting To " + WiFi.SSID() + " ---!");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    dbSerial1print(".");
    if (++connection_counter >= 100)
    {
      Serial.println("");
      dbSerial1println("Can't connect to server!");
      Serial.println(String("ERROR - Deep sleep for " + String(ERROR_DEEP_SLEEP_AMOUNT) + " seconds!") + String("Running time: ") + String(micros() / 1e6));
      ESP.deepSleep(ERROR_DEEP_SLEEP_AMOUNT * 1e6);
    }
  }
  dbSerial1println("!-- Client Device Connected --!");
  dbSerial1println("Signal Strenght   : " + String(WiFi.RSSI()) + " dBm");
  dbSerial1print  ("Server IP Address : ");
  dbSerial1println(server);
  dbSerial1print  ("Device IP Address : ");
  dbSerial1println(WiFi.localIP());
  // First Make Sure You Got Disconnected
  client1.stop();
  // If Sucessfully Connected Send Connection Message
  if (!client1.connect(server, 9001))
  {
    turnoff = true;
    error = true;
    dbSerial1println("Can't connect to port 9001");
  }
}

void client_loop()
{
  client1.print(String(DEVICEID) + charCurrTemp + '\n');
  client1.flush();
  turnoff = true;
  dbSerial1print("Message sent! ");
  //    if(client1 && client1.connected())
  //    {
  //      // Wait for server to respond
  //      while(client1.available())
  //      {
  //        String message = client1.readStringUntil('\n');
  //        client1.flush();
  //        if(message == "<OK>")
  //        {
  //          dbSerial1println("Server responded with OK, setting turn off flag!");
  //          turnoff = true;
  //        }
  //      }
  //    }
}

