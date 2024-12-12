#ifndef MAIN_H
#define MAIN_H

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)

/* Includes ------------------------------------------------------------------*/
#include "gw1ns4c.h"
#include <stdio.h>
#include <hfbeacon.h>

#if 0
struct Gen{
	uint32_t freq;
	uint32_t phase;
};
#endif

/* Includes ------------------------------------------------------------------*/
void SPIInit(void);
void initializeUART();
void initializeTimer();
void delayMillis(uint32_t ms);
extern uint8_t checkGen(struct Gen*);
void send_frequency(uint32_t *freq);

#endif /* MAIN_H */
