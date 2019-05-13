/*
Club Robot - Polytech Marseille
Eurobot 2011


Fonctions sur les angles

Révision:     	$Rev: $
Auteur:       	$Author: $
Date révision: 	$Date:  $
projet:      	$URL: $



*/
#include "header.h"
#include "trigo.h"
#include <math.h>

double modulo2pi(double Ang)
{
// Retourne l'angle module 2pi
// Compris entre -pi/2 et 3pi/2
	while(Ang<-C_pi2 || Ang>C_3pi2)
	{
		if(Ang<-C_pi2) 		Ang=Ang+C_2pi;
		else if(Ang>C_3pi2)	Ang=Ang-C_2pi;
	}
	return Ang;
}

double diffAng(double Ang1, double Ang2)
{
// Retourne la difference des angles module 2pi
/*	Ang1=modulo2pi(Ang1);
	Ang2=modulo2pi(Ang2);
	return Ang1-Ang2;
*/
	return modulo2pi(Ang1-Ang2);
}


char get_orientation(double Angle){
	if(-C_pi2<=Angle && Angle<-C_pi4)	return 4;
	if(-C_pi4<=Angle && Angle<C_pi4)	return 1;
	if(C_pi4<=Angle && Angle<C_3pi4)	return 2;
	if(C_3pi4<=Angle && Angle<C_5pi4)	return 3;
	if(C_5pi4<=Angle && Angle<C_3pi2)	return 4;
	return 0;
}


int signV(double dx, double dy, double Angle)
{
	int sign=0;
	if(-C_pi2<=Angle && Angle<-C_pi4)
	{
		if(dy<0) sign=1;
		else sign=-1;
		return sign;
	}
	if(-C_pi4<=Angle && Angle<C_pi4)
	{
		if(dx>0) sign=1;
		else sign=-1;
		return sign;
	}
	if(C_pi4<=Angle && Angle<C_3pi4)
	{
		if(dy>0) sign=1;
		else sign=-1;
		return sign;
	}
	if(C_3pi4<=Angle && Angle<C_5pi4)
	{
		if(dx<0) sign=1;
		else sign=-1;
		return sign;
	}
	if(C_5pi4<=Angle && Angle<C_3pi2)
	{
		if(dy<0) sign=1;
		else sign=-1;
		return sign;
	}
	return sign;
}


