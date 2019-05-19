#include "uart.h"
#include "main.h"
#include "pwm.h"
#include "Assign.h"
#include <ctype.h>
#include <stdio.h>            /* for printf */ 
#include <string.h>


void transmit(void) {

	if (IEC0bits.U1TXIE == 0) {
		sprintf(str, "Vts_M1:%ld", Consigne.Vts_M1);
		sprintf(str, "Vts_M2:%ld", Consigne.Vts_M2);
		sprintf(str, "WHATEVER_YOU_WANT:%ld", 000000);
	}
	FlagUart.U1Tx = 0;	//envele l'aquitement d'émission
	IEC0bits.U1TXIE = 1; // /Enable Transmisssion Interrupts 1
}