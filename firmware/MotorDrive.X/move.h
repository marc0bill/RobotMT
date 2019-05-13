/*********************************************************************/
/*              Header File for move module Library routines          */
/*********************************************************************/
/*
Révision:     	$Rev: $
Auteur:       	$Author: $
Date révision: 	$Date:  $
projet:      	$URL: $
*/



#ifndef MOVE_H
#define MOVE_H

#define x_max 		3000.0
#define y_max 		2000.0

struct Struct_PstVts{
	signed long Vts_d;
	signed long Vts_a;
	double Vts_M1;
	double Vts_M2;
	signed long Dis; // en mm
	double Ang;
	double AngModPi;
	double x; // en mm
	double y; // en mm
	double Vmax_M;
//	double Acc_M;
	double ErrDis;
	double ErrAng;
	double Err_x;
	double Err_y;
	int mode;
};

struct Struct_TablePst{
	int nb;
	signed long Dis[nbPst]; // en mm
	double Ang[nbPst]; // en rad
	double x[nbPst]; // en mm
	double y[nbPst]; // en mm
	signed long Vmax_M[nbPst];
//	int Acc_M[nbPst];
	int mode[nbPst];
	int wait[nbPst]; // en s

//	int d_Obst[nbPst];
	double ErrAng[nbPst];
	double Err_x[nbPst];
	double Err_y[nbPst];

};

struct Struct_FlagMove{
	int Pst;//Indique que le robot est arrive en position
	int Start;
	char Ordre;
// 0 : pas d'ordre
// 1 : Start
// 2 : Stop
// 3 : Restart
// 4 : Continu
// 5 : Telecommande
	int Avance;  //1 : robot avance & -1 : robot recule
	int CollRob; //1 : Indique une collision
};

extern struct Struct_TablePst TablePst;
extern struct Struct_PstVts Consigne;
extern struct Struct_PstVts Reel;
extern struct Struct_FlagMove FlagMove;

extern signed long VMAX_M;

extern void init_move(void);
extern void aff_Consigne(void);

#ifdef _PATHFIND_H_
extern void demo_pathfinding(void);
#endif


#endif    /*MOVE_H  */
