#ifndef NEXCENTRALNO_H_
#define NEXCENTRALNO_H_
void postavinextion(void);
void NexDnevPostUpPushCallback(void *ptr);
void NexDnevPostDnPushCallback(void *ptr);


// Declare a text object [page id:0,component id:2, component name: "textNumber"].
NexText t0 = NexText(0, 1, "t0");
NexText t1 = NexText(0, 2, "t1");
NexText t2 = NexText(0, 3, "t2");
NexText t3 = NexText(0, 4, "t3");
NexText t4 = NexText(0, 5, "t4");
NexText t5 = NexText(0, 6, "t5");
NexText t6 = NexText(0, 7, "t6");
NexText t7 = NexText(0, 8, "t7");
NexText NexKvar = NexText(0, 30, "NexKvar");
 // ide ovako danTjedna,dan,mjesec,vrijeme
NexText nexdanTjedna = NexText(0, 9, "nexdanTjedna");
NexText nexdan = NexText(0, 11, "nexdan");
NexText nexmjesec = NexText(0, 12, "nexmjesec");
NexText nexvrijeme = NexText(0, 13, "nexvrijeme");
NexTimer NexTimerKvar = NexTimer(0, 29, "NexTimerKvar");
NexButton NexDnevPostDn = NexButton(1, 11, "NexDnevPostDn");
NexButton NexDnevPostUp = NexButton(1, 10, "NexDnevPostUp");
NexText NexDnevPost = NexText(1, 12, "NexDnevPost");

NexTouch *nex_listen_list[] =
{
  &NexDnevPostDn,
  &NexDnevPostUp,
  NULL
};
#endif