#include <OneWire.h>
#include <DallasTemperature.h>
#include <NTPtimeESP.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Nextion.h>
#include <SoftwareSerial.h>
#include <Ticker.h>

#include "NexCentralno.h"
#include "CentralniVar.h"

uint8_t postavljena[N_SENZORA]; //temperatura koju smo postavili preko nextiona ili moba
float trenutna[N_SENZORA]; //temperatura koju smo ocitali sa senzora
boolean grijanje[N_SENZORA]; // flag koji je true ako hocemo grijanje u toj sobi
uint8_t ZastavaVrijeme=0; // zastavica kojom gledamo da se ne zaustavimo negdje bespotrebno
char vrijeme[10], danTjedna[10], dan[10], mjesec[10];

uint16_t Loop_v=0, Loop_t_init=0;

unsigned long time_prev=0, blynk_prev=0, temp0_prev=0, net_prev=0, net_delay=30*1000*1000, reconn_delay=10*1000*1000, time_delay=50*1000*1000, temp0_delay=60*1000*1000, blynk_delay=8*1000*1000;
boolean reconn_active=false;

char auth[] = "54bc4eb2bfc4407796667ee142ec4bd0";
BlynkTimer timer;

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

WiFiServer server(80);

//primam tocno vrijeme s neta
NTPtime NTPhr("time.google.com");

char *ssid      = "Connectify-jkl";               // Set you WiFi SSID
char *password  = "123123123";               // Set you WiFi password
char *espssid   = "CentralnoGrijanje";
char *esppass   = "ezpzlmnsqz123";
IPAddress ip(192,168,69,4);
IPAddress gateway(192,168,69,1);
IPAddress subnet(255,255,255,0);

strDateTime dateTime;

//Ticker sta_tick, wifi_recon, tick_tren0, tick_blynk, tick_vrijeme;


//---------------------DEBUG--------------
void brojponavljanja(void){
   if(Loop_t_init==0){
      Loop_t_init=micros();
  } else {
        if(micros()<(Loop_t_init+60000000)){
           Loop_v++;
        } else {
          Serial.println(Loop_v);
       }
  }
}

//---------------------SETUP------------
void setup(void)
{
  // start serial port
  nexInit();
  Serial.begin(9600);
  nexSerial.begin(115200);
  NexDnevPostDn.attachPush(NexDnevPostDnPushCallback);
  NexDnevPostUp.attachPush(NexDnevPostUpPushCallback);
  //inicijalizacija pina koji upravlja relejem
  pinMode(RELEJ_PIN, OUTPUT);
  digitalWrite(RELEJ_PIN,LOW);
  pinMode(D5, INPUT);
  // Start up the library
  sensors.begin();
  for(int i=0; i<N_SENZORA;i++){
    postavljena[i]=20;
    trenutna[i]=99.0;
    grijanje[i]=false;
  }
  grijanje[0]=true;
  WiFi.mode(WIFI_AP/*_STA*/);
  WiFi.softAPConfig(ip,gateway,subnet);
  WiFi.softAP(espssid, esppass);
  //Blynk.begin(auth, ssid, password);
  Blynk.config(auth);
  timer.setInterval(20000L, myTimerEvent); //svakih 20 sekundi udi u funkciju myTimerEvent
  server.begin();

  //tickeri
  /*
  tick_tren0.attach(60, tren0); 
  tick_blynk.attach(8, blynkfunc);
  tick_vrijeme.attach(50, TrenutnoT);
  */
  //enableWiFi();
}
//------------------LOOP----------------------------
void loop(void){ 
  nexLoop(nex_listen_list);
  
  //postavinextion();
  dohvati_temp_senzora();
  upravljaj_relejem();

  //podatci_s_neta();
  svi_tickeri();
}
//----------------------------------------------------
//unsigned long time_prev=0, blynk_prev=0, temp0_prev=0, net_prev=0, net_delay=30*1000*1000, reconn_delay=10*1000*1000, time_delay=50*1000*1000, temp0_delay=60*1000*1000, blynk_delay=8*1000*1000;
void svi_tickeri(void){
    unsigned long run_time=micros();
    if(time_prev>run_time || blynk_prev>run_time || temp0_prev>run_time){
      time_prev=blynk_prev=temp0_prev=run_time;
    }

    if(run_time>=time_prev + time_delay || time_prev==0){
      time_prev=run_time;
      TrenutnoT();
    }

    if(run_time>=blynk_prev + blynk_delay){
      blynk_prev=run_time;
      blynkfunc();
    }

    if(run_time>=temp0_prev + temp0_delay || temp0_prev==0){
      temp0_prev=run_time;
      tren0();
    }

    if(WiFi.status() != WL_CONNECTED){
      if((run_time>=net_prev+net_delay+reconn_delay) || net_prev==0){
            Serial.println("Pokusajem se spojit");
            WiFi.mode(WIFI_AP_STA);
            WiFi.begin(ssid, password);
            net_prev=run_time;
            reconn_active=true;
        }
      if(run_time>=net_prev+reconn_delay && reconn_active){
            WiFi.mode(WIFI_AP);
            Serial.println("Nije se spojio");
            reconn_active=false;
      }
    }
}

void tren0(void){
  sensors.requestTemperatures();
  trenutna[0]=sensors.getTempCByIndex(0);
}

void blynkfunc(void){ 
    if(WiFi.status() == WL_CONNECTED){
        if(Blynk.connected()){
            Blynk.run();
            timer.run();    
        }else if(!Blynk.connected()){
            Blynk.connect();
         }
    }/* else if(!wifi_recon.active()){
        wifi_recon.attach(30, enableWiFi);
        Serial.println("Pokusajem se spojit za 30 sec");
     //ako nema neta pokusaj se ponovno spojiti nakon 30 sec
     //ne mozes koristiti AP i STA ako cijelo vrijeme trazis router
     //jer će esp stalno mjenjati kanale dok trazi router.
     //vise u esp8266 programming guide
    }*/
}

//------------------------SVE STO TREBA INTERNET-----------------------------

void podatci_s_neta(void){
    if(WiFi.status() == WL_CONNECTED){ 

        TrenutnoT();
        if(Blynk.connected()){
            Blynk.run();
            timer.run();    
        }else if(!Blynk.connected()){
            Blynk.connect();
         }
    }/*else if(!wifi_recon.active()){
        wifi_recon.attach(30, enableWiFi);
        Serial.println("Pokusajem se spojit za 30 sec");
     //ako nema neta pokusaj se ponovno spojiti nakon 30 sec
     //ne mozes koristiti AP i STA ako cijelo vrijeme trazis router
     //jer će esp stalno mjenjati kanale dok trazi router.
     //vise u esp8266 programming guide
    }*/
}

//------------------------PONOVNO SPAJANJE NA WIFI------------------------------------------

void enableWiFi(){
    Serial.println("Pokusajem se spojit");
    WiFi.mode(WIFI_AP_STA);
    WiFi.begin(ssid, password);
}

void staCheck(){
  //ako se u 10 sec nije spojio onda prestani traziti
  if(WiFi.status() != WL_CONNECTED){
    WiFi.mode(WIFI_AP);
    Serial.println("Nije se spojio");
  } else 
     Serial.println("Spojio se");
}
//-------------------------TRENUTNO VRIJEME S NETA-----------------------------
void TrenutnoT() {
  if(WiFi.status() == WL_CONNECTED){ 
  dateTime = NTPhr.getNTPtime(1.0, 1);  // +1GMT with summer time.

  if(dateTime.valid){
    stavivrijemeuchar();
    //Serial.println(trenutno_vrijeme);
    ZastavaVrijeme=0;
  } else if(ZastavaVrijeme<3){
    ZastavaVrijeme++;
    delay(100);  // adding this delay make the function work 100% reliable.
    TrenutnoT();
  } else {
      ZastavaVrijeme=0;
    }
  }
}
//-----------------------------------------------------------------------
void upravljaj_relejem(void){
  boolean gasi=1, pali=0, promjena=0;
  uint8_t i;
  for(i=0;i<(N_SENZORA-1);i++){
    if(grijanje[i]){
     if(trenutna[i]<(postavljena[i]-2)){
        pali=1;
      }
      else if(trenutna[i]<(postavljena[i]+1)){
        gasi=0;    
      }
    }
  }
    if(pali){
          digitalWrite(RELEJ_PIN,HIGH);
    } else 
        if(gasi){
          digitalWrite(RELEJ_PIN,LOW);
    }
}
//-----------------------AKO JE SPOJEN SENZOR PROČITAJ NJEGOVU TEMP---------------
void dohvati_temp_senzora(void){
   uint8_t espID; 
  WiFiClient client = server.available();
  // wait for a client (web browser) to connect
  if (client)
  {
    Serial.println("Client connected");
    while (client.connected())
    {
      // read line by line what the client (web browser) is requesting
      if (client.available())
      {
        String req = client.readStringUntil('\r');
        espID = req.toFloat();
        req = client.readStringUntil('\r');
        trenutna[espID]=req.toFloat();
        Serial.print("TEMP= ");
        Serial.println(trenutna[espID]);
        client.flush();
        delay(1); // give the web browser time to receive the data
        client.stop(); // close the connection
      }
    }
    Serial.println("Client disonnected");
  }
}

//UDP-8 => ISO 1 byte-2
// č = 232 Č = 200
// ć = 230 Ć = 198
// ž = 190 Ž = 172
// š = 185 Š = 169
// đ = 240 Đ = 208
//--------------------------------PRIPREMI VRIJEME ZA NEXTION----------------------
void stavivrijemeuchar(void){ // ide ovako danTjedna,dan,mjesec,vrijeme
  char temp[10]="\0";
   switch(dateTime.dayofWeek){
      case 1: strcpy(danTjedna,"Ned, \0"); break;
      case 2: strcpy(danTjedna,"Pon, \0"); break;
      case 3: strcpy(danTjedna,"Uto, \0"); break;
      case 4: strcpy(danTjedna,"Sri, \0"); break;
      case 5: strcpy(danTjedna,"Cet, \0"); danTjedna[0]=200; break;
      case 6: strcpy(danTjedna,"Pet, \0"); break;
      case 7: strcpy(danTjedna,"Sub, \0"); break;
    }                                         //u char array danTjedna je npr. "Ned, " 
    itoa((int)dateTime.day,dan,10);
    strcat(dan,". \0"); //u char array dan je npr. "31. " 
    switch(dateTime.month){
      case 1:  strcpy(mjesec,"Sijecnja\0"); mjesec[4]=232;break;
      case 2:  strcpy(mjesec,"Veljace\0"); mjesec[5]=232; break;
      case 3:  strcpy(mjesec,"Ozujka\0"); mjesec[1]=190; break;
      case 4:  strcpy(mjesec,"Travnja\0"); break;
      case 5:  strcpy(mjesec,"Svibnja\0"); break;
      case 6:  strcpy(mjesec,"Lipnja\0"); break;
      case 7:  strcpy(mjesec,"Srpnja\0"); break;
      case 8:  strcpy(mjesec,"Kolovoza\0"); break;
      case 9:  strcpy(mjesec,"Rujna\0"); break;
      case 10:  strcpy(mjesec,"Listapada\0"); break;
      case 11:  strcpy(mjesec,"Studenog\0"); break;
      case 12:  strcpy(mjesec,"Prosinca\0"); break; //u char array mjesec je npr. "Veljača" 
    }

  itoa((int)dateTime.hour, vrijeme, 10);
  if(dateTime.hour<10){
    vrijeme[1]=vrijeme[0];
    vrijeme[0]='0';
    vrijeme[2]='\0';
    }
  strcat(vrijeme, ":\0");
 
  itoa((int)dateTime.minute, temp, 10);
  if(dateTime.minute<10){
    temp[1]=temp[0];
    temp[0]='0';
    temp[2]='\0';
    }
  strcat(vrijeme, temp); //u char array vrijeme je npr. "10:54"
}
//-----------------BLYNK---------------
void myTimerEvent()
{
  Blynk.virtualWrite(V0, grijanje[0]);
  Blynk.virtualWrite(V1, grijanje[1]);
  Blynk.virtualWrite(V2, grijanje[2]);
  Blynk.virtualWrite(V3, grijanje[3]);
  Blynk.virtualWrite(V4, grijanje[4]);
  Blynk.virtualWrite(V5, grijanje[5]);
  Blynk.virtualWrite(V6, grijanje[6]);
  Blynk.virtualWrite(V7, grijanje[7]);
  Blynk.virtualWrite(V10, postavljena[0]);
  Blynk.virtualWrite(V15, postavljena[5]);
}


// This function is called when there is a Widget
// which is requesting data from Virtual Pin (5)
BLYNK_READ(V0){   Blynk.virtualWrite(V0, grijanje[0]);}
BLYNK_READ(V1){   Blynk.virtualWrite(V1, grijanje[1]);}
BLYNK_READ(V2){   Blynk.virtualWrite(V2, grijanje[2]);}
BLYNK_READ(V3){   Blynk.virtualWrite(V3, grijanje[3]);}
BLYNK_READ(V4){   Blynk.virtualWrite(V4, grijanje[4]);}
BLYNK_READ(V5){   Blynk.virtualWrite(V5, grijanje[5]);}
BLYNK_READ(V6){   Blynk.virtualWrite(V6, grijanje[6]);}
BLYNK_READ(V7){   Blynk.virtualWrite(V7, grijanje[7]);}
BLYNK_READ(V10){   Blynk.virtualWrite(V10, postavljena[0]);}
BLYNK_READ(V15){   Blynk.virtualWrite(V15, postavljena[5]);}

// This function will be called every time Slider Widget
// in Blynk app writes values to the Virtual Pin
BLYNK_WRITE(V0){ grijanje[0] = param.asInt();}
BLYNK_WRITE(V1){ grijanje[1] = param.asInt();}
BLYNK_WRITE(V2){ grijanje[2] = param.asInt();}
BLYNK_WRITE(V3){ grijanje[3] = param.asInt();}
BLYNK_WRITE(V4){ grijanje[4] = param.asInt();}
BLYNK_WRITE(V5){ grijanje[5] = param.asInt();}
BLYNK_WRITE(V6){ grijanje[6] = param.asInt();}
BLYNK_WRITE(V7){ grijanje[7] = param.asInt();}
BLYNK_WRITE(V10){ postavljena[0] = param.asInt();}
BLYNK_WRITE(V15){ postavljena[5] = param.asInt();}

BLYNK_APP_CONNECTED() {         // Called when Smartphone App is opened
  Serial.println("App Connected.");
  myTimerEvent(); //updateaj zadnje vrijednosti na blynk serveru 
}

