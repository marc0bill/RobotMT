/*
Club Robot - Polytech Marseille

Fonctions de gestions des collisions et reparage des autres robots

Révision:     	$Rev: $
Auteur:       	$Author: $
Date révision: 	$Date:  $
projet:      	$URL: $


*/
#include "header.h"

#ifdef _MESURE_DISTANCE_H_
#include "moduleI2C.h"
#include "move.h"
#include "trigo.h"
#include <math.h>
#include "uartTx.h"

struct Struct_Dis Dis;

double distance_bord(double Angle){
	double d_bordX=5000000.0,	d_bordY=5000000.0;
// Il faut prendre le modulo de l'angle ...
	if(-C_pi2<Angle && Angle<C_pi2 ) d_bordX = (x_max-Reel.x)/cos(Angle);
	if(C_pi2<Angle && Angle<C_3pi2 ) d_bordX = -Reel.x/cos(Angle);
	
	if(0<Angle && Angle<C_pi ) d_bordY = (y_max-Reel.y)/sin(Angle);
	if(C_pi<Angle && Angle<C_2pi ) d_bordY = -Reel.y/sin(Angle);
	
	if(d_bordX>=d_bordY) return d_bordY;
	else  return d_bordX;
}


void mesure_distance(void)
{
	int UltraSon_mesure[2];
	static char UltraSon_last[2];
	char err_i2c_ar=0; // 1 si erreur de com i2c, -1 si nouvelle valeur de mesure
	//IEC1bits.U2TXIE	= 1;

UltraSon_mesure[0]=mesure_ultrason_1(ADDRESS_US_av); //module Avant
UltraSon_mesure[1]=300;
err_i2c_ar=-1;
//err_i2c_ar=mesure_ultrason_2(ADDRESS_US_ar,UltraSon_mesure+1); //module Arriere


//	mesure_ultrason(0xE4,UltraSon+1); //module maison//module Arrière :

// Calcul d'une valeur moyen sur 2 points si une nouvelle valeur de distance est mesuré
	if(UltraSon_mesure[0]>0){
		Dis.obstAv_uS=UltraSon_mesure[0];//+UltraSon_last[0])/2;
		UltraSon_last[0]=UltraSon_mesure[0];
	}
	if(err_i2c_ar==-1){
		Dis.obstAr_uS=(UltraSon_mesure[1]+UltraSon_last[1])/2;
		UltraSon_last[1]=UltraSon_mesure[1];
	}

	Dis.bordAv=distance_bord(Reel.AngModPi);
	Dis.bordAr=distance_bord(modulo2pi(-Reel.AngModPi));
}


#endif

