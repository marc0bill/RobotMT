#include "uart.h"
#include "main.h"
#include "pwm.h"
#include "Assign.h"
#include <ctype.h>
#include <stdio.h>            /* for printf */ 
#include <string.h>


void transmit(void) {
    char buffer[16];
	if (IEC0bits.U1TXIE == 0) {
		sprintf(buffer, "Vts_M1:%ld", Consigne.Vts_M1);   //renvoie Vts_M1
		sprintf(buffer, "Vts_M2:%ld", Consigne.Vts_M2);   //renvoie Vts_M2
		sprintf(buffer, "WHATEVER_YOU_WANT:%ld", 000000);
	}
	FlagUart.U1Tx = 0;	//envele l'aquitement d'émission
	IEC0bits.U1TXIE = 1; // /Enable Transmisssion Interrupts 1
}