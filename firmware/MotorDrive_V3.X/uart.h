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


extern void initUART1(unsigned long);
void U1Tx_chaine(char string[UxTx_length]);

#endif
