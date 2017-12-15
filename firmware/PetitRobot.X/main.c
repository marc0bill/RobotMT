/*
Club Robot - Polytech Marseille

Révision:     	$Rev: $
Auteur:       	$Author: $
Date révision: 	$Date:  $
projet:      	$URL: $

*/

#include "header.h"	// processor, constantes, variables globales...
#include "init_pic.h"
#include "pwm.h"
#include "QEI.h"
#include "asserv.h"
#include "timer.h"
#include "i2c.h"
#include "uart.h"
#include "move.h"
#include "uartTx.h"




/***********************************************************************
				CONFIGURATION DU PIC
*/
#ifdef _CARTE_MOTEUR_V1_
_FOSCSEL(FNOSC_PRIPLL); // Primary Oscillator (XT, HS, EC) w/ PLL
_FOSC(FCKSM_CSECMD & OSCIOFNC_OFF  & POSCMD_XT);
    //FCKSM_CSECMD  Clock switching is enabled, Fail-Safe Clock Monitor is disabled
    //OSCIOFNC_OFF  OSC2 pin has clock out function
    //POSCMD_XT     XT Oscillator Mode
_FWDT(FWDTEN_OFF);
    // FWDTEN_OFF   Watchdog timer enabled/disabled by user software
//Configuration pin I2C
_FPOR(ALTI2C_ON)


#endif
#ifdef _CARTE_MOTEUR_V2_
//Configuration pin I2C
_FPOR(ALTI2C_ON)
//_FPOR(ALTI2C_ON & PWMPIN_OFF & HPOL_ON & LPOL_ON)                //ASDA/ASDL
//_FPOR(ALTI2C_OFF)
#endif
#ifdef _CARTE_MOTEUR_V3_
_FOSCSEL(FNOSC_PRIPLL); // Primary Oscillator (XT, HS, EC) w/ PLL
_FOSC(FCKSM_CSECMD & OSCIOFNC_OFF  & POSCMD_XT);
    //FCKSM_CSECMD  Clock switching is enabled, Fail-Safe Clock Monitor is disabled
    //OSCIOFNC_OFF  OSC2 pin has clock out function
    //POSCMD_XT     XT Oscillator Mode
_FWDT(FWDTEN_OFF);
    // FWDTEN_OFF   Watchdog timer enabled/disabled by user software
//Configuration pin I2C
_FPOR(ALTI2C_ON)
#endif



int main(void) 
{
    int Start_temp;
    //initialisation
    init_clock();	// horloge
    init_port();	// ports
    init_interrupt();	// inerruption
    init_PWM1();        // PWM1
    init_QEI();		// Capteurs incrementals
    init_timer1();	// Timer 1
    
    T_U1Tx_wait=100;
    aff_Info_en_Tx( INFO_COM,
            INFO_C_VTS_D,
            INFO_C_VTS_A,// C_Vts_a_en
            INFO_C_VTS_M1,// C_Vts_M1_en
            INFO_C_VTS_M2,// C_Vts_M2_en
            INFO_C_DIS,// C_Dis_en
            INFO_C_ANG,// C_Ang_en
            INFO_C_ANGPI,// C_AngModPi_en
            INFO_C_X,// C_x_en
            INFO_C_Y,// C_y_en
            INFO_C_VMAX,// C_Vmax_M_en
            INFO_C_MODE,// C_mode_en
            INFO_ERRDIS,// C_ErrDis_en
            INFO_C_ERRANG,// C_ErrAng_en
            INFO_C_ERRX,// C_Err_x_en
            INFO_C_ERRY,// C_Err_y_en
            INFO_C_DOBS,// C_d_Obst_en
            INFO_R_VTS_D,// R_Vts_d_en
            INFO_R_VTS_A,// R_Vts_a_en
            INFO_R_VTS_M1,// R_Vts_M1_en
            INFO_R_VTS_M2,// R_Vts_M2_en
            INFO_R_DIS,// R_Dis_en
            INFO_R_ANG,// R_Ang_en
            INFO_R_ANGPI,// R_AngModPi_en
            INFO_R_X,// R_x_en
            INFO_R_Y,// R_y_en
            INFO_R_ERRDIS,// R_ErrDis_en
            INFO_R_ERRANG,// R_ErrAng_en
            INFO_R_ERRX,// R_Err_x_en
            INFO_R_ERRY,// R_Err_y_en
            INFO_R_DOBS,//R_d_Obst_en
            INFO_CARTE);//carte_en
    init_asserv(ASSERV_TE,//Te
            ASSERV_KVPURE,//KvPure
            ASSERV_KVPID,//KvPID
            ASSERV_TIV,//Tiv
            ASSERV_TDV,//Tdv
            ASSERV_AV,//Av
            ASSERV_KPD,//KpD
            ASSERV_KPA,//KpA
            ASSERV_TIP,//Tip
            ASSERV_TDP,//Tdp
            ASSERV_AP,//Ap
            ASSERV_TYPE_V,//corr_type_v
            ASSERV_TYPE_P,//corr_type_p
            ASSERV_SEUIL,//Seuil
            ASSERV_A,//Acceleration
            ASSERV_R,//Rayon_Roue
            ASSERV_DR,//Distance_Roue
            ASSERV_RR,//Rapport_Reduction
            ASSERV_NB_IMP);//Nb_imp
    initUART1(9600);//9600:ok, 19200:NON, 14400:NON
    initUART2(9600);
    config_I2C();

    init_move();
    //init_ultrason();//initialise la porte des ultrason a 150cm

/*sans PI sur la vitesse*/
//	init_asserv(0.004,10.0 ,10.0 ,1.0,1.0,1.0,1.0,0.1,1.0,1.0,1.0,0,0,500.0,3.0,38.0,256.0,28.8,500.0);	
/*avec PI sur la vitesse*/

    //save_asserv();
    //load_asserv();


#ifdef _ASCENSEUR_H_
    init_ascenseur();
    ascenseur(down);
#endif
#ifdef _SERVO_H_
    init_pince();
    fermer_pince();
#endif

    /*Attente du lancement avec Jack*/
    Start_temp=START;
    while(START==Start_temp && FlagMove.Start!=1){
        uxtx_pstvts_char(tempsjeux);
#ifdef _MESURE_DISTANCE_H_
        mesure_distance();
        Reel.d_Obst=Dis.obstAv_uS;
#endif
    }

    FlagMove.Start=1;
    tempsjeux=0;

/* Secance de déplamcent */
    while(1){
        uxtx_pstvts_char(tempsjeux);
#ifdef _MESURE_DISTANCE_H_
        mesure_distance();
        if(FlagMove.Avance==1)
            Reel.d_Obst=Dis.obstAv_uS;
//		else if(FlagMove.Avance==-1)
//			Reel.d_Obst=Dis.obstAr_uS;
#endif

#ifdef _PATHFIND_H_
        demo_pathfinding();
#endif
    }
}



