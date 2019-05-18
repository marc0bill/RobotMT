#include "uart.h"
#include "main.h"
#include "pwm.h"
#include "Assign.h"
#include <ctype.h>
#include <stdio.h>            /* for printf */ 
#include <string.h>
struct Vitesse Consigne



void assign(char UxRx_string[UxRx_length]) {
	
	if (strncmp(UxRx_string, "Stop", 3) == 0) then
		Consigne.Vts_M1 = 0;
		Consigne.Vts_M2 = 0;
	elsif (strncmp(UxRx_string, "VtsM", 3) == 0) then 
		Consigne.Flag_Vt = 1;
	assig_Vitesse();
		

}

int assig_Vitesse(char UxRx_string[UxRx_length]) {

	switch (Consigne.Flag)
	{
		case 1:
			Consigne.Vts_M1 = atof(UxRx_string);
			Consigne.Flag_Vt = 2;
			break;
		case 2;
			Consigne.Vts_M2 = atof(UxRx_string);
			Consigne.Flag_Vt = 0;
			break;

	}
}