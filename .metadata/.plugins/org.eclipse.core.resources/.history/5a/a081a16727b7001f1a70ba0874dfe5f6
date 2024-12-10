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
#include <Arduino.h>
#include <AD9833.h>

class HFBEACON
{
  public:
    HFBEACON();
   
   void rsidToggle(boolean rsidEnable);
   void cwTx(long freqCw, char * stringCw, int cwWpm, AD9833*);
   void pskTx(long freqPsk, char * stringPsk, int modePsk, int baudsPsk, AD9833*);
   void rttyTx(long freqRtty, char * stringRtty);
   void hellTx(long freqHell, char * stringHell);
   void wsprTx(long freqWspr, char * callWsprTx, char * locWsprTx, char * powWsprTx);
   void wsprEncode(char * callWsprProc, char * locWsprProc, char * powWsprProc);
   void ddsPower(int powDds, AD9833*);
   byte wsprSymb[162];
   int wsprSymbGen;
			
  private:
   void rsidTx(long freqRsid, int modeRsid, AD9833*);
   void pskIdle(long freqIdle, int baudsIdle, AD9833*);
   void rttyTxByte (long freqRttyTxbyte, char c);
   
   byte parity(unsigned long tempo);
   byte rsidTxEnable;
};

extern HFBEACON Beacon;

#endif