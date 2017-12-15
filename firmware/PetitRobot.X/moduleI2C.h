/*
Club Robot - Polytech Marseille

Fonctions de gestions des capteur ultra son

Révision:     	$Rev: $
Auteur:       	$Author: $
Date révision: 	$Date:  $
projet:      	$URL: $


*/


#ifndef _MODULEI2C_H_
#define _MODULEI2C_H_

extern struct Struct_Boussole Boussole;

struct Struct_Boussole{
	unsigned char  Val;
	int ValMean;
	//unsigned char  newVal_F:1;
	unsigned char  newVal_E;
	
};

char mesure_boussole(void);

//void init_ultrason(void);
void init_ultrason(unsigned char);
/*
init_ultrason permet d'initialiser les module OEM "MSU10".
Il regle simlement la porte des module a 1m50
*/

int mesure_ultrason_1(unsigned char);
/*
mesure_ultrason_1 permet d'effectuer la mesure de distance
grace au module OEM "MSU10".
La fonction renvoie :
soit -1 quand le resultat de mesure n'est pas pres
soit la distance mesure 

adresse : adresse du module
*/
//char mesure_ultrason_2(char, char *);
#endif

