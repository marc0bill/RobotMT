/*
Club Robot - Polytech Marseille

Fonctions liées à l'utilisation du module UART

version 0.0.1: 21/01/2011


Révision:     	$Rev: $
Auteur:       	$Author: $
Date révision: 	$Date:  $
projet:      	$URL: $

*/
#ifndef _UART_H_
#define _UART_H_


#define UxRx_length 8
#define UxTx_length 20

struct Struct_FlagUart{
	int U2Tx;		// indique la fin de la transmission de U2Tx_string
	int U1Tx;		// indique la fin de la transmission de U1Tx_string
	int U2Tx_wait;	// demande un attente avant la transmission d'un nouveau char
	int U1Tx_wait;	// demande un attente avant la transmission d'un nouveau char
	
};

extern char U1Tx_string[UxTx_length];
extern char U2Tx_string[UxTx_length];
extern int U1Tx_size;
extern int U2Tx_size;

extern struct Struct_FlagUart FlagUart;


extern struct Struct_EnTx Info_en;

extern void initUART1(unsigned long);
extern void initUART2(unsigned long) ;
extern void startU1TX(void);
void U1Tx_int(int Data);
void U1Tx_char(char carac);
void U1Tx_chaine(char string[UxTx_length]);

#endif
