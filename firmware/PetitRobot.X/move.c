/*
Club Robot - Polytech Marseille
Eurobot 2011


Fonctions de deplacement

Révision:     	$Rev: $
Auteur:       	$Author: $
Date révision: 	$Date:  $
projet:      	$URL: $



*/
#include "header.h"
#include "move.h"
#include "timer.h"
//Variable définie en extern
struct Struct_PstVts Consigne;
struct Struct_PstVts Reel;
struct Struct_TablePst TablePst;
struct Struct_FlagMove FlagMove;

signed long VMAX_M = 500;

void init_Pst(void)
{
	Consigne.Vts_d=0;
	Consigne.Vts_a=0;
	Consigne.Vts_M1=0;
	Consigne.Vts_M2=0;
	Consigne.Dis=DEPARRT_ANG;
	Consigne.AngModPi=DEPARRT_ANG;
	Consigne.x=DEPART_X;
	Consigne.y=DEPART_Y;
	Consigne.Vmax_M=0;
//	Consigne.Acc_M=100;	// A DEFINIR
	Consigne.mode=TablePst.mode[0];
	Consigne.ErrDis=ERR_XYm;	// Erreur de distance toléré : mode 2
	Consigne.ErrAng=ERR_ANGm;		// Erreur d'angle toléré : mode 2-4
	Consigne.Err_x=ERR_XYm;		// Erreur sur x toléré : mode 3
	Consigne.Err_y=ERR_XYm;		// Erreur sur y toléré : mode 3
#ifdef _MESURE_DISTANCE_H_
	Consigne.d_Obst=D_OBSm;	// distance a partir de la quel le robot s'arret s'il voit un obstrable
							// ATTENTION : en cm !!!
	Reel.d_Obst=80.0;
#endif

	Reel.Vts_d=0;
	Reel.Vts_a=0;
	Reel.Vts_M1=0;
	Reel.Vts_M2=0;
	Reel.Dis=0;
	Reel.Ang=DEPARRT_ANG;
	Reel.AngModPi=DEPARRT_ANG;
	Reel.x=DEPART_X;
	Reel.y=DEPART_Y;
	Reel.Vmax_M=Consigne.Vmax_M;
//	Reel.Acc_M=Consigne.Acc_M;
	Reel.mode=-1;//PAS DE SENS
	Reel.ErrDis=0.0;
	Reel.ErrAng=0.0;
	Reel.Err_x=0.0;
	Reel.Err_y=0.0;
}



// Initialisation des structures indiquant la position actuelle du robot et sa consigne
void init_move(void)
{
#ifdef _PATHFIND_H_
	init_map(CARTE);
	init_pathfind(DEPART_X, DEPART_Y, DEPARRT_ANG);
#else
//							0		 1		2		3		4		5		6		7		8		9		10		11		12		13		14		15		16		17		18		19		20		21		22		23		24		25
	signed long Dis[26]=	{0 		, 0		, 0 	, 0		, 0		, 0		, 0		, 0		, 0		, 0 	, 0		, 0		, 0		, 0		, 0		, 0		, 0 	, 0		, 0		, 0		, 0		, 0		, 0		, 0 	, 0		, 0		}; // en mm
	double Ang[26]=		{0.0	, 0.0	, C_pi2+C_2pi	, C_pi2	, C_pi	, C_3pi2, C_3pi2, 0.0	, 0.0	, 0.0	, 0.0	, 0.0	, 0.0	, 0.0	, 0.0	, 0.0	, 0.0	, 0.0	, 0.0	, 0.0	, 0.0	, 0.0	, 0.0	, 0.0	, 0.0	, 0.0	}; // en rad
	double x[26]=		{0.0	, 500.0 , 500.0 , 500.0	, 000.0	, 000.0	, 0.0	, 0.0	, 0.0	, 0.0	, 0.0	, 0.0	, 0.0	, 0.0	, 0.0	, 0.0	, 0.0	, 0.0	, 0.0	, 0.0	, 0.0	, 0.0	, 0.0	, 0.0	, 0.0	, 0.0	}; // en mm
	double y[26]=		{0.0	, 0.0	, 500.0 , 500.0 , 500.0	, 500.0	, 0.0	, 0.0	, 0.0	, 0.0	, 0.0	, 0.0	, 0.0	, 0.0	, 0.0	, 0.0	, 0.0	, 0.0	, 0.0	, 0.0	, 0.0	, 0.0	, 0.0	, 0.0	, 0.0	, 0.0	}; // en mm
	int mode[26]=		{0		, 5		, 4 	, 5		, 4		, 5		, 4		, 5		, 4		, 10 	, 0		, 0		, 0		, 0		, 0		, 0		, 0 	, 0		, 0		, 0		, 0		, 0		, 0		, 0 	, 0		, 0		};
	int wait[26]=		{0 		, 1000	, 1000 	, 1000	, 1000	, 1000	, 0		, 0		, 0		, 0 	, 0		, 0		, 0		, 0		, 0		, 0		, 0 	, 0		, 0		, 0		, 0		, 0		, 0		, 0 	, 0		, 0		}; // en s
//	signed long Vmax_M[nbPst]= 	{300  	, 300	, 200 	, 300	, 200	, 300	, 200	, 300	, 200	, 0 	, 0		, 0		, 0		, 0		, 0		, 0		, 0 	, 0		, 0		, 0		, 0		, 0		, 0		, 0 	, 0		, 0		};
//	int d_Obst[nbPst]=		{0		, 20	, 20	, 20	, 20	, 20	, 20 	, 20	, 20	, 0 	, 0		, 0		, 0		, 0		, 0		, 0		, 0 	, 0		, 0		, 0		, 0		, 0		, 0		, 0 	, 0		, 0		}; // ATTENTION : en cm !!!

// mode :	0 => Mode télécommande
//			1 => Vts_M1 = Vmax_M;
//			2 => Deplacement en distance et angle
//			3 => Deplacement (soit avance, soit recule) en x et y
//			4 => Ajustement de l'angle
//			5 => Avance en x et y
//			6 => Revule en x et y
//			10=> Arret PWM

	int i=0;

	TablePst.nb=9;
	for(i=0;i<TablePst.nb;i++)
	{
		TablePst.Dis[i]=Dis[i];
		if(Switch_Couleur==0)
		{
			TablePst.Ang[i]=Ang[i];
			TablePst.x[i]=x[i];;
		}
		else
		{
			TablePst.Ang[i]=C_pi-Ang[i];
			TablePst.x[i]=x_max-x[i];
		}
		TablePst.y[i]=y[i];

		TablePst.Vmax_M[i]=VCROISIERE;//Vmax_M[i];
		TablePst.mode[i]=mode[i];
		TablePst.wait[i]=wait[i];
/*
		TablePst.d_Obst[i]=D_OBSm;*/
		TablePst.ErrAng[i]=ERR_ANGm;
		TablePst.Err_x[i]=ERR_XYm;
		TablePst.Err_y[i]=ERR_XYm;
	}

	FlagMove.Pst=1;
	FlagMove.Start=0;
	FlagMove.Ordre=0;
	FlagMove.Avance=0;
	FlagMove.CollRob=0;
#endif

	init_Pst();
}

int aff_mode_1(int i, unsigned long * attente)
{
	if(i<TablePst.nb-1 && tempsjeux>=(*attente))
	{
		i++;
		Consigne.x=TablePst.x[i];
		Consigne.y=TablePst.y[i];
		Consigne.Ang=TablePst.Ang[i];
		Consigne.Dis=Consigne.Dis + TablePst.Dis[i];
		Consigne.Vmax_M=TablePst.Vmax_M[i];
		Consigne.mode=TablePst.mode[i];
#ifdef _MESURE_DISTANCE_H_
		Consigne.d_Obst=D_OBSm;
#endif
		Consigne.ErrAng=ERR_ANGm;
		Consigne.Err_x=ERR_XYm;
		Consigne.Err_y=ERR_XYm;
		FlagMove.Pst=0;
		*attente=tempsjeux+TablePst.wait[i];
	}
	return i;
}


int aff_mode(int i, unsigned long *attente)
{
	if(FlagMove.Pst==1)
	{
		Consigne.mode=10;
		if(i<TablePst.nb-1 && tempsjeux>=(*attente))
		{
			i++;
			Consigne.x=TablePst.x[i];
			Consigne.y=TablePst.y[i];
			Consigne.Ang=TablePst.Ang[i];
			Consigne.Dis=Consigne.Dis + TablePst.Dis[i];
			Consigne.Vmax_M=TablePst.Vmax_M[i];
			Consigne.mode=TablePst.mode[i];
#ifdef _MESURE_DISTANCE_H_
			Consigne.d_Obst=D_OBSm;
#endif
			Consigne.ErrAng=ERR_ANGm;
			Consigne.Err_x=ERR_XYm;
			Consigne.Err_y=ERR_XYm;
			FlagMove.Pst=0;
		}
	}
	else *attente=tempsjeux+TablePst.wait[i];
	return i;
}


int aff_mode_track(int i, unsigned long *attente)
{
	if(i<TablePst.nb-1 && tempsjeux>=(*attente))
	{
		i++;
		Consigne.x=TablePst.x[i];
		Consigne.y=TablePst.y[i];
		Consigne.Ang=TablePst.Ang[i];
		Consigne.Dis=Consigne.Dis + TablePst.Dis[i];
		Consigne.Vmax_M=VMAX_M;
		Consigne.mode=TablePst.mode[i];
#ifdef _MESURE_DISTANCE_H_
		Consigne.d_Obst=D_OBSm;
#endif
		Consigne.ErrAng=ERR_ANGm;
		Consigne.Err_x=ERR_XYm;
		Consigne.Err_y=ERR_XYm;
		FlagMove.Pst=0;
		*attente=tempsjeux+TablePst.wait[i];
	}
	
	return i;
}


/***
 * Fonction d'affectation des consignes
 * Consigne d'ordre qui peuvent être modifier par 
***/
void aff_Consigne(void)
{
	static int i=0;
	static unsigned long attente=0;
	switch(FlagMove.Ordre){
		case 1: // Start
			i=0;
			init_Pst();
			Brake12=0;
			FlagMove.Start=1;
                        FlagMove.Pst=1;
			break;
		case 2: // Stop
			Consigne.mode=10;
			Consigne.Vts_M1=0.0;
			Consigne.Vts_M2=0.0;
			Reel.Vts_M1=0.0;
			Reel.Vts_M2=0.0;
			P1DC1=0;
			P1DC2=0; 		// activation moteur Brake=0
			Brake12=1;
			break;
		case 3: // Restart
			i=0;
			Brake12=0;
			FlagMove.Start=1;
			FlagMove.Pst=1;
			break;
		case 4: // Continue
			Brake12=0;
			FlagMove.Pst=0;
			FlagMove.Start=1;
			Consigne.mode=TablePst.mode[i];
			break;
		case 5: // Telecommande
			Brake12=0;
			Consigne.mode=0;
			Consigne.Vmax_M=1000;
			break;
		default:
			break;
	}
	FlagMove.Ordre=0;	// Aquitement de l'ordre
	if(FlagMove.Start==1){
		if(Consigne.mode==1) i=aff_mode_1(i,&attente);
		else{
			if(Consigne.mode==7) i=aff_mode_track(i,&attente);
			else i=aff_mode(i,&attente);
		}
	}
}








