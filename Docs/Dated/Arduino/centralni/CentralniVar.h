#ifndef CENTRALNIVAR_H_
#define CENTRALNIVAR_H_

//gdje se nalazi ESP?
//const uint8_t SENZOR_ID = 0; Dnevni Boravak (centralni)

// Senzor je spojen na D5 od esp-a
#define ONE_WIRE_BUS 14

#define MAX_TEMP 45
#define MIN_TEMP -30

//relej je spojen na D8 tj. 15
#define RELEJ_PIN 15

#define N_SENZORA 9

extern uint8_t postavljena[N_SENZORA]; //temperatura koju smo postavili preko nextiona ili moba
extern float trenutna[N_SENZORA]; //temperatura koju smo ocitali sa senzora
extern boolean grijanje[N_SENZORA]; // flag koji je true ako hocemo grijanje u toj sobi
extern uint8_t ZastavaVrijeme; // zastavica kojom gledamo da se ne zaustavimo negdje bespotrebno
extern char vrijeme[10], danTjedna[10], dan[10], mjesec[10];

extern uint16_t Loop_v, Loop_t_init;

extern unsigned long time_prev, blynk_prev, temp0_prev, net_prev, net_delay, reconn_delay, time_delay, temp0_delay, blynk_delay;
extern boolean reconn_active;

extern char auth[];

extern char *ssid, *espssid, *password, *esppass;

extern strDateTime dateTime;

//D2 je RX, a D1 je TX
//SoftwareSerial SoftSerial(4,5);
extern SoftwareSerial nexSerial;

extern NTPtime NTPhr;

void TrenutnoT();
void dohvati_temp_senzora(void);
void upisitrenutnutemp(void);
void myTimerEvent();
void upravljaj_relejem(void);
void podatci_s_neta(void);
#endif
