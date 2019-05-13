/*
Club Robot - Polytech Marseille

Révision:     	$Rev: $
Auteur:       	$Author: $
Date révision: 	$Date:  $
projet:      	$URL: $


*/
#ifndef _UARTTX_H_
#define _UARTTX_H_

#include "uart.h"


//#define _UART2_TX_PSTVTS_
//#define _UART2_TX_SERVO_



// Strucutre permttant de savoir quel donner il faut envoyer
struct Struct_EnTx{
	char Com; // Autorise l'envoie d'information
	char ComOne; // Autorise l'envoie d'information
	char C_Vts_d;
	char C_Vts_a;
	char C_Vts_M1;
	char C_Vts_M2;
	char C_Dis;
	char C_Ang;
	char C_AngModPi;
	char C_x;
	char C_y;
	char C_Vmax_M;
	char C_mode;
	char C_ErrDis;
	char C_ErrAng;
	char C_Err_x;
	char C_Err_y;
#ifdef _MESURE_DISTANCE_H_
	char C_d_Obst;
#endif


	char carte;

	char R_Vts_d;
	char R_Vts_a;
	char R_Vts_M1;
	char R_Vts_M2;
	char R_Dis;
	char R_Ang;
	char R_AngModPi;
	char R_x;
	char R_y;
	char R_ErrDis;
	char R_ErrAng;
	char R_Err_x;
	char R_Err_y;
#ifdef _MESURE_DISTANCE_H_
	char R_d_Obst;
#endif
};

extern struct Struct_EnTx Info_en;
extern unsigned T_U1Tx_wait;


extern void aff_Info_en_Tx(char,char,char,char,char,char,char,char,char,char,char,char,char,char,char,char,char,char,char,char,char,char,char,char,char,char,char,char,char,char,char,char);
extern void setComOne(void);
extern void uxtx_pstvts_char(unsigned long);
extern void uxtx_Data(char * , int *,int);
extern void  fctUartTx(char *);
#endif
