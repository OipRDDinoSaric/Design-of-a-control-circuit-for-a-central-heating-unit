#include "CentralniVar.h"
#include "NexCentralno.h"

//-------------------------------------NEXTION---------------------------------------
char buffer[10] = {0};

void NexDnevPostUpPushCallback(void *ptr){
    if(postavljena[0]<30) postavljena[0]++;
    memset(buffer, 0, sizeof(buffer)); // clear buffer
    utoa(postavljena[0], buffer, 10);
    NexDnevPost.setText(buffer);
}

void NexDnevPostDnPushCallback(void *ptr){
  if(postavljena[0]>15)postavljena[0]--;
  memset(buffer, 0, sizeof(buffer)); // clear buffer
  utoa(postavljena[0], buffer, 10);
  NexDnevPost.setText(buffer);
}
void postavinextion(void){
  //nije kvar, ne vidi se objekt NexKvar
  memset(buffer, 0, sizeof(buffer)); // clear buffer
  utoa((uint16_t)0, buffer, 10);
  NexKvar.setBco(buffer);
  
  //nije kvar, resetiraj timer
  NexTimerKvar.disable();
  NexTimerKvar.enable();
  
  //MOZE PRIKAZATI -99.9 -> 999.9
  memset(buffer, 0, sizeof(buffer)); // clear buffer
  dtostrf(trenutna[0], 5, 1, buffer);
  t0.setText(buffer);
  
  memset(buffer, 0, sizeof(buffer)); // clear buffer
  dtostrf(trenutna[1], 5, 1, buffer);
  t1.setText(buffer);
  
  memset(buffer, 0, sizeof(buffer)); // clear buffer
  dtostrf(trenutna[2], 5, 1, buffer);
  t2.setText(buffer);
  
  memset(buffer, 0, sizeof(buffer)); // clear buffer
  dtostrf(trenutna[3], 5, 1, buffer);
  t3.setText(buffer);
  
  memset(buffer, 0, sizeof(buffer)); // clear buffer
  dtostrf(trenutna[4], 5, 1, buffer);
  t4.setText(buffer);
  
  memset(buffer, 0, sizeof(buffer)); // clear buffer
  dtostrf(trenutna[5], 5, 1, buffer);
  t5.setText(buffer);
  
  memset(buffer, 0, sizeof(buffer)); // clear buffer
  dtostrf(trenutna[6], 5, 1, buffer);
  t6.setText(buffer);
  
  memset(buffer, 0, sizeof(buffer)); // clear buffer
  dtostrf(trenutna[7], 5, 1, buffer);
  //strcpy(buffer, NexTemp.c_str());
  t7.setText(buffer);
  
  //memset(buffer, 0, sizeof(buffer)); // clear buffer
  //dtostrf(trenutna[8], 4, 1, buffer);
  //t8.setText(buffer);
  
  // ide ovako danTjedna,dan,mjesec,vrijeme
  memset(buffer, 0, sizeof(buffer)); // clear buffer
  strcpy(buffer,danTjedna);
  nexdanTjedna.setText(buffer);

  memset(buffer, 0, sizeof(buffer)); // clear buffer
  strcpy(buffer,dan);
  nexdan.setText(buffer);

  memset(buffer, 0, sizeof(buffer)); // clear buffer
  strcpy(buffer,mjesec);
  nexmjesec.setText(buffer);

  memset(buffer, 0, sizeof(buffer)); // clear buffer
  strcpy(buffer,vrijeme);
  nexvrijeme.setText(buffer);
  
}
