/*
Club Robot - Polytech Marseille
Eurobot 2011


Fonctions asservissements

Révision:     	$Rev: $
Auteur:       	$Author: $
Date révision: 	$Date:  $
projet:      	$URL: $



*/
#include "header.h"
#include "asserv.h"
#include "pwm.h"
#include "move.h"
#include "trigo.h"
//#include "i2c.h"
#include <math.h>


#ifdef MOTEUR_SENS_INVERSE
	#define MOTEUR_AV -
#else
	#define MOTEUR_AV +
#endif

double Amax; // acceleration max en impulsion
double Err_Seuil_PID;
double KvPure;
double KvPID,Ai_v,Ad_v,Bd_v;
double KpD,KpA,a0i_p,a1i_p,b1i_p,a0d_p,a1d_p,b1d_p;
int nb_IT_PWM;

// Permet de d'avoir les distances en mm
double Coeff_mm;
// Permet de d'avoir les angles en radian
double Coeff_a;

double ErrDisMax=10.0;	//10mm




#ifdef ADDRESS_EEPROM
void save_asserv(void){
	int base=ADDRESS_ASSERV;

	save_double(Err_Seuil_PID,&base);
	save_double(Amax,&base);
	save_double(KvPure,&base);
	save_double(KvPID,&base);
	save_double(Ai_v,&base);
	save_double(Ad_v,&base);
	save_double(Bd_v,&base);


	save_double(KpD,&base);
	save_double(KpA,&base);
	save_double(a0i_p,&base);
	save_double(a1i_p,&base);
	save_double(b1i_p,&base);
	save_double(a0d_p,&base);
	save_double(a1d_p,&base);
	save_double(b1d_p,&base);

	save_double(Coeff_mm,&base);
	save_double(Coeff_a,&base);

	save_int(nb_IT_PWM,&base);

}


void load_asserv(void){
	int base=ADDRESS_ASSERV;

	Err_Seuil_PID=load_double(&base);
	Amax	= load_double(&base);
	KvPure	= load_double(&base);
	KvPID	= load_double(&base);
	Ai_v	= load_double(&base);
	Ad_v	= load_double(&base);
	Bd_v	= load_double(&base);

	KpD		= load_double(&base);
	KpA 	= load_double(&base);
	a0i_p	= load_double(&base);
	a1i_p	= load_double(&base);
	b1i_p	= load_double(&base);
	a0d_p	= load_double(&base);
	a1d_p	= load_double(&base);
	b1d_p	= load_double(&base);

	Coeff_mm= load_double(&base);
	Coeff_a	= load_double(&base);

	nb_IT_PWM=load_int(&base);
}
#endif




// Calcul des coefficient des correcteurs 
void init_asserv(double Te, double KvvPure, double KvvPID, double Tiv, double Tdv, double Av, double KppD, double KppA,double Tip, double Tdp, double Ap, int corr_type_v, int corr_type_p, double Seuil,double Acceleration,double Rayon_Roue, double Distance_Roue, double Rapport_Reduction, double Nb_imp)
{
// Permet de d'avoir les distances en mm
	Coeff_mm=2.0*C_pi*Rayon_Roue/(Rapport_Reduction*Nb_imp * 4.0);
// Permet de d'avoir les angles en radian
	Coeff_a=Coeff_mm/Distance_Roue; // Coeff_a=Coeff_mm/distance entre roue




	Err_Seuil_PID=Seuil;

	Amax=Acceleration;

	KvPure=KvvPure;
	KvPID=KvvPID;
	Ai_v=0.0;
	Ad_v=0.0;
	Bd_v=0.0;

	KpD=KppD;
	KpA=KppA;
	a0i_p=1;
	a1i_p=0;
	b1i_p=0;
	a0d_p=0;
	a1d_p=0;
	b1d_p=0;


	nb_IT_PWM=Te/T_IT_PWM;

	//PI  : corr_type_v=1
	//PID : corr_type_v=2
	if(corr_type_v==1 || corr_type_v==2)
		Ai_v=Te/(2.0*Tiv);
	if(corr_type_v==2)
	{
		//Ad_v= ??;
		//Bd_v= ??;
	}

	//PI  : corr_type_p=1
	//PID : corr_type_p=2
	if(corr_type_p==1 || corr_type_p==2)
	{
		a0i_p=Te/(2.0*Tip)+1;
		a1i_p=Te/(2.0*Tip)-1;
		b1i_p=1;
	}
	if(corr_type_p==2)
	{
		a0d_p=(Te+2*Tdp)/(Te+2*Ap*Tdp);
		a1d_p=(Te-2*Tdp)/(Te+2*Ap*Tdp);
		b1d_p=-(Te-2*Ap*Tdp)/(Te+2*Av*Tdp);
	}


}

void default_asserv(void){
	init_asserv(0.004,10.0 ,10.0 ,1.0,1.0,1.0,1.0,0.1,1.0,1.0,1.0,0,0,500.0,3.0,38.0,256.0,28.8,500.0);
}



// Fonction permettant de limiter l'acceleration
double limit_acc(double Vst_Mx, double Vst_Mx_new){
	if ((Vst_Mx_new - Vst_Mx) > Amax) {
		return Vst_Mx + Amax ;
	}	
	else {
		if ((Vst_Mx_new - Vst_Mx) < -Amax){
			return Vst_Mx - Amax ;
		}
	}
	return Vst_Mx_new;
}

// Fonction permettant de limiter 2 vitesses a une vitesse max (Vmax_M) en gardant le rapport de vitesse
void limit_vts(double S_M[2])
{
	double S_M0_abs=S_M[0];
	double S_M1_abs=S_M[1];
	double S_Max;
	if(S_M[0]<0) S_M0_abs=-S_M[0];
	if(S_M[1]<0) S_M1_abs=-S_M[1];
	if(S_M1_abs>S_M0_abs) S_Max=S_M1_abs;
	else S_Max=S_M0_abs;

	if(S_Max>Consigne.Vmax_M) 
	{
		S_M[0]=Consigne.Vmax_M*S_M[0]/S_Max;
		S_M[1]=Consigne.Vmax_M*S_M[1]/S_Max;
	}
}

void limit_vts_UV(double S_M[2], double V,double U,double valmax)
{
	double temp;
	
	if(U>valmax){
		if(V>3*U){
			U=valmax/3.0;
			V=2*U;
		}
		else{
			if(V<-3*U){
				U=valmax/3.0;
				V=-2*U;
			}
			else{
				U=valmax;
				V=0.0;
			}
		}
	}
	else{
		if(U<-valmax){
			if(V>-3*U){
				U=-valmax/3.0;
				V=-2*U;
			}
			else{
				if(V<3*U){
					U=-valmax/3.0;
					V=2*U;
				}
				else{
					U=-valmax;
					V=0.0;
				}
			}
		}
		else{
			temp=V+U;
			if(temp>valmax)	V=valmax-U;
			else{
				if(temp<-valmax)	V=-valmax-U;
				else{
						temp=V-U;
					if(temp>valmax)	V=valmax+U;
					else{if(temp<-valmax)	V=-valmax+U;}
				}
			}
		}
	}
	S_M[0]=V+U;
	S_M[1]=V-U;
}

// Fonction permettant de limiter la vitesse a une vitesse max, par exemple : Vmax_M
double valeurmax(double Vitesse,double valmax)
{
	if(Vitesse>valmax) return valmax;
	if (Vitesse<-valmax) return -valmax;
	return Vitesse;
}


void corr_vts(double ErrVts_M[2])
{
	double Err_M0,Err_M1;
	static double Err_z1_M0=0.0,Err_z1_M1=0.0;
	static double Ui_M0=0.0,Ui_M1=0.0;

	static double Ud_M0=0.0,Ud_M1=0.0;

	Err_M0=ErrVts_M[0];
	Err_M1=ErrVts_M[1];
	

	if(Err_M0>Err_Seuil_PID || Err_M0<-Err_Seuil_PID){
		Ui_M0= 0.0;
		Ud_M0= 0.0;
		Err_z1_M0=Err_M0;
		Err_M0 = KvPure*Err_M0;
	}
	else{
		Ui_M0 = Ai_v*(Err_M0 + Err_z1_M0) + Ui_M0;
		if(Ui_M0> 1000.0) Ui_M0=1000.0;
		if(Ui_M0<-1000.0) Ui_M0=-1000.0;
		Ud_M0 = Ad_v*(Err_M0 - Err_z1_M0) - Bd_v*Ud_M0;
		Err_z1_M0 = Err_M0;
		Err_M0 = KvPID*(Err_M0 + Ui_M0 + Ud_M0);
		
	}

	if(Err_M1>Err_Seuil_PID || Err_M1<-Err_Seuil_PID){
		Ui_M1= 0.0;
		Ud_M1= 0.0;
		Err_z1_M1=Err_M1;
		Err_M1 = KvPure*Err_M1;
	}
	else{
		Ui_M1 = Ai_v*(Err_M1 + Err_z1_M1) + Ui_M1;
		if(Ui_M1> 1000.0) Ui_M1=1000.0;
		if(Ui_M1<-1000.0) Ui_M1=-1000.0;
		Ud_M1 = Ad_v*(Err_M1 - Err_z1_M1) - Bd_v*Ud_M1;
		Err_z1_M1 = Err_M1;
		Err_M1 = KvPID*(Err_M1 + Ui_M1 + Ud_M1);
	}


	ErrVts_M[0] = MOTEUR_AV Err_M0;
	ErrVts_M[1] = MOTEUR_AV Err_M1;		
}


void position_vitesse_reel_roue(void)
{
	double dAng,dAng2,dDis,dx,dy,Ang_moy,K_dDis;
// Aquisition de l'information de vitesse des roues : codeurs+QEI
	if (POS1CNT<POSxCNTmoy) 
	{
		Reel.Vts_M1=POS1CNT;
	}
	else
	{
		Reel.Vts_M1=-POS1CNT;
		Reel.Vts_M1=-Reel.Vts_M1;
	}
	if (POS2CNT<POSxCNTmoy)
	{
		Reel.Vts_M2=POS2CNT;
	}
	else
	{
		Reel.Vts_M2=-POS2CNT;
		Reel.Vts_M2=-Reel.Vts_M2;
	}
	Reel.Vts_M2=MOTEUR_AV Reel.Vts_M2;
	Reel.Vts_M1=MOTEUR_AV Reel.Vts_M1;


// Réinitialisation du QEI
	POS1CNT=0;
	POS2CNT=0;

// Calcul de l'image de la vitesse moyenne
	Reel.Vts_d=(Reel.Vts_M1+Reel.Vts_M2)/2;
// Calcul de l'image de la vitesse angulaire
	Reel.Vts_a=Reel.Vts_M1-Reel.Vts_M2;
// Calcul de l'image de la distance
	dDis=Reel.Vts_d*Coeff_mm;
	Reel.Dis=Reel.Dis+dDis;
// Calcul de l'image de l'angule
	dAng=Reel.Vts_a*Coeff_a;
	Reel.Ang=Reel.Ang+dAng;
	Reel.AngModPi=modulo2pi(Reel.Ang);
// Calcul des coordonnes x-y-teta
	dAng2=dAng/2;
	Ang_moy=Reel.Ang-dAng2;
	if(dAng2==0) 	K_dDis=dDis;// Pour éviter la division par zéro
	else 			K_dDis=dDis*sin(dAng2)/dAng2;
	dx=K_dDis*cos(Ang_moy);
	dy=K_dDis*sin(Ang_moy);
	Reel.x=Reel.x+dx;
	Reel.y=Reel.y+dy;
}



void aff_vitesse_roue(double alpha_M[2])
{
	signed a0=alpha_M[0];
	signed a1=alpha_M[1];
	if (alpha_M[0]>=0)
	{
		if (a0<PWM_max) P1DC1=a0;
		else P1DC1=PWM_max;
		SENS_M1=0x0;
	}
	else
	{
		if (-a0<PWM_max) P1DC1=-a0;
		else P1DC1=PWM_max;
		SENS_M1=0x1;
	}
	if (alpha_M[1]>=0)
	{
		if (a1<PWM_max) P1DC2=a1;
		else P1DC2=PWM_max;
		SENS_M2=0x0;
	}
	else
	{
		if (-a1<PWM_max) P1DC2=-a1;
		else P1DC2=PWM_max;
		SENS_M2=0x1;
	}
}

// Fonction de calcul de l'erreur de possition (consigne de vitesse des 2 moteurs) pour le mode de déplacement 3
// mode 3 : le robot doit arrivé à une position avec comme consigne : x,y.
// L'angle est calculé par cette fonction pour visé la position x,y voulu.
// mode 3 parfaitement fonctionnel
void err_pst_xy(double ErrPst_M[2],int AvRe)
{
	double U,V,dx,dy,dAng2,sigDis,vlim_M1,vlim_M2;
	dx=(Consigne.x-Reel.x);
	dy=(Consigne.y-Reel.y);
	
	switch(AvRe){
		case 0 : 	//C'est la fonction qui deside si le robot doit avance ou reculer
			sigDis=signV(dx,dy,Reel.AngModPi);
			break;
		case 1 : 	// Le robot avance
			sigDis=1;
			break;
		case -1:	// Le robot recule
			sigDis=-1;
			break;
	}
	FlagMove.Avance=sigDis;

	if(dx>ErrDisMax) dAng2=atan(dy/dx);
	else{
		if(dx<-ErrDisMax) dAng2=pi+atan(dy/dx);
		else{
			if(dy>0.0) dAng2=C_pi2;
			else dAng2=-C_pi2;
		}
	}
	if(sigDis<0) dAng2=pi+dAng2;
	dAng2=diffAng(dAng2,Reel.Ang)/2;
	U=dAng2/Coeff_a;
	if(dAng2==0) 	V=sqrt(dx*dx+dy*dy)/Coeff_mm;// Pour éviter la division par zéro
	else 			V=sqrt(dx*dx+dy*dy)*dAng2/(Coeff_mm*sin(dAng2));
	if(sigDis<0) V=-V;

// Actuellement utile au rapport d'erreur. Non utilisé pour l'asservissement
	Reel.ErrDis=V;
	Reel.ErrAng=dAng2*2.0;
	Reel.Err_x=dx;
	Reel.Err_y=dy;

	//pour le debug :
//P1DC1=0;
//P1DC2=0;

//vlim[mm/s]=sqrt(distance A parcourir [mm] * acceleration [mm/s^2])
//vlim[imp]=sqrt(distance A parcourir [imp] * acceleration [imp])
	vlim_M1=sqrt(Amax*fabs(V+U));
	vlim_M2=sqrt(Amax*fabs(V-U));


// Correcteur de position
	V=KpD*V;
	U=KpA*U;
//Limitation de la vitesse maximum
	limit_vts_UV(ErrPst_M,V,U,Consigne.Vmax_M);
//	V=valeurmax(V,Consigne.Vmax_M);
//	U=valeurmax(U,Consigne.Vmax_M);
//	ErrPst_M[0]=V+U;
//	ErrPst_M[1]=V-U;

//Limitation de la vitesse en fonction de l'acceleration autorisé et la distance
	ErrPst_M[0]=valeurmax(ErrPst_M[0],vlim_M1);
	ErrPst_M[1]=valeurmax(ErrPst_M[1],vlim_M2);
//Limitation de l'acceleration
	Consigne.Vts_M1=limit_acc(Consigne.Vts_M1,ErrPst_M[0]);//ErrPst_M[0];
	Consigne.Vts_M2=limit_acc(Consigne.Vts_M2,ErrPst_M[1]);//ErrPst_M[1];
}





// Fonction de calcul de l'erreur de possition (consigne de vitesse des 2 moteurs) pour le mode de déplacement 4
// mode 4 : le robot tourne de l'angle Consigne.Ang.
void err_pst_ang(double ErrPst_M[2])
{
	double vlim_M;
	Reel.ErrAng=Consigne.Ang-Reel.Ang;
	ErrPst_M[0]=(Reel.ErrAng)/Coeff_a;
/*
vlim[mm/s]=sqrt(distance A parcourir [mm] * acceleration [mm/s^2])
vlim[imp]=sqrt(distance A parcourir [imp] * acceleration [imp])
*/
	vlim_M=sqrt(Amax*fabs(ErrPst_M[0]));
//Correcteur de position
	ErrPst_M[0]=KpA*ErrPst_M[0];
	ErrPst_M[1]=-ErrPst_M[0];
//Limitation de la vitesse maximum
	ErrPst_M[0]=valeurmax(ErrPst_M[0],Consigne.Vmax_M);
	ErrPst_M[1]=valeurmax(ErrPst_M[1],Consigne.Vmax_M);
//Limitation de la vitesse en fonction de l'acceleration autorisé et la distance
	ErrPst_M[0]=valeurmax(ErrPst_M[0],vlim_M);
	ErrPst_M[1]=valeurmax(ErrPst_M[1],vlim_M);
//Limitation de l'acceleration
	Consigne.Vts_M1=limit_acc(Consigne.Vts_M1,ErrPst_M[0]);//ErrPst_M[0];
	Consigne.Vts_M2=limit_acc(Consigne.Vts_M2,ErrPst_M[1]);//ErrPst_M[1];
}







void asservisement_roue(double ErrVts_M[2]){
    double ErrDis;
    double ErrPst_M[2];
    static double Cons0_Vts_M1;
    static double Cons0_Vts_M2;
    
    position_vitesse_reel_roue();
    switch (Consigne.mode){
        case 1:
            Consigne.Vts_M1=Consigne.Vmax_M;
            Consigne.Vts_M2=Consigne.Vmax_M;
#ifdef _CARTE_MOTEUR_V1_
            if((CapAvG==0 && CapAvD==0) || (CapArG==0 && CapArD==0)){
                FlagMove.Pst=1;
                Consigne.mode=10;
                Consigne.Vts_M1=0.0;
                Consigne.Vts_M2=0.0;
                P1DC1=0;
                P1DC2=0;
                if(Reel.AngModPi>-C_pi4 && Reel.AngModPi<C_pi4){
                    Reel.x=Consigne.x;
                    Reel.Ang=0.0;
                    Reel.AngModPi=0.0;
                }
                if(Reel.AngModPi>C_3pi4 && Reel.AngModPi<C_5pi4){
                    Reel.x=Consigne.x;
                    Reel.Ang=C_pi;
                    Reel.AngModPi=C_pi;
                }
                if(Reel.AngModPi>C_pi4 && Reel.AngModPi<C_3pi4){
                    Reel.y=Consigne.y;
                    Reel.Ang=C_pi2;
                    Reel.AngModPi=C_pi2;
                }
                if((Reel.AngModPi>C_5pi4 && Reel.AngModPi<C_3pi2) || (Reel.AngModPi>-C_pi2 && Reel.AngModPi<-C_pi4)){
                    Reel.y=Consigne.y;
                    Reel.Ang=-C_pi2;
                    Reel.AngModPi=-C_pi2;
                }
            }
#endif
            break;
        case 2:
            ErrDis=(Consigne.Dis-Reel.Dis)/Coeff_mm;
            Reel.ErrAng=(Consigne.Ang-Reel.Ang)/Coeff_a;
            if(ErrDis<=Consigne.ErrDis && ErrDis>=-Consigne.ErrDis && Reel.ErrAng<=Consigne.ErrAng && Reel.ErrAng>=-Consigne.ErrAng){
                FlagMove.Pst=1;
            }
            ErrPst_M[0]=KpD*ErrDis+KpA*Reel.ErrAng;
            ErrPst_M[1]=KpD*ErrDis-KpA*Reel.ErrAng;
            limit_vts(ErrPst_M);
            Consigne.Vts_M1=limit_acc(Consigne.Vts_M1,ErrPst_M[0]);//ErrPst_M[0];
            Consigne.Vts_M2=limit_acc(Consigne.Vts_M2,ErrPst_M[1]);//ErrPst_M[1];
            break;
        case 3://			3 => Deplacement (soit avance, soit recule) en x et y
            err_pst_xy(ErrPst_M,0);
            //if(ErrPst_M[0]<=Consigne.ErrDis && ErrPst_M[0]>=-Consigne.ErrDis && ErrPst_M[1]<=Consigne.ErrDis && ErrPst_M[1]>=-Consigne.ErrDis)
            if(Reel.Err_x<=Consigne.Err_x && Reel.Err_y<=Consigne.Err_y && Reel.Err_x>=-Consigne.Err_x && Reel.Err_y>=-Consigne.Err_y){
                FlagMove.Pst=1;
            }
            break;
        case 4://			4 => Ajustement de l'angle
            ErrDis=0;
            err_pst_ang(ErrPst_M);
            if(Reel.ErrAng<=Consigne.ErrAng && Reel.ErrAng>=-Consigne.ErrAng){
                FlagMove.Pst=1;
            }
            break;
        case 5://			5 => Avance en x et y
            err_pst_xy(ErrPst_M,1);
			if(Reel.Err_x<=Consigne.Err_x && Reel.Err_y<=Consigne.Err_y && Reel.Err_x>=-Consigne.Err_x && Reel.Err_y>=-Consigne.Err_y)
			{
				FlagMove.Pst=1;
			}
			break; 
		case 6://			6 => Revule en x et y
			err_pst_xy(ErrPst_M,-1);
			if(Reel.Err_x<=Consigne.Err_x && Reel.Err_y<=Consigne.Err_y && Reel.Err_x>=-Consigne.Err_x && Reel.Err_y>=-Consigne.Err_y)
			{
				FlagMove.Pst=1;
			}
			break;
		case 7://			5 => Avance en x et y
			Reel.ErrAng=modulo2pi(Consigne.Ang-Reel.Ang);
			if((Reel.ErrAng>=C_pi4) || (Reel.ErrAng<=-C_pi4)){
				err_pst_ang(ErrPst_M);
			}
			else{
				err_pst_xy(ErrPst_M,1);
			}
			FlagMove.Pst=1;
			break; 
		default :
			break;
	} 
	if(Consigne.mode==10)
	{
		P1DC1=0;
		P1DC2=0;
	}
	else
	{
		if(Consigne.mode==0){
			Cons0_Vts_M1=limit_acc(Cons0_Vts_M1,Consigne.Vts_M1);
			Cons0_Vts_M2=limit_acc(Cons0_Vts_M2,Consigne.Vts_M2);
			ErrVts_M[0]=Cons0_Vts_M1-Reel.Vts_M1;
			ErrVts_M[1]=Cons0_Vts_M2-Reel.Vts_M2;
		}
		else{
			ErrVts_M[0]=Consigne.Vts_M1-Reel.Vts_M1;
			ErrVts_M[1]=Consigne.Vts_M2-Reel.Vts_M2;
		}
		corr_vts(ErrVts_M);
		aff_vitesse_roue(ErrVts_M);
	}
}


