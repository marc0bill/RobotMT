/*
Club Robot - Polytech Marseille

Fonctions liées à la resption des donnees venant de l'UART


0.0.1: 04/12/2011

Révision:     	$Rev: $
Auteur:       	$Author: $
Date révision: 	$Date:  $
projet:      	$URL: $

*/
#include "header.h"
#include "uart.h"
#include "uartassig.h"
#include "move.h"
#include "asserv.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "timer.h"
#include <stdio.h>            /* for printf */ 


#include "uartTx.h"

//#include "ascenseur.h"
//#include "servo.h"


signed long char2long(char UxRx_string[UxRx_length],int istart){
	int i=0;
	signed long temp=0;
	for(i=istart;i<UxRx_length;i++)
	{
		if(isspace(UxRx_string[i])==1) 
		{
			break;
		}
		else
		{
			temp=temp*10+UxRx_string[i]-48;
		}
	}
	return temp;
}


signed long char2signedlong(char UxRx_string[UxRx_length]){
	if(UxRx_string[0]=='-')
	{
		return char2long(UxRx_string,1);
	}
	else
	{
		return char2long(UxRx_string,0);
	}
}

int assig_PstCons(int idAc,char UxRx_string[UxRx_length])
{
	static int i=0,j=0;
	if (strncmp(UxRx_string,"End",3)==0)
	{
		j=0;
		i=0;
		return 0;
	}
	switch(i)
	{
		case 0:
			TablePst.nb=atoi(UxRx_string);
			i++;
			break;
		case 1:
		TablePst.Dis[j]=char2signedlong(UxRx_string);
			i++;
			break;
		case 2:
			TablePst.Ang[j]=atof(UxRx_string);
			i++;
			break;
		case 3:
			TablePst.x[j]=atof(UxRx_string);
			i++;
			break;
		case 4:
			TablePst.y[j]=atof(UxRx_string);
			i++;
			break;
		case 5:
			TablePst.Vmax_M[j]=char2signedlong(UxRx_string);
			i++;
			break;
		case 6:
			TablePst.mode[j]=atoi(UxRx_string);
			i++;
			break;
		case 7:
			TablePst.wait[j]=atoi(UxRx_string);
			i++;
			break;
/*		case 8:
			TablePst.d_Obst[j]=atoi(UxRx_string);
			i++;
			break;*/
		case 8:
			TablePst.ErrAng[j]=atoi(UxRx_string);
			i++;
			break;
		case 9:
			TablePst.Err_x[j]=atoi(UxRx_string);
			i++;
			break;
		case 10:
			TablePst.Err_y[j]=atoi(UxRx_string);
			idAc=0;
			j++;
			i=0;
			break;
	}
	return idAc;
}

// Mode 1 Vitesse moteur = Vmax_ M;
int assig_PstCons_M1(int idAc,char UxRx_string[UxRx_length])
{
	static int i=0,j=0;	
	switch(i)
	{
		case 0:
			j=atoi(UxRx_string);
			//TablePst.nb;
			TablePst.mode[j]=1;
			TablePst.Dis[i]=0;
			TablePst.Ang[i]=0.0;
			TablePst.x[i]=0.0;
			TablePst.y[i]=0.0;
/*			TablePst.d_Obst[j]=20;*/
			TablePst.ErrAng[j]=ERR_ANGm;
			TablePst.Err_x[j]=ERR_XYm;
			TablePst.Err_y[j]=ERR_XYm;
			i++;
			break;
		case 1:
			TablePst.Vmax_M[j]=char2signedlong(UxRx_string);
			i++;
			break;
		case 2:
			TablePst.wait[j]=atoi(UxRx_string);
			idAc=0;
			i=0;
			break;
	}
	return idAc;
}

// Mode 2 Vitesse moteur = Vmax_ M;
int assig_PstCons_M2(int idAc,char UxRx_string[UxRx_length])
{
	static int i=0, j=0;	
	switch(i)
	{
		case 0:
			j=atoi(UxRx_string);
			//TablePst.nb;
			TablePst.mode[j]=2;

			TablePst.x[i]=0.0;
			TablePst.y[i]=0.0;
/*			TablePst.d_Obst[j]=20;*/
			TablePst.ErrAng[j]=ERR_ANGm;
			TablePst.Err_x[j]=ERR_XYm;
			TablePst.Err_y[j]=ERR_XYm;
			i++;
			break;
		case 1:
		TablePst.Dis[j]=char2signedlong(UxRx_string);
			i++;
			break;
		case 2:
			TablePst.Ang[j]=atof(UxRx_string);
			i++;
			break;
		case 3:
			TablePst.Vmax_M[j]=char2signedlong(UxRx_string);
			i++;
			break;
		case 4:
			TablePst.wait[j]=atoi(UxRx_string);
			idAc=0;
			i=0;
			break;
	}
	return idAc;
}

// Mode 3 XY
int assig_PstCons_M3(int idAc,char UxRx_string[UxRx_length])
{
	static int i=0, j=0;	
	switch(i)
	{
		case 0:
			j=atoi(UxRx_string);
			//TablePst.nb;
			TablePst.mode[j]=3;

			TablePst.Dis[j]=0;
			TablePst.Ang[j]=0.0;
			TablePst.ErrAng[j]=ERR_ANGm;
/*			TablePst.d_Obst[j]=20;*/
			i++;
			break;
		case 1:
			TablePst.x[j]=atof(UxRx_string);
			i++;
			break;
		case 2:
			TablePst.y[j]=atof(UxRx_string);
			i++;
			break;
		case 3:
			TablePst.Vmax_M[j]=char2signedlong(UxRx_string);
			i++;
			break;
		case 4:
			TablePst.wait[j]=atoi(UxRx_string);
/*			i++;
			break;
		case 5:
			TablePst.Err_x[j]=atoi(UxRx_string);
			i++;
			break;
		case 6:
			TablePst.Err_y[j]=atoi(UxRx_string);*/
			idAc=0;
			i=0;
			break;
	}
	return idAc;
}

// Mode 4 Angle
int assig_TuRn(int idAc,char UxRx_string[UxRx_length])
{
	static int i=0,j=0;
	switch(i)
	{
		case 0:
			j=atoi(UxRx_string);
			//TablePst.nb;
			TablePst.mode[j]=4;

			TablePst.Dis[j]=0;
			TablePst.x[j]=0.0;
			TablePst.y[j]=0.0;
			i++;
			break;
		case 1:
			TablePst.Ang[j]=atof(UxRx_string);
			i++;
			break;
		case 2:
			TablePst.Vmax_M[j]=char2signedlong(UxRx_string);
			i++;
			break;
		case 3:
			TablePst.wait[j]=atoi(UxRx_string);
			i++;
			break;
		case 4:
			TablePst.ErrAng[j]=atoi(UxRx_string);
			idAc=0;
			i=0;
			break;
	}
	return idAc;
}

// Mode 5 XY
/*
 *
 */
int assig_GoTo(int idAc,char UxRx_string[UxRx_length])
{
	static int i=0, j=0;	
	switch(i)
	{
		case 0:
			j=atoi(UxRx_string);
			//TablePst.nb;
			TablePst.mode[j]=5;

			TablePst.Dis[j]=0;
			TablePst.Ang[j]=0.0;
			i++;
			break;
		case 1:
			TablePst.x[j]=atof(UxRx_string);
			i++;
			break;
		case 2:
			TablePst.y[j]=atof(UxRx_string);
			i++;
			break;
		case 3:
			TablePst.Vmax_M[j]=char2signedlong(UxRx_string);
			i++;
			break;
		case 4:
			TablePst.wait[j]=atoi(UxRx_string);
			i++;
			break;
		case 5:
			TablePst.ErrAng[j]=atoi(UxRx_string);
			i++;
			break;
		case 6:
			TablePst.Err_x[j]=atoi(UxRx_string);
			i++;
			break;
		case 7:
			TablePst.Err_y[j]=atoi(UxRx_string);
			idAc=0;
			i=0;
			break;
	}
	return idAc;
}



// Mode 6 XY
int assig_PstCons_M6(int idAc,char UxRx_string[UxRx_length])
{
	static int i=0, j=0;	
	switch(i)
	{
		case 0:
			j=atoi(UxRx_string);
			//TablePst.nb;
			TablePst.mode[j]=6;

			TablePst.Dis[j]=0;
			TablePst.Ang[j]=0.0;
/*			TablePst.ErrAng[j]=ERR_ANGm;
			TablePst.d_Obst[j]=20;*/
			i++;
			break;
		case 1:
			TablePst.x[j]=atof(UxRx_string);
			i++;
			break;
		case 2:
			TablePst.y[j]=atof(UxRx_string);
			i++;
			break;
		case 3:
			TablePst.Vmax_M[j]=char2signedlong(UxRx_string);
			i++;
			break;
		case 4:
			TablePst.wait[j]=atoi(UxRx_string);
/*			i++;
			break;
		case 5:
			TablePst.Err_x[j]=atoi(UxRx_string);
			i++;
			break;
		case 6:
			TablePst.Err_y[j]=atoi(UxRx_string);*/
			idAc=0;
			i=0;
			break;
	}
	return idAc;
}


// Mode 7 XY
int assig_Track(int idAc,char UxRx_string[UxRx_length])
{
	static int i=0, j=0;	
	switch(i)
	{
		case 0:
			j=atoi(UxRx_string);
			TablePst.nb=j;
			TablePst.mode[j]=7;
			TablePst.Dis[j]=0;
			i++;
			break;
		case 1:
			TablePst.x[j]=atof(UxRx_string);
			i++;
			break;
		case 2:
			TablePst.y[j]=atof(UxRx_string);
			i++;
			break;
		case 3:
			TablePst.Ang[j]=atof(UxRx_string);
			i++;
			break;
		case 4:
			TablePst.wait[j]=atoi(UxRx_string);
			idAc=0;
			i=0;
			break;
	}
	return idAc;
}





// Mode 0 Telecommande
int assig_PstCons_M0(int idAc,char UxRx_string[UxRx_length])
{
	int j=0;	
	j=atoi(UxRx_string);
	//TablePst.nb;
	TablePst.mode[j]=0;
	TablePst.Dis[j]=0;
	TablePst.Ang[j]=0.0;	
	TablePst.x[j]=0.0;
	TablePst.y[j]=0.0;
	TablePst.Vmax_M[j]=VCROISIERE;
	TablePst.wait[j]=0;
/*	TablePst.ErrAng[j]=ERR_ANGm;
	TablePst.Err_x[j]=ERR_XYm;
	TablePst.Err_y[j]=ERR_XYm;
	TablePst.d_Obst[j]=20;
*/	
	idAc=0;
	return idAc;
}

int assig_Asserv(int idAc,char UxRx_string[UxRx_length])
{
	static int i=0;
	static double Te;
	static double Seuil;
	static double KvvPure,KvvPID,Tiv,Tdv,Av;
	static double KppD,KppA,Tip,Tdp,Ap;
	static int corr_type_v,corr_type_p;
	static double Acceleration;
	static double  Rayon_Roue, Distance_Roue, Rapport_Reduction, Nb_imp;


	switch(i)
	{
		case 0:
			Te=atof(UxRx_string);
			i++;
			break;
		case 1:
			KvvPure=atof(UxRx_string);
			i++;
			break;
		case 2:
			KvvPID=atof(UxRx_string);
			i++;
			break;
		case 3:
			Tiv=atof(UxRx_string);
			i++;
			break;
		case 4:
			Tdv=atof(UxRx_string);
			i++;
			break;
		case 5:
			Av=atof(UxRx_string);
			i++;
			break;
		case 6:
			KppD=atof(UxRx_string);
			i++;
			break;
		case 7:
			KppA=atof(UxRx_string);
			i++;
			break;
		case 8:
			Tip=atof(UxRx_string);
			i++;
			break;
		case 9:
			Tdp=atof(UxRx_string);
			i++;
			break;
		case 10:
			Ap=atof(UxRx_string);
			i++;
			break;
		case 11:
			corr_type_v=atoi(UxRx_string);
			i++;
			break;
		case 12:
			corr_type_p=atoi(UxRx_string);
			i++;
			break;
		case 13:
			Seuil=atof(UxRx_string);
			i++;
			break;
		case 14:
			Acceleration=atof(UxRx_string);
			i++;
			break;
		case 15:
			Rayon_Roue=atof(UxRx_string);
			i++;
			break;
		case 16:
			Distance_Roue=atof(UxRx_string);
			i++;
			break;
		case 17:
			Rapport_Reduction=atof(UxRx_string);
			i++;
			break;
		case 18:
			Nb_imp=atof(UxRx_string);
			init_asserv(Te,KvvPure,KvvPID,Tiv,Tdv,Av,KppD,KppA,Tip,Tdp,Ap,corr_type_v,corr_type_p,Seuil,Acceleration,Rayon_Roue,Distance_Roue,Rapport_Reduction,Nb_imp);
			idAc=0;
			i=0;
			break;
	}
	return idAc;		
}


int assig_VtsM(int idAc,char UxRx_string[UxRx_length])
{
	static int i=0;
//    static int e=0;
//    while(e <= 15)
//    {
//        IFS0bits.U1TXIF = 0;	// Renvoie de ce que le controleur voie dans le terminal PC
//        U1TXREG = UxRx_string[e];
//        e++;
//    }
    ////////////////////////////////////////////////////////////////// ON EST LA
//    static int e = 0;
//	IFS0bits.U1TXIF = 0;	// acquittement
//	U1TXREG = UxRx_string[e]; // Transmit one character
//	e++;
//	if(e>=15){
//        IEC0bits.U1TXIE	= 0;	// // Disenable Transmisssion Interrupts 1
//	//U1STAbits.UTXEN = 0;	// UART1 transmitter Disenable;
//		FlagUart.U1Tx=1;		// Information envoye
//	e=0;
    
	switch(i)
	{
		case 0:
			Consigne.Vts_M1=atof(UxRx_string);// Bizare, j'aurai mis atoi
			i++;
			break;
		case 1:
			Consigne.Vts_M2=atof(UxRx_string);// Bizare, j'aurai mis atoi
			idAc=0;
			i=0;
			break;
		default :
			break;
	}
	return idAc;		
}

/*
int assig_Info(int idAc,char UxRx_string[UxRx_length])
{
	if (strncmp(UxRx_string,"End",3)==0)	return 0;


	if(strncmp(UxRx_string,"Com_Off",7)==0)	Info_en.Com=0;
	if(strncmp(UxRx_string,"Com_On",6)==0)	Info_en.Com=1;
	if(strncmp(UxRx_string,"VdC_Off",7)==0)	Info_en.C_Vts_d=0;;
	if(strncmp(UxRx_string,"VdC_On",6)==0)	Info_en.C_Vts_d=1;
	if(strncmp(UxRx_string,"VaC_Off",7)==0)	Info_en.C_Vts_a=0;
	if(strncmp(UxRx_string,"VaC_On",6)==0)	Info_en.C_Vts_a=1;
	if(strncmp(UxRx_string,"V1C_Off",7)==0)	Info_en.C_Vts_M1=0;
	if(strncmp(UxRx_string,"V1C_On",6)==0)	Info_en.C_Vts_M1=1;
	if(strncmp(UxRx_string,"V2C_Off",7)==0)	Info_en.C_Vts_M2=0;
	if(strncmp(UxRx_string,"V2C_On",6)==0)	Info_en.C_Vts_M2=1;
	if(strncmp(UxRx_string,"DsC_Off",7)==0)	Info_en.C_Dis=0;
	if(strncmp(UxRx_string,"DsC_On",6)==0)	Info_en.C_Dis=1;
	if(strncmp(UxRx_string,"AgC_Off",7)==0)	Info_en.C_Ang=0;
	if(strncmp(UxRx_string,"AgC_On",6)==0)	Info_en.C_Ang=1;
	if(strncmp(UxRx_string,"AMC_Off",7)==0)	Info_en.C_AngModPi=0;
	if(strncmp(UxRx_string,"AMC_On",6)==0)	Info_en.C_AngModPi=1;
	if(strncmp(UxRx_string,"XrC_Off",7)==0)	Info_en.C_x=0;
	if(strncmp(UxRx_string,"XrC_On",6)==0)	Info_en.C_x=1;
	if(strncmp(UxRx_string,"YrC_Off",7)==0)	Info_en.C_y=0;
	if(strncmp(UxRx_string,"YrC_On",6)==0)	Info_en.C_y=1;
	if(strncmp(UxRx_string,"VmC_Off",7)==0)	Info_en.C_Vmax_M=0;
	if(strncmp(UxRx_string,"VmC_On",6)==0)	Info_en.C_Vmax_M=1;
	if(strncmp(UxRx_string,"MdC_Off",7)==0)	Info_en.C_mode=0;
	if(strncmp(UxRx_string,"MdC_On",6)==0)	Info_en.C_mode=1;
	if(strncmp(UxRx_string,"EdC_Off",7)==0)	Info_en.C_ErrDis=0;
	if(strncmp(UxRx_string,"EdC_On",6)==0)	Info_en.C_ErrDis=1;
	if(strncmp(UxRx_string,"EaC_Off",7)==0)	Info_en.C_ErrAng=0;
	if(strncmp(UxRx_string,"EaC_On",6)==0)	Info_en.C_ErrAng=1;
	if(strncmp(UxRx_string,"ExC_Off",7)==0)	Info_en.C_Err_x=0;
	if(strncmp(UxRx_string,"ExC_On",6)==0)	Info_en.C_Err_x=1;
	if(strncmp(UxRx_string,"EyC_Off",7)==0)	Info_en.C_Err_y=0;
	if(strncmp(UxRx_string,"EyC_On",6)==0)	Info_en.C_Err_y=1;
	if(strncmp(UxRx_string,"dOC_Off",7)==0)	Info_en.C_d_Obst=0;
	if(strncmp(UxRx_string,"dOC_On",6)==0)	Info_en.C_d_Obst=1;
	if(strncmp(UxRx_string,"VdR_Off",7)==0)	Info_en.R_Vts_d=0;
	if(strncmp(UxRx_string,"VdR_On",6)==0)	Info_en.R_Vts_d=1;
	if(strncmp(UxRx_string,"VaR_Off",7)==0)	Info_en.R_Vts_a=0;
	if(strncmp(UxRx_string,"VaR_On",6)==0)	Info_en.R_Vts_a=1;
	if(strncmp(UxRx_string,"V1R_Off",7)==0)	Info_en.R_Vts_M1=0;
	if(strncmp(UxRx_string,"V1R_On",6)==0)	Info_en.R_Vts_M1=1;
	if(strncmp(UxRx_string,"V2R_Off",7)==0)	Info_en.R_Vts_M2=0;
	if(strncmp(UxRx_string,"V2R_On",6)==0)	Info_en.R_Vts_M2=1;
	if(strncmp(UxRx_string,"DsR_Off",7)==0)	Info_en.R_Dis=0;
	if(strncmp(UxRx_string,"DsR_On",6)==0)	Info_en.R_Dis=1;
	if(strncmp(UxRx_string,"AgR_Off",7)==0)	Info_en.R_Ang=0;
	if(strncmp(UxRx_string,"AgR_On",6)==0)	Info_en.R_Ang=1;
	if(strncmp(UxRx_string,"AMR_Off",7)==0)	Info_en.R_AngModPi=0;
	if(strncmp(UxRx_string,"AMR_On",6)==0)	Info_en.R_AngModPi=1;
	if(strncmp(UxRx_string,"XrR_Off",7)==0)	Info_en.R_x=0;
	if(strncmp(UxRx_string,"XrR_On",6)==0)	Info_en.R_x=1;
	if(strncmp(UxRx_string,"YrR_Off",7)==0)	Info_en.R_y=0;
	if(strncmp(UxRx_string,"YrR_On",6)==0)	Info_en.R_y=1;
	if(strncmp(UxRx_string,"EdR_Off",7)==0)	Info_en.R_ErrDis=0;
	if(strncmp(UxRx_string,"EdR_On",6)==0)	Info_en.R_ErrDis=1;
	if(strncmp(UxRx_string,"EaR_Off",7)==0)	Info_en.R_ErrAng=0;
	if(strncmp(UxRx_string,"EaR_On",6)==0)	Info_en.R_ErrAng=1;
	if(strncmp(UxRx_string,"ExR_Off",7)==0)	Info_en.R_Err_x=0;
	if(strncmp(UxRx_string,"ExR_On",6)==0)	Info_en.R_Err_x=1;
	if(strncmp(UxRx_string,"EyR_Off",7)==0)	Info_en.R_Err_y=0;
	if(strncmp(UxRx_string,"EyR_On",6)==0)	Info_en.R_Err_y=1;
	if(strncmp(UxRx_string,"dOR_Off",7)==0)	Info_en.R_d_Obst=0;
	if(strncmp(UxRx_string,"dOR_On",6)==0)	Info_en.R_d_Obst=1;
	return idAc;
		
}
*/


int idAction(char Action[UxRx_length]){
	if(strncmp(Action,"NaN",3)==0)		return 0;
	if(strncmp(Action,"PstCons",7)==0)	return 2;
	if(strncmp(Action,"Asserv",6)==0)	return 3;
	if(strncmp(Action,"VtsM",4)==0)		return 4;
	if(strncmp(Action,"Track",5)==0)	return 5;
	if(strncmp(Action,"TU1Tx",5)==0)	return 6;
	if(strncmp(Action,"TuRn",4)==0)		return 7;
	if(strncmp(Action,"GoTo",4)==0)		return 8;


	if(strncmp(Action,"Start",5)==0)	return 11;
	if(strncmp(Action,"Restart",7)==0)	return 12;
	if(strncmp(Action,"Stop",4)==0)		return 13;
	if(strncmp(Action,"Continu",8)==0)	return 14;
	if(strncmp(Action,"Telecommande",12)==0)		return 15;

#ifdef _ASCENSEUR_H_
	if(strncmp(Action,"AscUp",5)==0)	return 16;
	if(strncmp(Action,"AscDown",7)==0)	return 17;
#endif
#ifdef _SERVO_H_
	if(strncmp(Action,"OpenPince",5)==0)	return 18;
	if(strncmp(Action,"ClosePince",7)==0)	return 19;
#endif
	if(strncmp(Action,"DfltAss",7)==0)	return 20;
	if(strncmp(Action,"SvAss",5)==0)	return 21;
	if(strncmp(Action,"LdAss",5)==0)	return 22;



	if(strncmp(Action,"VaC?",4)==0)	return 50;
	if(strncmp(Action,"V1C?",4)==0)	return 51;
	if(strncmp(Action,"V2C?",4)==0)	return 52;
	if(strncmp(Action,"DsC?",4)==0)	return 53;
	if(strncmp(Action,"AgC?",4)==0)	return 54;
	if(strncmp(Action,"AMC?",4)==0)	return 55;
	if(strncmp(Action,"XrC?",4)==0)	return 56;
	if(strncmp(Action,"YrC?",4)==0)	return 57;
	if(strncmp(Action,"VmC?",4)==0)	return 58;
	if(strncmp(Action,"MdC?",4)==0)	return 59;
	if(strncmp(Action,"EdC?",4)==0)	return 60;
	if(strncmp(Action,"EaC?",4)==0)	return 61;
	if(strncmp(Action,"ExC?",4)==0)	return 62;
	if(strncmp(Action,"EyC?",4)==0)	return 63;
	if(strncmp(Action,"dOC?",4)==0)	return 64;
	if(strncmp(Action,"VdR?",4)==0)	return 65;
	if(strncmp(Action,"VaR?",4)==0)	return 66;
	if(strncmp(Action,"V1R?",4)==0)	return 67;
	if(strncmp(Action,"V2R?",4)==0)	return 68;
	if(strncmp(Action,"DsR?",4)==0)	return 69;
	if(strncmp(Action,"AgR?",4)==0)	return 70;
	if(strncmp(Action,"AMR?",4)==0)	return 71;
	if(strncmp(Action,"XrR?",4)==0)	return 72;
	if(strncmp(Action,"YrR?",4)==0)	return 73;
	if(strncmp(Action,"EdR?",4)==0)	return 74;
	if(strncmp(Action,"EaR?",4)==0)	return 75;
	if(strncmp(Action,"ExR?",4)==0)	return 76;
	if(strncmp(Action,"EyR?",4)==0)	return 77;
	if(strncmp(Action,"dOR?",4)==0)	return 78;


	if(strncmp(Action,"Com_Off",7)==0)	return 500;
	if(strncmp(Action,"Com_On",6)==0)	return 501;
	if(strncmp(Action,"VdC_Off",7)==0)	return 502;
	if(strncmp(Action,"VdC_On",6)==0)	return 503;
	if(strncmp(Action,"VaC_Off",7)==0)	return 504;
	if(strncmp(Action,"VaC_On",6)==0)	return 505;
	if(strncmp(Action,"V1C_Off",7)==0)	return 506;
	if(strncmp(Action,"V1C_On",6)==0)	return 507;
	if(strncmp(Action,"V2C_Off",7)==0)	return 508;
	if(strncmp(Action,"V2C_On",6)==0)	return 509;
	if(strncmp(Action,"DsC_Off",7)==0)	return 510;
	if(strncmp(Action,"DsC_On",6)==0)	return 511;
	if(strncmp(Action,"AgC_Off",7)==0)	return 512;
	if(strncmp(Action,"AgC_On",6)==0)	return 513;
	if(strncmp(Action,"AMC_Off",7)==0)	return 514;
	if(strncmp(Action,"AMC_On",6)==0)	return 515;
	if(strncmp(Action,"XrC_Off",7)==0)	return 516;
	if(strncmp(Action,"XrC_On",6)==0)	return 517;
	if(strncmp(Action,"YrC_Off",7)==0)	return 518;
	if(strncmp(Action,"YrC_On",6)==0)	return 519;
	if(strncmp(Action,"VmC_Off",7)==0)	return 520;
	if(strncmp(Action,"VmC_On",6)==0)	return 521;
	if(strncmp(Action,"MdC_Off",7)==0)	return 522;
	if(strncmp(Action,"MdC_On",6)==0)	return 523;
	if(strncmp(Action,"EdC_Off",7)==0)	return 524;
	if(strncmp(Action,"EdC_On",6)==0)	return 525;
	if(strncmp(Action,"EaC_Off",7)==0)	return 526;
	if(strncmp(Action,"EaC_On",6)==0)	return 527;
	if(strncmp(Action,"ExC_Off",7)==0)	return 528;
	if(strncmp(Action,"ExC_On",6)==0)	return 529;
	if(strncmp(Action,"EyC_Off",7)==0)	return 530;
	if(strncmp(Action,"EyC_On",6)==0)	return 531;
	if(strncmp(Action,"dOC_Off",7)==0)	return 532;
	if(strncmp(Action,"dOC_On",6)==0)	return 533;
	if(strncmp(Action,"VdR_Off",7)==0)	return 534;
	if(strncmp(Action,"VdR_On",6)==0)	return 535;
	if(strncmp(Action,"VaR_Off",7)==0)	return 536;
	if(strncmp(Action,"VaR_On",6)==0)	return 537;
	if(strncmp(Action,"V1R_Off",7)==0)	return 538;
	if(strncmp(Action,"V1R_On",6)==0)	return 539;
	if(strncmp(Action,"V2R_Off",7)==0)	return 540;
	if(strncmp(Action,"V2R_On",6)==0)	return 541;
	if(strncmp(Action,"DsR_Off",7)==0)	return 542;
	if(strncmp(Action,"DsR_On",6)==0)	return 543;
	if(strncmp(Action,"AgR_Off",7)==0)	return 544;
	if(strncmp(Action,"AgR_On",6)==0)	return 545;
	if(strncmp(Action,"AMR_Off",7)==0)	return 546;
	if(strncmp(Action,"AMR_On",6)==0)	return 547;
	if(strncmp(Action,"XrR_Off",7)==0)	return 548;
	if(strncmp(Action,"XrR_On",6)==0)	return 549;
	if(strncmp(Action,"YrR_Off",7)==0)	return 550;
	if(strncmp(Action,"YrR_On",6)==0)	return 551;
	if(strncmp(Action,"EdR_Off",7)==0)	return 552;
	if(strncmp(Action,"EdR_On",6)==0)	return 553;
	if(strncmp(Action,"EaR_Off",7)==0)	return 554;
	if(strncmp(Action,"EaR_On",6)==0)	return 555;
	if(strncmp(Action,"ExR_Off",7)==0)	return 556;
	if(strncmp(Action,"ExR_On",6)==0)	return 557;
	if(strncmp(Action,"EyR_Off",7)==0)	return 558;
	if(strncmp(Action,"EyR_On",6)==0)	return 559;
	if(strncmp(Action,"dOR_Off",7)==0)	return 560;
	if(strncmp(Action,"dOR_On",6)==0)	return 561;
	if(strncmp(Action,"Crt_Off",7)==0)	return 562;
	if(strncmp(Action,"Crt_On",6)==0)	return 563;
	return 0;
}



void assig_char(char UxRx_string[UxRx_length]){
	static int idAc=0;
	switch(idAc)
	{
		case 0:
			switch(idAction(UxRx_string))
			{
				case 2: //UxRx_string == "PstCons"
					idAc=2;
                    Info_en.ComOne=1;
					break;
				case 3: //UxRx_string == "Asserv"
					idAc=3;
                    Info_en.ComOne=1;
					break;
				case 4: //UxRx_string == "VtsM"
					idAc=4;
                    Info_en.ComOne=1;
					break;
				case 5: //UxRx_string == "Track"
					idAc=5;
					break;
				case 6: //UxRx_string == "TU1Tx"
					idAc=6;
                    Info_en.ComOne=1;
					break;
				case 7: //UxRx_string == "TuRn"
					idAc=7;
					break;
				case 8: //UxRx_string == "GoTo"
					idAc=8;
                    Info_en.ComOne=1;
					break;





				case 11: //UxRx_string == "Start"
					FlagMove.Ordre=1;	// Met en activité le robot
                    Info_en.ComOne=1;
					break;
				case 12: //UxRx_string == "Restart"
					FlagMove.Ordre=3;	// Reinitialisation la  table de points de parcours et met en activité le robot
                    Info_en.ComOne=1;
					break;
				case 13: //UxRx_string == "Stop"
					FlagMove.Ordre=2;
					break;
				case 14: //UxRx_string == "Continu"
					FlagMove.Ordre=4;
					break;
				case 15: //UxRx_string == "Telecommande"
					FlagMove.Ordre=5;// Consigne.mode=0;	Consigne.Vmax_M=1000;
					break;
#ifdef _ASCENSEUR_H_
				case 16: //UxRx_string == "AscUp"
					ascenseur(up);
					break;
				case 17: //UxRx_string == "AscDown"
					ascenseur(down);
					break;
#endif
#ifdef _SERVO_H_
				case 18: //UxRx_string == "OpenPince"
					ouvrir_pince();
					break;
				case 19: //UxRx_string == "ClosePince"
					fermer_pince();
					break;
#endif
				case 20: //UxRx_string == "DfltAss"
					default_asserv();
					break;
#ifdef ADDRESS_EEPROM
				case 21: //UxRx_string == "SvAss"
					save_asserv();
					break;
				case 22: //UxRx_string == "LdAss"
					load_asserv();
					break;
#endif
				case 50: //UxRx_string == "VaC"
					aff_Info_en_Tx(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
					Info_en.C_Vts_a=1;
					Info_en.ComOne=1;
					break;
				case 51: //UxRx_string == "V1C"
					aff_Info_en_Tx(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
					Info_en.C_Vts_M1=1;
					Info_en.ComOne=1;
					break;
				case 52: //UxRx_string == "V2C"
					aff_Info_en_Tx(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
					Info_en.C_Vts_M2=1;
					Info_en.ComOne=1;
					break;
				case 53: //UxRx_string == "DsC"
					aff_Info_en_Tx(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
					Info_en.C_Dis=1;
					Info_en.ComOne=1;
					break;
				case 54: //UxRx_string == "AgC"
					aff_Info_en_Tx(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
					Info_en.C_Ang=1;
					Info_en.ComOne=1;
					break;
				case 55: //UxRx_string == "AMC"
					aff_Info_en_Tx(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
					Info_en.C_AngModPi=1;
					Info_en.ComOne=1;
					break;
				case 56: //UxRx_string == "XrC"
					aff_Info_en_Tx(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
					Info_en.C_x=1;
					Info_en.ComOne=1;
					break;
				case 57: //UxRx_string == "YrC"
					aff_Info_en_Tx(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
					Info_en.C_y=1;
					Info_en.ComOne=1;
					break;
				case 58: //UxRx_string == "VmC"
					aff_Info_en_Tx(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
					Info_en.C_Vmax_M=1;
					Info_en.ComOne=1;
					break;
				case 59: //UxRx_string == "MdC"
					aff_Info_en_Tx(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
					Info_en.C_mode=1;
					Info_en.ComOne=1;
					break;
				case 60: //UxRx_string == "EdC"
					aff_Info_en_Tx(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
					Info_en.C_ErrDis=1;
					Info_en.ComOne=1;
					break;
				case 61: //UxRx_string == "EaC"
					aff_Info_en_Tx(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
					Info_en.C_ErrAng=1;
					Info_en.ComOne=1;
					break;
				case 62: //UxRx_string == "ExC"
					aff_Info_en_Tx(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
					Info_en.C_Err_x=1;
					Info_en.ComOne=1;
					break;
				case 63: //UxRx_string == "EyC"
					aff_Info_en_Tx(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
					Info_en.C_Err_y=1;
					Info_en.ComOne=1;
					break;
#ifdef _MESURE_DISTANCE_H_
				case 64: //UxRx_string == "dOC"
					aff_Info_en_Tx(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
					Info_en.C_d_Obst=1;
					Info_en.ComOne=1;
					break;
#endif
				case 65: //UxRx_string == "VdR"
					aff_Info_en_Tx(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
					Info_en.R_Vts_d=1;
					Info_en.ComOne=1;
					break;
				case 66: //UxRx_string == "VaR"
					aff_Info_en_Tx(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
					Info_en.R_Vts_a=1;
					Info_en.ComOne=1;
					break;
				case 67: //UxRx_string == "V1R"
					aff_Info_en_Tx(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
					Info_en.R_Vts_M1=1;
					Info_en.ComOne=1;
					break;
				case 68: //UxRx_string == "V2R"
					aff_Info_en_Tx(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
					Info_en.R_Vts_M2=1;
					Info_en.ComOne=1;
					break;
				case 69: //UxRx_string == "DsR"
					aff_Info_en_Tx(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
					Info_en.R_Dis=1;
					Info_en.ComOne=1;
					break;
				case 70: //UxRx_string == "AgR"
					aff_Info_en_Tx(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
					Info_en.R_Ang=1;
					Info_en.ComOne=1;
					break;
				case 71: //UxRx_string == "AMR"
					aff_Info_en_Tx(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
					Info_en.R_AngModPi=1;
					Info_en.ComOne=1;
					break;
				case 72: //UxRx_string == "XrR"
					aff_Info_en_Tx(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
					Info_en.R_x=1;
					Info_en.ComOne=1;
					break;
				case 73: //UxRx_string == "YrR"
					aff_Info_en_Tx(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
					Info_en.R_y=1;
					Info_en.ComOne=1;
					break;
				case 74: //UxRx_string == "EdR"
					aff_Info_en_Tx(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
					Info_en.R_ErrDis=1;
					Info_en.ComOne=1;
					break;
				case 75: //UxRx_string == "EaR"
					aff_Info_en_Tx(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
					Info_en.R_ErrAng=1;
					Info_en.ComOne=1;
					break;
				case 76: //UxRx_string == "ExR"
					aff_Info_en_Tx(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
					Info_en.R_Err_x=1;
					Info_en.ComOne=1;
					break;
				case 77: //UxRx_string == "EyR"
					aff_Info_en_Tx(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
					Info_en.R_Err_y=1;
					Info_en.ComOne=1;
					break;
#ifdef _MESURE_DISTANCE_H_
				case 78: //UxRx_string == "dOR"
					aff_Info_en_Tx(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
					Info_en.R_d_Obst=1;
					Info_en.ComOne=1;
					break;
#endif



				case 500:
					Info_en.Com=0;
					break;
				case 501:
					Info_en.Com=1;
					break;
				case 502:
					Info_en.C_Vts_d=0;
					break;
				case 503:
					Info_en.C_Vts_d=1;
					break;
				case 504:
					Info_en.C_Vts_a=0;
					break;
				case 505:
					Info_en.C_Vts_a=1;
					break;
				case 506:
					Info_en.C_Vts_M1=0;
					break;
				case 507:
					Info_en.C_Vts_M1=1;
					break;
				case 508:
					Info_en.C_Vts_M2=0;
					break;
				case 509:
					Info_en.C_Vts_M2=1;
					break;
				case 510:
					Info_en.C_Dis=0;
					break;
				case 511:
					Info_en.C_Dis=1;
					break;
				case 512:
					Info_en.C_Ang=0;
					break;
				case 513:
					Info_en.C_Ang=1;
					break;
				case 514:
					Info_en.C_AngModPi=0;
					break;
				case 515:
					Info_en.C_AngModPi=1;
					break;
				case 516:
					Info_en.C_x=0;
					break;
				case 517:
					Info_en.C_x=1;
					break;
				case 518:
					Info_en.C_y=0;
					break;
				case 519:
					Info_en.C_y=1;
					break;
				case 520:
					Info_en.C_Vmax_M=0;
					break;
				case 521:
					Info_en.C_Vmax_M=1;
					break;
				case 522:
					Info_en.C_mode=0;
					break;
				case 523:
					Info_en.C_mode=1;
					break;
				case 524:
					Info_en.C_ErrDis=0;
					break;
				case 525:
					Info_en.C_ErrDis=1;
					break;
				case 526:
					Info_en.C_ErrAng=0;
					break;
				case 527:
					Info_en.C_ErrAng=1;
					break;
				case 528:
					Info_en.C_Err_x=0;
					break;
				case 529:
					Info_en.C_Err_x=1;
					break;
				case 530:
					Info_en.C_Err_y=0;
					break;
				case 531:
					Info_en.C_Err_y=1;
					break;
#ifdef _MESURE_DISTANCE_H_
				case 532:
					Info_en.C_d_Obst=0;
					break;
				case 533:
					Info_en.C_d_Obst=1;
					break;
#endif
				case 534:
					Info_en.R_Vts_d=0;
					break;
				case 535:
					Info_en.R_Vts_d=1;
					break;
				case 536:
					Info_en.R_Vts_a=0;
					break;
				case 537:
					Info_en.R_Vts_a=1;
					break;
				case 538:
					Info_en.R_Vts_M1=0;
					break;
				case 539:
					Info_en.R_Vts_M1=1;
					break;
				case 540:
					Info_en.R_Vts_M2=0;
					break;
				case 541:
					Info_en.R_Vts_M2=1;
					break;
				case 542:
					Info_en.R_Dis=0;
					break;
				case 543:
					Info_en.R_Dis=1;
					break;
				case 544:
					Info_en.R_Ang=0;
					break;
				case 545:
					Info_en.R_Ang=1;
					break;
				case 546:
					Info_en.R_AngModPi=0;
					break;
				case 547:
					Info_en.R_AngModPi=1;
					break;
				case 548:
					Info_en.R_x=0;
					break;
				case 549:
					Info_en.R_x=1;
					break;
				case 550:
					Info_en.R_y=0;
					break;
				case 551:
					Info_en.R_y=1;
					break;
				case 552:
					Info_en.R_ErrDis=0;
					break;
				case 553:
					Info_en.R_ErrDis=1;
					break;
				case 554:
					Info_en.R_ErrAng=0;
					break;
				case 555:
					Info_en.R_ErrAng=1;
					break;
				case 556:
					Info_en.R_Err_x=0;
					break;
				case 557:
					Info_en.R_Err_x=1;
					break;
				case 558:
					Info_en.R_Err_y=0;
					break;
				case 559:
					Info_en.R_Err_y=1;
					break;
#ifdef _MESURE_DISTANCE_H_
				case 560:
					Info_en.R_d_Obst=0;
					break;
				case 561:
					Info_en.R_d_Obst=1;
					break;
#endif
				case 562:
					Info_en.carte=0;
					break;
				case 563:
					Info_en.carte=1;
					break;
			}
			break;
		case 2:
			idAc=assig_PstCons(idAc,UxRx_string);
			break;
		case 3:
			idAc=assig_Asserv(idAc,UxRx_string);
			break;
		case 4:  //Action == "VtsM"
			idAc=assig_VtsM(idAc,UxRx_string);
			break;
		case 5://Action == "Track"
			idAc=assig_Track(idAc,UxRx_string);
			break;
		case 6:  //Action == "TU1Tx"
			T_U1Tx_wait=atoi(UxRx_string);
			idAc=0;
			break;
		case 7://Action == "TuRn"
			idAc=assig_TuRn(idAc,UxRx_string);
			break;
		case 8://Action == "GoTo"
			idAc=assig_GoTo(idAc,UxRx_string);
			break;
		default :
			idAc=0;
			break;
	}
}

