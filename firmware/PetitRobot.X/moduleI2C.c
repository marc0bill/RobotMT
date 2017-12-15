/*
Club Robot - Polytech Marseille

Fonctions de gestions des capteur ultra son

Révision:     	$Rev: $
Auteur:       	$Author: $
Date révision: 	$Date:  $
projet:      	$URL: $


*/

#include "header.h"
#ifdef _MESURE_DISTANCE_H_


#include "i2c.h"
#include "moduleI2C.h"
//#include "timer.h"

struct Struct_Boussole Boussole;

char mesure_boussole(void){
    unsigned char data;
    if(Boussole.newVal_E){
        if(lecture_reg_I2C(0XC0,1,&data) != 1){
            Boussole.Val = data;
            Boussole.ValMean = Boussole.ValMean*0.9 + ((int) data)*0.1;
            Boussole.newVal_E = 0;
            return 1;
        }
    }
    return 0;
}



/*void init_ultrason(void){
	//configuration portee = 150cm
	while(write_reg_i2c(ADDRESS_US_av,0X02,0x22));
//	while(write_reg_i2c(ADDRESS_US_ar,0X02,0x22));
}
 * */

void init_ultrason(unsigned char adresse){
	while(write_reg_i2c(adresse,0X02,0x22));
}

/******************************************************************************/
int mesure_ultrason_1(unsigned char adresse){
	static int etat=0;
	char err=0;
	char test=0;
	static char LSB_data;
	static char MSB_data;
	int data=-1;// on revoie -1 si le donnee n'est pas pret
	IdleI2C1();
	switch(etat){
		case 0: //debut de la mesure en cm
			err=write_reg_i2c(adresse,0X00,0x51);
			if(err!=1) etat++; // Si pas d'erreur : on continu
			break;
		case 1: //attente de fin de mesure
			err=lecture_reg_I2C(adresse,0x00,&test);
			if(test!=0xFF && err!=1)// Si pas d'erreur et l'uson repond : on continu
				etat++;
			break;
		case 2: //LSB de la mesure 
			err=lecture_reg_I2C(adresse,0x03,&LSB_data);
			if(err!=1) etat++; // Si pas d'erreur : on continu
			break;
		case 3: //MSB de la mesure 
			err=lecture_reg_I2C(adresse,0x02,&MSB_data);
			if(err!=1){// Si pas d'erreur :
				etat=0;  //on recommence
				data=(int) MSB_data;
				data=(data<<8)+ ((int) LSB_data);
			}
			break;
	}//end switch
	
	return data;
}
/******************************************************************************/
int mesure_ultrason_2(unsigned char adresse){
	static int etat=0;
	char err=0;
	char test=0;
	static char LSB_data;
	static char MSB_data;
	int data=-1;// on revoie -1 si le donnee n'est pas pret
	IdleI2C1();
	switch(etat){
		case 0: //debut de la mesure en cm
			err=write_reg_i2c(adresse,0X00,0x51);
			if(err!=1) etat++; // Si pas d'erreur : on continu
			break;
		case 1: //attente de fin de mesure
			err=lecture_reg_I2C(adresse,0x00,&test);
			if(test!=0xFF && err!=1)// Si pas d'erreur et l'uson repond : on continu
				etat++;
			break;
		case 2: //LSB de la mesure 
			err=lecture_reg_I2C(adresse,0x03,&LSB_data);
			if(err!=1) etat++; // Si pas d'erreur : on continu
			break;
		case 3: //MSB de la mesure 
			err=lecture_reg_I2C(adresse,0x02,&MSB_data);
			if(err!=1){// Si pas d'erreur :
				etat=0;  //on recommence
				data=(int) MSB_data;
				data=(data<<8)+ ((int) LSB_data);
			}
			break;
	}//end switch
	
	return data;
}
/******************************************************************************/
int mesure_ultrason_3(unsigned char adresse){
	static int etat=0;
	char err=0;
	char test=0;
	static char LSB_data;
	static char MSB_data;
	int data=-1;// on revoie -1 si le donnee n'est pas pret
	IdleI2C1();
	switch(etat){
		case 0: //debut de la mesure en cm
			err=write_reg_i2c(adresse,0X00,0x51);
			if(err!=1) etat++; // Si pas d'erreur : on continu
			break;
		case 1: //attente de fin de mesure
			err=lecture_reg_I2C(adresse,0x00,&test);
			if(test!=0xFF && err!=1)// Si pas d'erreur et l'uson repond : on continu
				etat++;
			break;
		case 2: //LSB de la mesure 
			err=lecture_reg_I2C(adresse,0x03,&LSB_data);
			if(err!=1) etat++; // Si pas d'erreur : on continu
			break;
		case 3: //MSB de la mesure 
			err=lecture_reg_I2C(adresse,0x02,&MSB_data);
			if(err!=1){// Si pas d'erreur :
				etat=0;  //on recommence
				data=(int) MSB_data;
				data=(data<<8)+ ((int) LSB_data);
			}
			break;
	}//end switch
	
	return data;
}
/*********************************************************************************
fonction de mesure Arriere
*/
/*
char mesure_ultrason_2(char adresse, char *LSB){
	static int etat=0;
	static unsigned long wait=0;
	char err=0;
	IdleI2C1();
	switch(etat){
		case 0	: //configuration portee = 70cm
			err=write_reg_i2c(adresse,0X02,0x21);
			wait=tempsjeux+65;
			etat++;
			break;
		case 1: //debut de la mesure en cm
			if(tempsjeux>wait){// attente de 65 ms	
				err=write_reg_i2c(adresse,0X00,0x51);
				wait=tempsjeux+65;
				etat++;
			}
			break;
		case 2: //LSB de la mesure 
			if(tempsjeux>wait){// attente de 65 ms	
				err=lecture_reg_I2C(adresse,0x03,LSB);
				etat=0;
				if(err==0){
					err=-1;
				}
			}
			break;
	}//end switch
	if(err==1){
		etat=0;
	}
	StopI2C1();
	return err;
}
*/
#endif

