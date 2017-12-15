/*
Club Robot - Polytech Marseille

Fonctions de mesure des distances du robot
Actuellement n'utilise que les ultrations pour les obstacles
Et calcul la distance des bords en face de lui

Révision:     	$Rev: $
Auteur:       	$Author: $
Date révision: 	$Date:  $
projet:      	$URL: $


*/


#ifndef _MESURE_DISTANCE_H_
#define _MESURE_DISTANCE_H_

#define d_bord_min 250000.0

struct Struct_Dis{
	int obstAv_uS; // en cm
	int obstAr_uS; // en cm
	double bordAv; // en um
	double bordAr; // en um
};


void mesure_distance(void);
extern struct Struct_Dis Dis;

#endif



