/*
Club Robot - Polytech Marseille


Révision:     	$Rev: $
Auteur:       	$Author: $
Date révision: 	$Date:  $
projet:      	$URL: $

*/
#ifndef _PATHFIND_H_
#define _PATHFIND_H_

#include "header.h"
//#include "mesure_distance.h"
#include "timer.h"
#include "trigo.h"

#define LO 1
#define LF 2
#define OBSTACLE 3
#define DEPART 4
#define ARRIVE 5
#define CHEMIN 6
#define VIDE 0
#define CARRE 1

#define DISVAR 20 //Distance de detection d'obstacle

//#define X_DEPART 0
//#define Y_DEPART 0
//#define X_ARRIVE 9
//#define Y_ARRIVE 9

#define X_MAX LARG_MAX/CARRE_DIS
#define Y_MAX HAUT_MAX/CARRE_DIS
#define CI_MAX (X_MAX+Y_MAX)*5

//VITESSE
#define NB_DESTINATION 8

#define INT_MAX 32760

struct SN{

	int ix;
	int iy;
	int G;
	int H;
	int F;
	char List; // 0=none, 1=LO, 2=LF, 3=obstacle, 4=depart, 5=arrive, 6=chemin
};

extern char CARTE[Y_MAX][X_MAX];

extern struct SN map[Y_MAX][X_MAX];

//extern int depart_x, depart_y;

void init_map(char[Y_MAX][X_MAX]);

void init_pathfind(double, double, double);

void ajouter_obs(char[Y_MAX][X_MAX], int, int);

void supprimer_obs(char[Y_MAX][X_MAX], int, int);

void reset_obs(char[Y_MAX][X_MAX]);

void calculF(int, int, int, int);

int EcrireChemin(int, int, int, int, int);

int Pathfind(int, int, int, int, int);

void Pathfind2(int, int, int, int, int, int);

int arrond(double);


#endif

