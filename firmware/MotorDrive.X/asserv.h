/*
Club Robot - Polytech Marseille

Fonctions liées à l'asservisement des roues

Révision:     	$Rev: $
Auteur:       	$Author: $
Date révision: 	$Date:  $
projet:      	$URL: $

*/
#ifndef _ASSERV_H_
#define _ASSERV_H_


#define ADDRESS_ASSERV 0x100



// Permet d'identifier le signe des POSxCNT venant des QEI
#define POSxCNTmoy 0x8000 //en decimale 32768

// Permet de d'avoir les distances en mm
//#define Coeff_mm 0.00414567// Coeff_mm=2*pi*Rayon_Roue/(NbImpParTourDeRoue * 4)
// Application1 - petit moteur maxon :
// Rayon_Roue= 40
// NbImpParTour= 500*24
// Coeff_mm= 2*pi*40/(500*24*4)=251.327/48000=0.00523598775598298873077107230547
//
// Application2 - gros moteur maxon :
// Rayon_Roue= 40
// NbImpParTour= 500*36
// Coeff_mm= 2*pi*40/(500*36*4)=251.327/72000=0.00349065850398865915384738153698
//
// Application3 - gros moteur maxon - :
// Rayon_Roue= 38
// NbImpParTour= 500*36/1.5
// Coeff_mm= 2*pi*38/(500*4*36/1.25)=0,00414567

// Permet de d'avoir les angles en radian
//#define Coeff_a 0.0000161940234375 // Coeff_a=Coeff_mm/distance entre roue
// 8.72222/350000=0.00002492
// 0.00523598775598/203=0.000025793
//0.00414567/254=0,000016322
//0.00414567/256=0.0000161940234375

#define PWM_max 1000 //1998   //2*P1TPERVAL
//#define NB_IMP_TOUR_ROUE 14400//Nbimp*rapport_reduction=500*36/1.25

extern int nb_IT_PWM;

extern void asservisement_roue(double [2]);
extern void aff_vitesse_roue_progressif(double [2]);
extern void init_asserv(double,double,double,double,double,double,double,double,double,double,double,int,int,double,double,double,double,double,double);
extern void save_asserv(void);
extern void load_asserv(void);
extern void default_asserv(void);
#endif
