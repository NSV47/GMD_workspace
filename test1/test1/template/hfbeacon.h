/********************************************************************************************
 * HF multimodes beacon Arduino library
 * Created 04/10/2014
 * Christophe Caiveau f4goj@free.fr 
 * 
 * Use this library freely
 *
 * Instance :
 *
 * Functions :
 *
 *******************************************************************************************/
 
 
#ifndef HFBEACON_H
#define HFBEACON_H

#include <stdbool.h>
#include "main.h"

#if 0
struct Gen{
	uint32_t freq;
	uint32_t phase;
};
#endif

void rsidToggle(bool rsidEnable);
void cwTx(long freqCw, char * stringCw, int cwWpm, struct Gen*); // , AD9833*
void pskTx(long freqPsk, char * stringPsk, int modePsk, int baudsPsk, struct Gen*); // , AD9833*
void rttyTx(long freqRtty, char * stringRtty);
void hellTx(long freqHell, char * stringHell);
void wsprTx(long freqWspr, char * callWsprTx, char * locWsprTx, char * powWsprTx);
void wsprEncode(char * callWsprProc, char * locWsprProc, char * powWsprProc);
void ddsPower(int powDds, struct Gen*); // , AD9833*
uint8_t wsprSymb[162];
int wsprSymbGen;

void rsidTx(long freqRsid, int modeRsid, struct Gen*); // , AD9833*
void pskIdle(long freqIdle, int baudsIdle, struct Gen*); // , AD9833*
void rttyTxByte (long freqRttyTxbyte, char c);

uint8_t parity(unsigned long tempo);
uint8_t rsidTxEnable;

//extern HFBEACON Beacon;

#endif