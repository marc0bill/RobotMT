/*
Révision:     	$Rev: $
Auteur:       	$Author: $
Date révision: 	$Date:  $
projet:      	$URL: $
*/

#include "header.h"
#include "i2c.h"



//fonction d'initialisation de la clock
void init_clock() {
    PLLFBD = PLL_M;
    CLKDIVbits.PLLPOST = PLL_N1;    // N1 = 2
    CLKDIVbits.PLLPRE = PLL_N2;     // N2 = 2
    OSCTUN = 0;                     // Tune FRC oscillator, if FRC is used
    RCONbits.SWDTEN = 0;            // Disable WatchDog Timer
    RCON = 0; // aucune erreur ne gener de RESET
// Clock switch to incorporate PLL
    __builtin_write_OSCCONH(FTYPE); // Initiate Clock Switch to
                                    // Primary oscillator (XT, HS, EC) with PLL (NOSC=0b011)
    __builtin_write_OSCCONL(0x01);  // Start clock switching
    while (OSCCONbits.COSC != FTYPE);	// Wait for Clock switch to occur
    while(OSCCONbits.LOCK != 1) {};
}

/****************************************************************************************
*/
void init_port(void)
{	

// configuration des périphériques "remappable"
//	 entrées : (chaque numéro correspond au numéro de RP, 1 pour RP1, 2 pour RP2, ...)
//	RPINR13bits.FLTA2R	=	x;		// PWM2 Fault sur RPx
#ifdef _CARTE_MOTEUR_V1_
	RPINR14bits.QEB1R 	=	25;		// voie B du QEI1 sur RP25
	RPINR14bits.QEA1R 	=	24;		// voie A du QEI1 sur RP24
	RPINR15bits.INDX1R 	=	23;		// Index du QEI1 sur RP23
	RPINR16bits.QEB2R 	=	9;		// voie B du QEI2 sur RP22
	RPINR16bits.QEA2R 	=	22;		// voie A du QEI2 sur RP9
	RPINR17bits.INDX2R 	=	8;		// Index du QEI2 sur RP8
	RPINR18bits.U1RXR 	= 	17 ;  	// assigne RX de UART1 sur RP17
	RPINR19bits.U2RXR 	= 	3 ;  	// assigne RX de UART2 sur RP3
	RPINR26bits.C1RXR	=	25 ;  	// assigne C1RX de ECAN1 sur RP25
	RPOR8bits.RP16R		= 0b00011 ;	// assigne TX de UART1 sur RP16 (00011<=>U1TX)
	RPOR1bits.RP2R		= 0b00101 ;	// assigne TX de UART2 sur RP2 (00101<=>U2TX)
// configure entrée analgique/numérique
    AD1PCFGLbits.PCFG5=1;            // UART2 : utilisation digitale de RP3<=>AN5
    AD1PCFGLbits.PCFG7=1;            // UART1 : utilisation digitale de RP17<=>AN7
#endif
#ifdef _CARTE_MOTEUR_V2_
	RPINR14bits.QEB1R 	=	21;		// voie B du QEI1 sur RP8
	RPINR14bits.QEA1R 	=	8;		// voie A du QEI1 sur RP21
	RPINR15bits.INDX1R 	=	20;		// Index du QEI1 sur RP20
	RPINR16bits.QEB2R 	=	25;		// voie B du QEI2 sur RP25
	RPINR16bits.QEA2R 	=	24;		// voie A du QEI2 sur RP9
	RPINR17bits.INDX2R 	=	9;		// Index du QEI2 sur RP8
	RPINR18bits.U1RXR 	= 	16 ;  	// assigne RX de UART1 sur RP17
	RPINR19bits.U2RXR 	= 	19 ;  	// assigne RX de UART2 sur RP3
	RPOR8bits.RP17R		= 0b00011 ;	// assigne TX de UART1 sur RP17 (00011<=>U1TX)
	RPOR2bits.RP4R		= 0b00101 ;	// assigne TX de UART2 sur RP4 (00101<=>U2TX)
// configure entrée analgique/numérique
	AD1PCFGLbits.PCFG0=0;			// Current Sense 2 : Analog Input
	AD1PCFGLbits.PCFG1=0;			// Current Sense 1 : Analog Input
	AD1PCFGLbits.PCFG4=0;			// Current Sense 3 : Analog Input
	AD1PCFGLbits.PCFG5=0;			// Current Sense 4 : Analog Input
    AD1PCFGLbits.PCFG6=1;			// UART1_RX : utilisation digitale de RP16<=>AN6
    AD1PCFGLbits.PCFG7=1;            // UART1_TX : utilisation digitale de RP17<=>AN7
#endif
#ifdef _CARTE_MOTEUR_V3_
    // configure entrée analgique/numérique
    AD1PCFGLbits.PCFG0=1;		// utilisation digitale de AN0
    AD1PCFGLbits.PCFG1=1;		// utilisation digitale de AN1
    AD1PCFGLbits.PCFG4=1;		// QEA1 : utilisation digitale de AN4
    AD1PCFGLbits.PCFG5=1;		// QEB1 : utilisation digitale de AN5
    AD1PCFGLbits.PCFG6=0;		// Current Sense 2 : Analog Input
    AD1PCFGLbits.PCFG7=0;           // Current Sense 1 : Analog Input
    
    TRISBbits.TRISB2 = 0; // RB2/RP2 en sortie
    TRISBbits.TRISB3 = 0; // RB3/RP3 en sortie
	RPINR14bits.QEB1R	=	3;	// voie B du QEI1 sur RP3
	RPINR14bits.QEA1R 	=	2;	// voie A du QEI1 sur RP2
	RPINR15bits.INDX1R 	=	10;	// Index du QEI1 sur RP10
	RPINR16bits.QEB2R 	=	9;	// voie B du QEI2 sur RP9
	RPINR16bits.QEA2R 	=	8;	// voie A du QEI2 sur RP8
	RPINR17bits.INDX2R 	=	22;	// Index du QEI2 sur RP22
	RPINR18bits.U1RXR 	= 	21;  	// assigne RX de UART1 sur RP21
	RPINR19bits.U2RXR 	= 	23;  	// assigne RX de UART2 sur RP23
	RPOR10bits.RP20R	= 0b00011 ;	// assigne TX de UART1 sur RP20 (00011<=>U1TX)
	RPOR3bits.RP7R		= 0b00101 ;	// assigne TX de UART2 sur RP7 (00101<=>U2TX)


#endif






// configure direction des ports:
	T_Brake12=0;	// TRIS de Brake : sortie 
	T_SENS_M1=0;	// TRIS de SENS_M1 : sortie
	T_SENS_M2=0;	// TRIS de SENS_M2 : sortie
	T_LED1=0;		// TRIS de LED1 : sortie
	T_LED0=0;		// TRIS de LED0 : sortie
	T_START=1;		// TRIS de START : entre
	//switch couleur
//	T_Switch_Couleur=1; // entrée
//	P_Switch_Couleur=1; // pull-up activé
    // initialise les sorties:
	Brake12=0; 		// (PORT de) EN_MOT1 à 0
	SENS_M1=0;		// sens moteur 1: avance (a vérifier)
	SENS_M2=0;		// sens moteur 2: avance (a vérifier)
	LED1=0;
	LED0=0;

#ifdef _CARTE_MOTEUR_V1_
	//switch contact
	T_CapAvG=1;		// direction du port : entrée
	T_CapAvD=1;		// direction du port : entrée
	T_CapArG=1;		// direction du port : entrée
	T_CapArD=1;		// direction du port : entrée
#endif
}


//fonction de configuration de l'interruption
void init_interrupt(void){
	
//	SRbits.IPL =0b000;             // IPL=111 desactive les interruptions ext
	INTCON1bits.NSTDIS=0;          // Autorisation des nested interruptions
	INTCON2bits.ALTIVT=0;          // standard vector table
//    CORCONbits.IPL3=0;             // activer les priorités sur les interruptions
    
	// Interruption Capteur pièce
/*
    IEC1bits.INT1IE=1;              //autorise le départ en int ext1
    RPINR0bits.INT1R=0b01010;       //int1 correspond à la pin RP10

	INTCON2bits.INT1EP=0;           // Interruption sur front montant
	IFS1bits.INT1IF=0;              // mise à zéro du flag interruption
	
	IPC5bits.INT1IP=0b011;
	
	//IPC1=0x4444;                    // priorité 4 de l'interruption externe  
    */
}





/*****************************************************************************
Routine d'interruption capteur
*/

/*
void __attribute__ ((interrupt, no_auto_psv)) _INT1Interrupt(void){
        
        close_pince();
		wait(300);
		up_pince();
		wait(200);
	 
	 	IFS1bits.INT1IF=0;          //raz du flag
}
*/	

