
/*
 * *****************************************************************************************
 *
 * 		Copyright (C) 2014-2021 Gowin Semiconductor Technology Co.,Ltd.
 *
 * @file			main.c
 * @author		Embedded Development Team
 * @version		V1.x.x
 * @date			2021-01-01 09:00:00
 * @brief			Main program body.
 ******************************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "gw1ns4c.h"
#include <stdio.h>

/* Includes ------------------------------------------------------------------*/
void SPIInit(void);
void initializeUART();
void initializeTimer();
void delayMillis(uint32_t ms);

/* Functions ------------------------------------------------------------------*/
int main(void)
{
  SystemInit();		//Initializes system
  SPIInit();			//Initializes SPI
  initializeUART();
  initializeTimer();

  SPI_Select_Slave(0x01) ;	//Select The SPI Slave
  SPI_WriteData(0x01);			//Send Jedec

  printf("init complete\r\n");

  uint32_t counter = 0;

  while(1)
  {

      counter++;
	  printf("GowinFPGA says hi! Count: %d\r\n", counter);
#if 1
	  if(~SPI_GetToeStatus() && SPI_GetTrdyStatus() == 1)
	  {
	      SPI_WriteData(0x81);//Send Jedec
	  }
#endif

	  delayMillis(500);

#if 1
	  if(~SPI_GetRoeStatus() && SPI_GetRrdyStatus() == 1)
	  {
//	      UART_SendChar(UART0,SPI_ReadData());
		  char value = SPI_ReadData();
		  printf("value: %c\r\n", value);
	  }
#endif
	  delayMillis(500);
#if 1
	  if(~SPI_GetToeStatus() && SPI_GetTrdyStatus() == 1)
	  {
		  SPI_WriteData(0x01);//Send Jedec
	  }
#endif
	  delayMillis(500);
  }
}

//Initializes SPI
void SPIInit(void)
{
	SPI_InitTypeDef init_spi;

  init_spi.CLKSEL= CLKSEL_CLK_DIV_6;		//80MHZ / 8
  init_spi.DIRECTION = DISABLE;					//MSB First
  init_spi.PHASE =DISABLE;							//ENABLE;//posedge
  init_spi.POLARITY =DISABLE;						//polarity 0

  SPI_Init(&init_spi);
}

//Initializes UART0
  void initializeUART()
  {
  	UART_InitTypeDef uartInitStruct;
  	//Enable transmission
  	uartInitStruct.UART_Mode.UARTMode_Tx = ENABLE;
  	//Disable reception
  	uartInitStruct.UART_Mode.UARTMode_Rx = DISABLE;
  	//9600 baud rate typical of Arduinos
  	uartInitStruct.UART_BaudRate = 9600;
  	//Initialize UART0 using the struct configs
  	UART_Init(UART0, &uartInitStruct);
  }

  void initializeTimer() {
    	TIMER_InitTypeDef timerInitStruct;

    	timerInitStruct.Reload = 0;

    	//Disable interrupt requests from timer for now
    	timerInitStruct.TIMER_Int = DISABLE;

    	//Disable timer enabling/clocking from external pins (GPIO)
    	timerInitStruct.TIMER_Exti = TIMER_DISABLE;

    	TIMER_Init(TIMER0, &timerInitStruct);
    	TIMER_StopTimer(TIMER0);
    }

    #define CYCLES_PER_MILLISEC (SystemCoreClock / 1000)
    void delayMillis(uint32_t ms) {
    	TIMER_StopTimer(TIMER0);
    	TIMER_SetValue(TIMER0, 0); //Reset timer just in case it was modified elsewhere
    	TIMER_EnableIRQ(TIMER0);

    	uint32_t reloadVal = CYCLES_PER_MILLISEC * ms;
    	//Timer interrupt will trigger when it reaches the reload value
    	TIMER_SetReload(TIMER0, reloadVal);

    	TIMER_StartTimer(TIMER0);
    	//Block execution until timer wastes the calculated amount of cycles
    	while (TIMER_GetIRQStatus(TIMER0) != SET);

    	TIMER_StopTimer(TIMER0);
    	TIMER_ClearIRQ(TIMER0);
    	TIMER_SetValue(TIMER0, 0);
    }
