/*
Club Robot - Polytech Marseille

Fonctions liées à l'utilisation des timer


Révision:     	$Rev: $
Auteur:       	$Author: $
Date révision: 	$Date:  $
projet:      	$URL: $

*/
#include "header.h"
#include "timer.h"
#include "uart.h"
//#include "move.h"
#include "uartTx.h"

unsigned long tempsjeux=0; // temps joué en ms

void init_timer1()              // configure timer1
{
	T1CONbits.TCKPS=0b00;
// Timer1 Input Clock Prescale Select bits
// 11 = 1:256
// 10 = 1:64
// 01 = 1:8
// 00 = 1:1

	T1CONbits.TCS=0;
// Timer1 Clock Source Select bit
// 1 = External clock from pin T1CK (on the rising edge)
// 0 = Internal clock (FCY)

	T1CONbits.TSYNC=0;
// Timer1 External Clock Input Synchronization Select bit
// When TCS = 1:
// 1 = Synchronize external clock input
// 0 = Do not synchronize external clock input
// When TCS = 0:This bit is ignored.

	T1CONbits.TGATE=0;
// Timer1 Gated Time Accumulation Enable bit
// When T1CS = 1: This bit is ignored.
// When T1CS = 0: 1 = Gated time accumulation enabled
//               0 = Gated time accumulation disabled

	T1CONbits.TSIDL=0;
// Stop in Idle Mode bit
// 1 = Discontinue module operation when device enters Idle mode
// 0 = Continue module operation in Idle mode*/

	T1CONbits.TON=1;
// Timer1 On bit
// 1 = Starts 16-bit Timer1
// 0 = Stops 16-bit Timer1
	
	PR1=2000*COEFF_PR1; //Frequence Timer1 : FCY/PR1=1kHz => 100µs
	
	IEC0bits.T1IE=1;	// autorisation des interruption du Timer 1
}

void wait_timer1(unsigned long attente)
{
	unsigned long tempsjeux_last=0;
	tempsjeux_last=tempsjeux;
	while(tempsjeux<tempsjeux_last+attente);
}

/********************************************************************************
interruption timer 1
*/
void __attribute__ ((interrupt, no_auto_psv)) _T1Interrupt(void)
{
	IFS0bits.T1IF=0;	// acquittement
	static unsigned tps_100us=0;
	static unsigned tps_1ms=0;
	static unsigned tps_10ms=0;
	static unsigned tps_100ms=0;
	static unsigned long tps_1s=0;
	static char FlagWaitUart2=0;
	static unsigned T_U1Tx=0;
	tps_100us++;

	if(tps_100us>9){
		tempsjeux++;
		tps_1ms++;
		tps_100us=0;
		if(tps_1ms>9){ //1ms*10
			tps_1ms=0;
			tps_10ms++;


	if(FlagUart.U2Tx==0 && FlagUart.U2Tx_wait==0){
		IEC1bits.U2TXIE	= 1;// Enable Transmisssion Interrupts 2
	}
	if(FlagWaitUart2!=0){
		FlagUart.U2Tx_wait=0;
		FlagWaitUart2 = 0;
	}
	if(FlagUart.U2Tx_wait!=0){
		FlagWaitUart2 = 1;
	}

	if(tempsjeux-T_U1Tx >= T_U1Tx_wait){
		FlagUart.U1Tx=1;
		T_U1Tx=tempsjeux;
	}

			if(tps_10ms>9){ //1ms*100
				tps_10ms=0;
				tps_100ms++;
//uxtx_pstvts_char(tempsjeux);
				if(tps_100ms>9){
					tps_100ms=0;
					tps_1s++;
					L_LED1=!L_LED1;
				}
			}
		}
	}
	if(tempsjeux>1000000000)
		tempsjeux=0;
/*
	if(tempsjeux>tempspartie)
	{
		while(1)
		{
			P1DC1=0;
			P1DC2=0;
		}
	}
*/
}
