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

#include "main.h"

long freq=10140600;

struct Gen gen;

uint32_t old_freq  = 0;
uint32_t old_phase = 0;

char txString[] = "RYRYRYRY THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG"; // RYRYRYRY THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG // NSV

/* Functions ------------------------------------------------------------------*/
int main(void)
{

	SystemInit();		//Initializes system
	SPIInit();			//Initializes SPI
	initializeUART();
	initializeTimer();

	SPI_Select_Slave(0x01) ;	//Select The SPI Slave
	SPI_WriteData(0x01);			//Send Jedec

	gen.freq  = freq;
	gen.phase = 0;

	printf("init complete\r\n");

	uint32_t counter = 0;

	while(1)
	{

//		cwTx(freq, txString, 20, &gen);
//		delayMillis(1000);

		pskTx(freq, txString, 'B', 31, &gen);
		delayMillis(2000);

#if 0
		counter++;
		printf("GowinFPGA says hi! Count: %d\r\n", counter);

		if(~SPI_GetToeStatus() && SPI_GetTrdyStatus() == 1)
		{
			SPI_WriteData(0x81);//Send Jedec
		}

		delayMillis(500);

		if(~SPI_GetToeStatus() && SPI_GetTrdyStatus() == 1)
		{
			SPI_WriteData(0x01);//Send Jedec
		}

		delayMillis(500);
#endif
	}

}

extern uint8_t checkGen(struct Gen *gen){
	uint8_t res = 0;
	if(old_freq != gen->freq){
		res = 1;
		send_frequency(&gen->freq);
		old_freq = gen->freq;
	}

	if(old_phase != gen->phase){
		res = 2;
//		printf("old_phase\r\n");
		send_phase(&gen->phase);
		old_phase = gen->phase;
	}

	return res;
}

void send_phase(uint32_t *phase){
//	printf("send_phase\r\n");
    uint32_t pword;

    pword=(((float)(*phase)*11.25)/360)*4096;

    uint8_t buff[2];

    buff[0] = pword       & 0xff;
    buff[1] = pword >>  8 & 0xff;

//    fpga_spi_blink(true);
    if(~SPI_GetToeStatus() && SPI_GetTrdyStatus() == 1)
	{
		SPI_WriteData(0x02);//Send Jedec
	}

    for(uint8_t i=0;i<2;++i){
//    	printf("pword: %d\r\n", buff[i]);
//        digitalWrite(PIN_FPGA_CS, 0);
//        SPI.beginTransaction(SPISettings(1000000, SPI_MSBFIRST, SPI_MODE3));
//        uint8_t fpga_output = SPI.transfer(buff[i]);
//        SPI.endTransaction();
//        digitalWrite(PIN_FPGA_CS, 1);
    	if(~SPI_GetToeStatus() && SPI_GetTrdyStatus() == 1)
		{
			SPI_WriteData(buff[i]);//Send Jedec
		}
    }
}

void send_frequency(uint32_t *freq){
    uint32_t fword;
    uint64_t tmp;
    tmp = (uint64_t)(*freq)*(uint64_t)4294967296;
    fword = tmp / (uint32_t)27000000;

//    printf("fword: %d\r\n", fword);

    uint8_t buff[4];

    buff[0] = fword       & 0xff;
    buff[1] = fword >>  8 & 0xff;
    buff[2] = fword >> 16 & 0xff;
    buff[3] = fword >> 24 & 0xff; // ñòàðøèé, ïåðåäàâàòü ñ íåãî

//    fpga_spi_blink(true);
    if(~SPI_GetToeStatus() && SPI_GetTrdyStatus() == 1)
	{
		SPI_WriteData(0x01); //Send Jedec // 0x01
	}

    for(uint8_t i=0;i<4;++i){
//    	printf("fword: %d\r\n", buff[i]);
//        digitalWrite(PIN_FPGA_CS, 0);
//        SPI.beginTransaction(SPISettings(1000000, SPI_MSBFIRST, SPI_MODE3));
//        uint8_t fpga_output = SPI.transfer(buff[i]);
//        SPI.endTransaction();
//        digitalWrite(PIN_FPGA_CS, 1);
    	if(~SPI_GetToeStatus() && SPI_GetTrdyStatus() == 1)
			{
				SPI_WriteData(buff[i]);//Send Jedec
			}
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
