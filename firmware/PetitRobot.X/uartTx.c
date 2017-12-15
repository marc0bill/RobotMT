/*
Club Robot - Polytech Marseille
Eurobot 2011

Révision:     	$Rev: $
Auteur:       	$Author: $
Date révision: 	$Date:  $
projet:      	$URL: $



*/
#include "header.h"
#include "move.h"
#include "uart.h"
//#include "mesure_distance.h"
#include <stdio.h>
#include <string.h>
#include "uartTx.h"

struct Struct_EnTx Info_en;
unsigned T_U1Tx_wait;

// Fonction permettant de definir quel donné sera transimise en temps reel vers l'extreieur via UART
void aff_Info_en_Tx(char Com,char C_Vts_d_en,char C_Vts_a_en,char C_Vts_M1_en,char C_Vts_M2_en,char C_Dis_en,char C_Ang_en,char C_AngModPi_en,char C_x_en,char C_y_en,char C_Vmax_M_en,char C_mode_en,char C_ErrDis_en,char C_ErrAng_en,char C_Err_x_en,char C_Err_y_en,char C_d_Obst_en,char R_Vts_d_en,char R_Vts_a_en,char R_Vts_M1_en,char R_Vts_M2_en,char R_Dis_en,char R_Ang_en,char R_AngModPi_en,char R_x_en,char R_y_en,char R_ErrDis_en,char R_ErrAng_en,char R_Err_x_en,char R_Err_y_en,char R_d_Obst_en, char carte_en){


Info_en.Com=Com;
Info_en.C_Vts_d=C_Vts_d_en;
Info_en.C_Vts_a=C_Vts_a_en;
Info_en.C_Vts_M1=C_Vts_M1_en;
Info_en.C_Vts_M2=C_Vts_M2_en;
Info_en.C_Dis=C_Dis_en;
Info_en.C_Ang=C_Ang_en;
Info_en.C_AngModPi=C_AngModPi_en;
Info_en.C_x=C_x_en;
Info_en.C_y=C_y_en;
Info_en.C_Vmax_M=C_Vmax_M_en;
Info_en.C_mode=C_mode_en;
Info_en.C_ErrDis=C_ErrDis_en;
Info_en.C_ErrAng=C_ErrAng_en;
Info_en.C_Err_x=C_Err_x_en;
Info_en.C_Err_y=C_Err_y_en;
#ifdef _MESURE_DISTANCE_H_
Info_en.C_d_Obst=C_d_Obst_en;
Info_en.R_d_Obst=R_d_Obst_en;
#endif



#ifdef _PATHFIND_H_
Info_en.carte=carte_en;
#else
Info_en.carte=0;
#endif

Info_en.R_Vts_d=R_Vts_d_en;
Info_en.R_Vts_a=R_Vts_a_en;
Info_en.R_Vts_M1=R_Vts_M1_en;
Info_en.R_Vts_M2=R_Vts_M2_en;
Info_en.R_Dis=R_Dis_en;
Info_en.R_Ang=R_Ang_en;
Info_en.R_AngModPi=R_AngModPi_en;
Info_en.R_x=R_x_en;
Info_en.R_y=R_y_en;
Info_en.R_ErrDis=R_ErrDis_en;
Info_en.R_ErrAng=R_ErrAng_en;
Info_en.R_Err_x=R_Err_x_en;
Info_en.R_Err_y=R_Err_y_en;
}




void asserv_Info_en_Tx(void){

}
#define CARTE_STATE 32
#ifdef _PATHFIND_H_
int printCarte(char str[UxTx_length],int * i_uxtx){
	int x,y;
	static char DataChar[Y_MAX][X_MAX];
	static int i=Y_MAX;
	static int j=0;
	int size;
	if(i<=0){//Fin de l'envoie
		i=Y_MAX;
		*i_uxtx=CARTE_STATE +1;
		return sprintf(str,"\n-------------\n");
	}
	else{
		if(i==Y_MAX){//Debut de l'envoie
			//Création de la carte à envoyer
			for (y=0; y<Y_MAX; y++){
				for (x=0; x<X_MAX; x++){
					if(CARTE[y][x]==1)DataChar[y][x]='#';
					else DataChar[y][x]='_';
					if(map[y][x].List==CHEMIN)DataChar[y][x]='C';
					if(map[y][x].List==DEPART) DataChar[y][x]='D';
					if(x==(arrond(Reel.x/CARRE_DIS)) && y==(arrond(Reel.y/CARRE_DIS)))DataChar[y][x]='R';
				}
			}
			i--;
			return sprintf(str,"\n-------------\n");
		}
		else{//Milieu de trame
			if(j==0)
				size=sprintf(str,"\n%c ", DataChar[i][0]);
			else
				size=sprintf(str,"%c ", DataChar[i][j]);
			j++;
			if(j>=X_MAX){
				j=0;
				i--;
				
			}
			return size;
		}
	}
}
#endif


/*
Fonction de création des mots à envoyer pour l'UART
les mots envoyés sont les informations de contenu dans les structures
"Struct_PstVts Consigne" et "Struct_PstVts Reel" (vitesse, position, ...)
*/




void uxtx_Com(unsigned long temps)
{	
	int j=0;
	int size;
	static int i=0;
//	static int size_last=0;
	static long int DataLInt[7];
	static int DataInt[3];
	static double DataDouble[21];
	char str[UxTx_length];

if(Info_en.Com==0) i=0;

//if(Info_en.Com==1 || Info_en.ComOne==1){
//#ifndef _UART2_TX_PSTVTS_
	//if(FlagUart.U1Tx==1)
/*#else
	if(FlagUart.U2Tx==1)
#endif*/
	switch(i){
		case 0:
			DataLInt[0]=temps;// long int
			DataLInt[1]=Consigne.Vts_d;// long int, contsigne vitesse de deplacement
			DataLInt[2]=Consigne.Vts_a;// long int, contsigne vitesse angulaire
			DataLInt[3]=Consigne.Dis;// long int, consigne de distance
			DataLInt[4]=Reel.Vts_d;// long int, 
			DataLInt[5]=Reel.Vts_a;// long int	
			DataLInt[6]=Reel.Dis; // long int
			DataInt[0]=Consigne.mode;// int, mode de déplacement
#ifdef _MESURE_DISTANCE_H_
			DataInt[1]=Consigne.d_Obst;// int
			DataInt[2]=Reel.d_Obst;// int
#endif
			DataDouble[0]=Consigne.Vts_M1;// double
			DataDouble[1]=Consigne.Vts_M2;// double
			DataDouble[2]=Consigne.Ang;// double
			DataDouble[3]=Consigne.AngModPi;// double
			DataDouble[4]=Consigne.x;// double
			DataDouble[5]=Consigne.y;// double
			DataDouble[6]=Consigne.Vmax_M;// double
			DataDouble[7]=Consigne.ErrDis;// double
			DataDouble[8]=Consigne.ErrAng;// double
			DataDouble[9]=Consigne.Err_x;// double
			DataDouble[10]=Consigne.Err_y;// double
			DataDouble[11]=Reel.Vts_M1;// double
			DataDouble[12]=Reel.Vts_M2;// double
			DataDouble[13]=Reel.Ang;// double
			DataDouble[14]=Reel.AngModPi;// double
			DataDouble[15]=Reel.x;// double
			DataDouble[16]=Reel.y;// double
			DataDouble[17]=Reel.ErrDis;// double
			DataDouble[18]=Reel.ErrAng;// double
			DataDouble[19]=Reel.Err_x;// double
			DataDouble[20]=Reel.Err_y;// double
			size=sprintf(str, "Tps:%ld", DataLInt[0]); //envoie du temps
			i=1;
			break;
		case 1:
			if(Info_en.C_Vts_d==1){
				size=sprintf(str, "\tVdC:%ld", DataLInt[1]);//envoie de la consigne vitesse de deplacement
				i=2;
				break;
			}
		case 2:
			if(Info_en.C_Vts_a==1){
				size=sprintf(str, "\tVaC:%ld", DataLInt[2]);//envoie de la consigne vitesse angulaire
				i=3;
				break;
			}
		case 3:
			if(Info_en.C_Dis==1){
				size=sprintf(str, "\tDsC:%ld", DataLInt[3]);
				i=4;
				break;
			}
		case 4:
			if(Info_en.R_Vts_d==1){
				size=sprintf(str, "\tVdR:%ld", DataLInt[4]);
				i=5;
				break;
			}
		case 5:
			if(Info_en.R_Vts_a==1){
				size=sprintf(str, "\tVaR:%ld", DataLInt[5]);
				i=6;
				break;
			}
		case 6:
			if(Info_en.R_Dis==1){
				size=sprintf(str, "\tDsR:%ld", DataLInt[6]);
				i=7;
				break;
			}
		case 7:
			if(Info_en.C_mode==1){
				size=sprintf(str, "\tMdC:%d", DataInt[0]);
#ifdef _MESURE_DISTANCE_H_
				i=8;
#else
				i=11;
#endif
				break;
			}
#ifdef _MESURE_DISTANCE_H_
		case 8:
			if(Info_en.C_d_Obst==1){
				size=sprintf(str, "\tdOC:%d", DataInt[1]);
				i=10;
				break;
			}
		case 10:
			if(Info_en.R_d_Obst==1){
				size=sprintf(str, "\tdOR:%d", DataInt[2]);
				i=11;
				break;
			}
#endif
		case 11:
			if(Info_en.C_Vts_M1==1){
				size=sprintf(str, "\tV1C:%.0f", DataDouble[0]);
				i=12;
				break;
			}
	case 12:
			if(Info_en.C_Vts_M2==1){
				size=sprintf(str, "\tV2C:%.0f", DataDouble[1]);
				i=13;
				break;
			}
			case 13:
			if(Info_en.C_Ang==1){
				size=sprintf(str, "\tAgC:%.4f", DataDouble[2]);
				i=14;
				break;
			}
		case 14:
			if(Info_en.C_AngModPi==1){
				size=sprintf(str, "\tAMC:%.4f", DataDouble[3]);
				i=15;
				break;
			}
		case 15:
			if(Info_en.C_x==1){
				size=sprintf(str, "\tXrC:%.0f", DataDouble[4]);
				i=16;
				break;
			}
		case 16:
			if(Info_en.C_y==1){
				size=sprintf(str, "\tYrC:%.0f", DataDouble[5]);
				i=17;
				break;
			}
		case 17:
			if(Info_en.C_Vmax_M==1){
				size=sprintf(str, "\tVmC:%.0f", DataDouble[6]);
				i=18;
					break;
			}
		case 18:
			if(Info_en.C_ErrDis==1){
				size=sprintf(str, "\tEdC:%.0f", DataDouble[7]);
				i=19;
				break;
			}
		case 19:
			if(Info_en.C_ErrAng==1){
				size=sprintf(str, "\tEaC:%.4f", DataDouble[8]);
				i=20;
				break;
			}
		case 20:
			if(Info_en.C_Err_x==1){
				size=sprintf(str, "\tExC:%.0f", DataDouble[9]);
				i=21;
				break;
			}
		case 21:
			if(Info_en.C_Err_y==1){
				size=sprintf(str, "\tEyC:%.0f", DataDouble[10]);
				i=22;
				break;
			}
		case 22:
			if(Info_en.R_Vts_M1==1){
				size=sprintf(str, "\tV1R:%.0f", DataDouble[11]);
				i=23;
				break;
			}
		case 23:
			if(Info_en.R_Vts_M2==1){
				size=sprintf(str, "\tV2R:%.0f", DataDouble[12]);
				i=24;
				break;
			}
			case 24:
			if(Info_en.R_Ang==1){
				size=sprintf(str, "\tAgR:%.4f", DataDouble[13]);
				i=25;
				break;
			}
		case 25:
			if(Info_en.R_AngModPi==1){
				size=sprintf(str, "\tAMR:%.4f", DataDouble[14]);
				i=26;
				break;
			}
		case 26:
			if(Info_en.R_x==1){
				size=sprintf(str, "\tXrR:%.0f", DataDouble[15]);
				i=27;
				break;
			}
		case 27:
			if(Info_en.R_y==1){
				size=sprintf(str, "\tYrR:%.0f", DataDouble[16]);
				i=28;
				break;
			}
		case 28:
				if(Info_en.R_ErrDis==1){
				size=sprintf(str, "\tEdR:%.0f", DataDouble[17]);
				i=29;
				break;
			}
		case 29:
			if(Info_en.R_ErrAng==1){
				size=sprintf(str, "\tEaR:%.4f", DataDouble[18]);
				i=30;
				break;
			}
		case 30:
			if(Info_en.R_Err_x==1){
				size=sprintf(str, "\tExR:%.0f", DataDouble[19]);
				i=31;
				break;
			}
		case 31:
			if(Info_en.R_Err_y==1){
				size=sprintf(str, "\tEyR:%.0f", DataDouble[20]);
				i=32;
				break;
			}
		case CARTE_STATE:
			#ifdef _PATHFIND_H_
			if(Info_en.carte==1){
				size=printCarte(str,&i);
				break;
			}
			#endif
		default:
			size=sprintf(str,"\n");
			i=0;
				FlagUart.U1Tx=0;	//envele l'aquitement d'émission
//				FlagUart.U2Tx=0;	//envele l'aquitement d'émission

		}
//		#ifndef _UART2_TX_PSTVTS_
			for(j=0;j<size;j++) U1Tx_string[j]=str[j];
			U1Tx_size=size;
			IEC0bits.U1TXIE	= 1;	// /Enable Transmisssion Interrupts 1
/*		#else
			for(j=0;j<size;j++) U2Tx_string[j]=str[j];
			U2Tx_size=size;
			IEC1bits.U2TXIE	= 1;//Enable Transmisssion Interrupts 2
		#endif*/
}


void uxtx_ComeOne(void)
{	
	int j=0;
	int size;
	static int i=0;
//	static int size_last=0;
	static long int DataLInt[7];
	static int DataInt[3];
	static double DataDouble[21];
	char str[UxTx_length];

if( IEC0bits.U1TXIE==0){
	switch(i){
		case 0:
			DataLInt[1]=Consigne.Vts_d;// long int, contsigne vitesse de deplacement
			DataLInt[2]=Consigne.Vts_a;// long int, contsigne vitesse angulaire
			DataLInt[3]=Consigne.Dis;// long int, consigne de distance
			DataLInt[4]=Reel.Vts_d;// long int, 
			DataLInt[5]=Reel.Vts_a;// long int	
			DataLInt[6]=Reel.Dis; // long int
			DataInt[0]=Consigne.mode;// int, mode de déplacement
#ifdef _MESURE_DISTANCE_H_
			DataInt[1]=Consigne.d_Obst;// int
			DataInt[2]=Reel.d_Obst;// int
#endif
			DataDouble[0]=Consigne.Vts_M1;// double
			DataDouble[1]=Consigne.Vts_M2;// double
			DataDouble[2]=Consigne.Ang;// double
			DataDouble[3]=Consigne.AngModPi;// double
			DataDouble[4]=Consigne.x;// double
			DataDouble[5]=Consigne.y;// double
			DataDouble[6]=Consigne.Vmax_M;// double
			DataDouble[7]=Consigne.ErrDis;// double
			DataDouble[8]=Consigne.ErrAng;// double
			DataDouble[9]=Consigne.Err_x;// double
			DataDouble[10]=Consigne.Err_y;// double
			DataDouble[11]=Reel.Vts_M1;// double
			DataDouble[12]=Reel.Vts_M2;// double
			DataDouble[13]=Reel.Ang;// double
			DataDouble[14]=Reel.AngModPi;// double
			DataDouble[15]=Reel.x;// double
			DataDouble[16]=Reel.y;// double
			DataDouble[17]=Reel.ErrDis;// double
			DataDouble[18]=Reel.ErrAng;// double
			DataDouble[19]=Reel.Err_x;// double
			DataDouble[20]=Reel.Err_y;// double
		case 1:
			if(Info_en.C_Vts_d==1){
				size=sprintf(str, "VdC:%ld", DataLInt[1]);//envoie de la consigne vitesse de deplacement
				i=2;
				break;
			}
		case 2:
			if(Info_en.C_Vts_a==1){
				size=sprintf(str, "VaC:%ld", DataLInt[2]);//envoie de la consigne vitesse angulaire
				i=3;
				break;
			}
		case 3:
			if(Info_en.C_Dis==1){
				size=sprintf(str, "DsC:%ld", DataLInt[3]);
				i=4;
				break;
			}
		case 4:
			if(Info_en.R_Vts_d==1){
				size=sprintf(str, "VdR:%ld", DataLInt[4]);
				i=5;
				break;
			}
		case 5:
			if(Info_en.R_Vts_a==1){
				size=sprintf(str, "VaR:%ld", DataLInt[5]);
				i=6;
				break;
			}
		case 6:
			if(Info_en.R_Dis==1){
				size=sprintf(str, "DsR:%ld", DataLInt[6]);
				i=7;
				break;
			}
		case 7:
			if(Info_en.C_mode==1){
				size=sprintf(str, "MdC:%d", DataInt[0]);
#ifdef _MESURE_DISTANCE_H_
				i=11;
#else
				i=8;
#endif
				break;
			}
#ifdef _MESURE_DISTANCE_H_
		case 8:
			if(Info_en.C_d_Obst==1){
				size=sprintf(str, "dOC:%d", DataInt[1]);
				i=10;
				break;
			}
		case 10:
			if(Info_en.R_d_Obst==1){
				size=sprintf(str, "dOR:%d", DataInt[2]);
				i=11;
				break;
			}
#endif
		case 11:
			if(Info_en.C_Vts_M1==1){
				size=sprintf(str, "V1C:%.0f", DataDouble[0]);
				i=12;
				break;
			}
		case 12:
			if(Info_en.C_Vts_M2==1){
				size=sprintf(str, "V2C:%.0f", DataDouble[1]);
				i=13;
				break;
			}
		case 13:
			if(Info_en.C_Ang==1){
				size=sprintf(str, "AgC:%.4f", DataDouble[2]);
				i=14;
				break;
			}
		case 14:
			if(Info_en.C_AngModPi==1){
				size=sprintf(str, "AMC:%.4f", DataDouble[3]);
				i=15;
				break;
			}
		case 15:
			if(Info_en.C_x==1){
				size=sprintf(str, "XrC:%.0f", DataDouble[4]);
				i=16;
				break;
			}
		case 16:
			if(Info_en.C_y==1){
				size=sprintf(str, "YrC:%.0f", DataDouble[5]);
				i=17;
				break;
			}
		case 17:
			if(Info_en.C_Vmax_M==1){
				size=sprintf(str, "VmC:%.0f", DataDouble[6]);
				i=18;
					break;
			}
		case 18:
			if(Info_en.C_ErrDis==1){
				size=sprintf(str, "EdC:%.0f", DataDouble[7]);
				i=19;
				break;
			}
		case 19:
			if(Info_en.C_ErrAng==1){
				size=sprintf(str, "EaC:%.4f", DataDouble[8]);
				i=20;
				break;
			}
		case 20:
			if(Info_en.C_Err_x==1){
				size=sprintf(str, "ExC:%.0f", DataDouble[9]);
				i=21;
				break;
			}
		case 21:
			if(Info_en.C_Err_y==1){
				size=sprintf(str, "EyC:%.0f", DataDouble[10]);
				i=22;
				break;
			}
		case 22:
			if(Info_en.R_Vts_M1==1){
				size=sprintf(str, "V1R:%.0f", DataDouble[11]);
				i=23;
				break;
			}
		case 23:
			if(Info_en.R_Vts_M2==1){
				size=sprintf(str, "V2R:%.0f", DataDouble[12]);
				i=24;
				break;
			}
			case 24:
			if(Info_en.R_Ang==1){
				size=sprintf(str, "AgR:%.4f", DataDouble[13]);
				i=25;
				break;
			}
		case 25:
			if(Info_en.R_AngModPi==1){
				size=sprintf(str, "AMR:%.4f", DataDouble[14]);
				i=26;
				break;
			}
		case 26:
			if(Info_en.R_x==1){
				size=sprintf(str, "XrR:%.0f", DataDouble[15]);
				i=27;
				break;
			}
		case 27:
			if(Info_en.R_y==1){
				size=sprintf(str, "YrR:%.0f", DataDouble[16]);
				i=28;
				break;
			}
		case 28:
				if(Info_en.R_ErrDis==1){
				size=sprintf(str, "EdR:%.0f", DataDouble[17]);
				i=29;
				break;
			}
		case 29:
			if(Info_en.R_ErrAng==1){
				size=sprintf(str, "EaR:%.4f", DataDouble[18]);
				i=30;
				break;
			}
		case 30:
			if(Info_en.R_Err_x==1){
				size=sprintf(str, "ExR:%.0f", DataDouble[19]);
				i=31;
				break;
			}
		case 31:
			if(Info_en.R_Err_y==1){
				size=sprintf(str, "EyR:%.0f", DataDouble[20]);
				i=32;
				break;
			}
		default:
			size=sprintf(str,"\n");
			i=0;
				FlagUart.U1Tx=0;	//envele l'aquitement d'émission
	}		
	str[size]='\n';
	size=size+1;
	i=0;
	FlagUart.U1Tx=0;	//envele l'aquitement d'émission
	Info_en.Com=0;
	Info_en.ComOne=0;
	aff_Info_en_Tx(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
	for(j=0;j<size;j++) U1Tx_string[j]=str[j];
	U1Tx_size=size;
	IEC0bits.U1TXIE	= 1;	// /Enable Transmisssion Interrupts 1
}
}





void uxtx_pstvts_char(unsigned long temps)
{	
//if(Info_en.Com==1 || Info_en.ComOne==1){
//#ifndef _UART2_TX_PSTVTS_
	//if(FlagUart.U1Tx==1)
/*#else
	if(FlagUart.U2Tx==1)
#endif*/
	if((Info_en.Com==1 && FlagUart.U1Tx==1 && IEC0bits.U1TXIE==0)){
		uxtx_Com(temps);
	}
	else{
		if(Info_en.ComOne==1 && IEC0bits.U1TXIE==0){
			uxtx_ComeOne();
		}
	}
}

















void uxtx_Data(char * UxTx_string, int *size, int Data)
{
	char str[12];
	if(FlagUart.U1Tx==1)
	{
		(*size)=sprintf(str, "%d", Data)+1;
		strcat(str,"\n");
		strcpy(UxTx_string,str);
		FlagUart.U1Tx=0;
		IEC0bits.U1TXIE	= 1;//Enable Transmisssion Interrupts 1
	}
}




void  fctUartTx(char string[UxTx_length]){
/*#ifndef _UART2_TX_SERVO_
		while(FlagUart.U1Tx!=1); // attente libération de l'UART1
		U1Tx_size=sprintf(U1Tx_string,string);
		FlagUart.U1Tx=0;	//envele l'aquitement d'émission
		IEC0bits.U1TXIE	= 1;//Enable Transmisssion Interrupts 1
		while(FlagUart.U1Tx!=1);*/
//#else
		while(FlagUart.U2Tx!=1); // attente libération de l'UART2
		U2Tx_size=sprintf(U2Tx_string,string);
		FlagUart.U2Tx=0;	//envele l'aquitement d'émission
		FlagUart.U2Tx_wait=0; 
		IEC1bits.U2TXIE	= 1;//Enable Transmisssion Interrupts 2
		while(FlagUart.U2Tx!=1);
//	#endif
}









