/*
Club Robot - Polytech Marseille

Fonctions du module QEI

Révision:     	$Rev: $
Auteur:       	$Author: $
Date révision: 	$Date:  $
projet:      	$URL: $

*/


#include "header.h"	// processor, constantes,

extern long RoueD, RoueR;
/***************************************************************************************
Initialisation des modules QEI

entrées : -
sortie : -   
*/
void init_QEI()			// configure Encodeurs
{
	//QEI1 Control Register
	QEI1CONbits.CNTERR = 1;
	QEI1CONbits.QEISIDL = 0;
	//QEI1CONbits.INDEX = X; (Read Only)
	//QEI1CONbits.UPDN = X;
	QEI1CONbits.QEIM = 0b111;	// mettre 111 si encoder sans index?
	QEI1CONbits.SWPAB = 0;
	QEI1CONbits.PCDOUT = 0;
	QEI1CONbits.TQGATE = 0;
	//QEI1CONbits.TQCKPS<1:0> = XX;
	QEI1CONbits.POSRES = 0;			//Index pulse does not reset position counter
	QEI1CONbits.TQCS = 0;
	QEI1CONbits.UPDN_SRC = 0;
						
	//QEI2 Control Register
	QEI2CONbits.CNTERR = 1;
	QEI2CONbits.QEISIDL = 0;
	//QEI2CONbits.INDEX = 0; (Read Only)
	//QEI2CONbits.UPDN = X;
	QEI2CONbits.QEIM = 0b111;
	QEI2CONbits.SWPAB = 0;
	QEI2CONbits.PCDOUT = 0;
	QEI2CONbits.TQGATE = 0;
	//QEI2CONbits.TQCKPS<1:0> = XX;
	QEI2CONbits.POSRES = 0; 		//Index pulse does not reset position counter
	QEI2CONbits.TQCS = 0;
	QEI2CONbits.UPDN_SRC = 0;
						

	DFLT1CON = 0x0000 ; /* DFLT Control Register*/
	DFLT2CON = 0x0000 ; /* DFLT Control Register*/
	//MAX1CNT=	4*	;	// pour remettre à zero à chaque tour, il faut mettre 4*N (N= resolution de l'encodeur)
	//MAX2CNT=	4*	;	// (valeur par défaut lors d'un reset 0xFFFF, POSxCNT à 0)
	POS1CNT=0;			// normalement déjà à 0 si reset (est ce valable pour tous les reset : soft, stack, ...) 
	POS2CNT=0;			// normalement déjà à 0 si reset (est ce valable pour tous les reset : soft, stack, ...)

// interruption QEI:
/*
	IPC14bits.QEI1IP	= 4;	// QEI1 interrupt priority
	IPC18bits.QEI2IP	= 4;	// QEI2 interrupt priority
	IFS3bits.QEI1IF	= 0;	// clear QEI1 interrupt flag
	IFS4bits.QEI2IF	= 0;	// clear QEI2 interrupt flag
	IEC3bits.QEI1IE	= 0;	// QEI1 interrupt enable
	IEC4bits.QEI2IE	= 0;	// QEI2 interrupt enable
*/
}

/***************************************************************************************
Interruption module QEI1

entrées : -
sortie : -    
*/
void __attribute__ ((interrupt, no_auto_psv)) _QEI1Interrupt(void) 
{
	IFS3bits.QEI1IF=0;	// acquittement

}

/***************************************************************************************
Interruption module QEI2

entrées : -
sortie : -  
*/
void __attribute__ ((interrupt, no_auto_psv)) _QEI2Interrupt(void) 
{
	IFS4bits.QEI2IF=0;	// acquittement

}
