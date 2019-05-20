#include "uart.h"
#include "main.h"
#include "pwm.h"
#include "Assign.h"
#include <ctype.h>
#include <stdio.h>            /* for printf */ 
#include <string.h>
#include <stdlib.h>



void Initialisation() {   // Au démarrage on doit être dans ce cas-ci 
	Consigne.Vts_M1 = 0;  // Pas de vitesse
	Consigne.Vts_M2 = 0;
	
	Consigne.Flag_Vt = 0; // S'assurer qu'il n'y a aucun flag
	Consigne.Flag_Stop = 0;
}
	


void assign(char UxRx_string[UxRx_length]) {  // Permet d'interpréter les ordres issue de l'UART
	
	if (strncmp(UxRx_string, "Stop", 3) == 0) {
		Consigne.Flag_Stop = 1;  // On est en Stop
	}
	else if(strncmp(UxRx_string, "VtsM", 3) == 0) {
		Consigne.Flag_Stop = 0;  // on doit avancer donc si on était en Stop on ne l'est plus
		Consigne.Flag_Vt = 1;  // On a lu VTSM donc le groupe de charactère suivant sera Vts_M1
	}
		
	assig_Vitesse(); // Peut importe ce qui se passe, on passe par l'assignation de vitesse afin d'être sure d'envoyer quelque chose
		

}

int assig_Vitesse(char UxRx_string[UxRx_length]) {

	if (Consigne.Flag_Stop == 1) {
		Consigne.Vts_M1 = 0;  // Si nous sommes en Stop alors rien ne doit bouger
		Consigne.Vts_M2 = 0;
	}
	else {                 // On est pas en stop donc on peut bouger

		if (Consigne.Flag_Vt == 1) { // Ce qui suit VtsM est Vts_M1
			Consigne.Vts_M1 = atof(UxRx_string); // On transforme l'ASCII en float afin d'avoir une consigne
			Consigne.Flag_Vt = 2;    // Permet d'attendre la valeur Vts_M2
		}
		else if (Consigne.Flag_Vt == 2) { // Ce qui suit Vts_M1 est Vts_M2
			Consigne.Vts_M2 = atof(UxRx_string); // On transforme l'ASCII en float afin d'avoir une consigne
			Consigne.Flag_Vt = 0;   // C'est fini on se place dans l'état de base
		}
	}

}