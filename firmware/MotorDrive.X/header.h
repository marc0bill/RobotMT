/*
Club Robot - Polytech Marseille

fichier des définitions communes
- constantes (quartz, ...)
- variables globales,
- ...

Révision:     	$Rev: $
Auteur:       	$Author: $
Date révision: 	$Date:  $
projet:      	$URL: $


*/
#ifndef _HEADER_H_
#define _HEADER_H_


#ifdef __dsPIC33FJ128MC802__
#include <p33fj128mc802.h>
#endif
#ifdef __dsPIC33FJ128MC804__
#include <p33fj128mc804.h>
#endif


#include <libpic30.h>

#define pi 3.14159265
#define C_pi 3.14159265
#define C_pi2 1.570796327
#define C_3pi2 4.712388998
#define C_2pi 6.283185307
#define C_pi4 0.785398163
#define C_3pi4 2.356194488
#define C_5pi4 3.926990813



#define FQUARTZ     4000000	// 4 MHz
#define PLL_N1      0	// 2 	(0.8M<FQuartz/N1<8M)
#define PLL_M       78	// 80 	(100M<FQuartz/N1*M<200M)		//  todo voir si MUL_40 définit dans .h
#define PLL_N2      0	// 2	(12.5M<FQuartz*M/(N1*N2)<80M)
				// FOSC=80MHz
				// FCY=40MHz
#define FTYPE       0b011 // Primary oscillator (XT, HS, EC) with PLL (NOSC=0b011)
#define FOSC        (FQUARTZ/(2*2))*80	//(FQUARTZ/(N1*N2))*M
#define FCY         FOSC/2
#define COEFF_PR1   2   // coeff correctif Timer1 pour interrupt tous les 1ms
                        // 1 pour PLL_M=38, soit FCY=20MHz
                        // 2 pour PLL_M=78, soit FCY=40MHz



/*Definition du GROS robot */

#define DEPART_X 0.0
#define DEPART_Y 0.0
#define DEPARRT_ANG 0.0
#define VCROISIERE 300
#define ERR_ANGm 0.05
#define ERR_XYm 30.0
#define D_OBSm 18.0

#define nbPst 24

#define MOTEUR_SENS_INVERSE

#define INFO_COM 	0
#define INFO_C_VTS_D	0 
#define INFO_C_VTS_A	0// C_Vts_a_en
#define INFO_C_VTS_M1	1// C_Vts_M1_en
#define INFO_C_VTS_M2	1// C_Vts_M2_en
#define INFO_C_DIS	0// C_Dis_en
#define INFO_C_ANG	0// C_Ang_en
#define INFO_C_ANGPI	0// C_AngModPi_en
#define INFO_C_X	0// C_x_en
#define INFO_C_Y	0// C_y_en
#define INFO_C_VMAX	0// C_Vmax_M_en
#define INFO_C_MODE     0// C_mode_en
#define INFO_ERRDIS	0// C_ErrDis_en
#define INFO_C_ERRANG	0// C_ErrAng_en
#define INFO_C_ERRX	0// C_Err_x_en
#define INFO_C_ERRY	0// C_Err_y_en
#define INFO_C_DOBS	0// C_d_Obst_en
#define INFO_R_VTS_D	0// R_Vts_d_en
#define INFO_R_VTS_A	0// R_Vts_a_en
#define INFO_R_VTS_M1	0// R_Vts_M1_en
#define INFO_R_VTS_M2	0// R_Vts_M2_en
#define INFO_R_DIS	0// R_Dis_en
#define INFO_R_ANG	1// R_Ang_en
#define INFO_R_ANGPI	0// R_AngModPi_en
#define INFO_R_X	1// R_x_en
#define INFO_R_Y	1// R_y_en
#define INFO_R_ERRDIS	0// R_ErrDis_en
#define INFO_R_ERRANG	0// R_ErrAng_en
#define INFO_R_ERRX	0// R_Err_x_en
#define INFO_R_ERRY	0// R_Err_y_en
#define INFO_R_DOBS	0//R_d_Obst_en
#define INFO_CARTE	0// carte_en

#define ASSERV_TE	0.004//Te
#define ASSERV_KVPURE	40.0 //KvPure
#define ASSERV_KVPID	15.0 //KvPID
#define ASSERV_TIV	0.1  //Tiv
#define ASSERV_TDV	1.0  //Tdv
#define ASSERV_AV	1.0  //Av
#define ASSERV_KPD	1.0	 //KpD
#define ASSERV_KPA	0.1	 //KpA
#define ASSERV_TIP	1.0	 //Tip
#define ASSERV_TDP	1.0	 //Tdp
#define ASSERV_AP	1.0	 //Ap
#define ASSERV_TYPE_V	1	 //corr_type_v
#define ASSERV_TYPE_P	0	 //corr_type_p
#define ASSERV_SEUIL	50.0 //Seuil
#define ASSERV_A	5.0	 //Acceleration
#define ASSERV_R	100.0 //Rayon_Roue
#define ASSERV_DR	275.0//Distance_Roue
#define ASSERV_RR	28.8 //Rapport_Reduction
#define ASSERV_NB_IMP	500.0//Nb_imp


// broche "sens Moteur 1"
#define	SENS_M1		PORTBbits.RB14		// PORT
//#define	SENS_M1		LATBbits.LATB14
#define T_SENS_M1	TRISBbits.TRISB14	// direction du port
// broche "sens Moteur 2"
#define	SENS_M2		PORTBbits.RB12		// PORT
//#define	SENS_M2		LATBbits.LATB12
#define T_SENS_M2	TRISBbits.TRISB12	// direction du port
// broche "arret des moteurs 1 et 2"
#define Brake12		PORTBbits.RB11		// PORT
#define T_Brake12	TRISBbits.TRISB11	// direction du port
#define L_Brake12	LATBbits.LATAB11		// Latch du port


// broche I/O :
// IO1 : PULL-UP interne POSSIBLE CN3
#define IO1		PORTAbits.RA1		// PORT
#define L_IO1		LATAbits.LATA1		// direction du port
#define T_IO1		TRISAbits.TRISA1	// Latch du port

// START : PULL-UP interne POSSIBLE CN2
#define START		  PORTAbits.RA0
#define L_START		  LATAbits.LATA0
#define T_START		  TRISAbits.TRISA0


#define LED1		PORTCbits.RC9
#define L_LED1		LATCbits.LATC9
#define T_LED1		TRISCbits.TRISC9
//
#define LED0		PORTCbits.RC8
#define L_LED0		LATCbits.LATC8
#define T_LED0		TRISCbits.TRISC8


//interrupteur couleur
#define Switch_Couleur		IO1
#define L_Switch_Couleur	L_IO1
#define T_Switch_Couleur	T_IO1




#define tempspartie 90000



#endif
