/****************************************************************************************

Révision:     	$Rev: $
Auteur:       	$Author: $
Date révision: 	$Date:  $
projet:      	$URL: $


*/
#include <math.h>
#include "header.h"
#include "move.h"

#ifdef _PATHFIND_H_

int tailleLO;
struct SN map[Y_MAX][X_MAX];
struct SN parent[Y_MAX][X_MAX];
struct SN open_list[(Y_MAX+X_MAX)*2];
struct SN current;

char CARTE[Y_MAX][X_MAX];

int dest_x[4]={5, 2, 5, 2};
int dest_y[4]={5, 2, 5, 2};

void demo_pathfinding(void){
	static int step=0;
	static int func=0;
	static int func_coli=0;
	static unsigned long temps_reset=0;
	static unsigned long tempsjeux_last=0;
	static int Rx_fut=0;
	static int Ry_fut=0;
	static int Rx_obs=0;
	static int Ry_obs=0;
	int Rx;
	int Ry;
	Rx=arrond(Reel.x/CARRE_DIS);
	Ry=arrond(Reel.y/CARRE_DIS);


	if((tempsjeux-temps_reset)>=18000) {	//Reset les obstacles
		reset_obs(CARTE);
		Pathfind(Rx, Ry, dest_x[func], dest_y[func], 1);
		FlagMove.Ordre=3;
		temps_reset=tempsjeux;
	}

/*Identification de la collision*/
	if(FlagMove.CollRob==0 && (Dis.obstAv_uS < DISVAR)){// && FlagMove.Avance==1 || (Dis.obstAr_uS < DISVAR && FlagMove.Avance==-1)))){
	switch (get_orientation(Reel.AngModPi)){
		case 1:
			Rx_obs=arrond((Reel.x+50)/CARRE_DIS);
			Ry_obs=Ry;
			Rx_fut=(Rx-2);
			Ry_fut=Ry;
			break;
		case 2:
			Rx_obs=Rx;
			Ry_obs=arrond((Reel.y+50)/CARRE_DIS);
			Rx_fut=Rx;
			Ry_fut=(Ry-2);
			break;
		case 3:
			Rx_obs=arrond((Reel.x-50)/CARRE_DIS);
			Ry_obs=Ry;
			Rx_fut=(Rx+2);
			Ry_fut=Ry;
			break;
		case 4 :
			Rx_obs=Rx;
			Ry_obs=arrond((Reel.y-50)/CARRE_DIS);
			Rx_fut=Rx;
			Ry_fut=(Ry+2);
			break;
		}

//		ajouter_obs(CARTE, Rx_obs, Ry_obs); // il faut voir si on rajoute tout obstacle observé ou pas ...

		if(map[Ry_obs][Rx_obs].List==CHEMIN)
			FlagMove.CollRob=1;
		else
			FlagMove.CollRob=0;
	}	

/*Traitement de la collision*/
	if(FlagMove.CollRob==1){
		switch(func_coli){
			case 0:
				FlagMove.Ordre=2;	//Arrete
				ajouter_obs(CARTE, Rx_obs, Ry_obs);
				//Recule
				TablePst.x[1]=Rx_fut*CARRE_DIS;
				TablePst.y[1]=Ry_fut*CARRE_DIS;
				TablePst.Ang[1]=0;
				TablePst.mode[1]=6;
				TablePst.nb=2;
				FlagMove.Ordre=3;
				tempsjeux_last=tempsjeux;
				func_coli++;
				break;
			case 1:
				//Recule fini?
				if((FlagMove.Pst==1) || (tempsjeux-tempsjeux_last>=3000))
					func_coli++;
				break;
			case 2:
				Pathfind(Rx, Ry, dest_x[func], dest_y[func], 1);
				//if(Dis.obstAv > DISVAR && Dis.obstAr > DISVAR){
					FlagMove.CollRob=0;
					FlagMove.Ordre=3;
					func_coli=0;
				//}
				break;
		}
	}


/*Gesion des different point d'interet*/
if(FlagMove.CollRob==0){
	switch (func){
		case 0:
			switch(step){
				case 0:
					Pathfind(Rx, Ry, dest_x[func], dest_y[func], 1);
					FlagMove.Start=1;
					FlagMove.Ordre=3;
					step=1;
					break;
				case 1:
					if(Rx==dest_x[func] && Ry==dest_y[func]) step=2;
					break;
				case 2:
					func=1;
					step=0;
					init_map(CARTE);
					break;
			}
			break;
		case 1:
			switch(step){
				case 0:
					Pathfind(Rx, Ry, dest_x[func], dest_y[func], 1);
					FlagMove.Ordre=3;
					step=1;
					break;
				case 1:
					if(Rx==dest_x[func] && Ry==dest_y[func]) step=2;
					break;
				case 2:
					func=2;
					step=0;
					init_map(CARTE);
					break;
			}
			break;
		case 2:
			switch(step){
				case 0:
					Pathfind(Rx, Ry, dest_x[func], dest_y[func], 1);
					FlagMove.Ordre=3;
					step=1;
					break;
				case 1:
					if(Rx==dest_x[func] && Ry==dest_y[func]) step=2;
					break;
				case 2:
					func=3;
					step=0;
					init_map(CARTE);
					break;
			}
			break;
		case 3:
			switch(step){
				case 0:
					Pathfind(Rx, Ry, dest_x[func], dest_y[func], 1);
					FlagMove.Ordre=3;
					step=1;
					break;
				case 1:
					if(Rx==dest_x[func] && Ry==dest_y[func]) step=2;
					break;
				case 2:
//					ascenseur(down);
//					func=8;//On arret tout
					func=0;//On recommance
					step=0;
					init_map(CARTE);
					break;
			}
			break;
		case 8://final
			P1DC1=0;
			P1DC2=0;
			step=0;
			Consigne.mode=10;
			break;
	}
}
}














void clear_carte(){
	int i, j;
	for (j=0; j<Y_MAX; j++){
		for (i=0; i<X_MAX; i++){
			CARTE[j][i]=0;
		}
	}
}

void init_map(char iMap[Y_MAX][X_MAX]){
	int i, j;
	for (j=0; j<Y_MAX; j++){
		for (i=0; i<X_MAX; i++){
			if(iMap[j][i]==1) map[j][i].List=OBSTACLE;
			else map[j][i].List=VIDE;
		}
	}
}

void init_pathfind(double x_o, double y_o, double ang){
    TablePst.x[0]=x_o;
    TablePst.y[0]=y_o;
    TablePst.Ang[0]=ang;
    TablePst.mode[0]=-1; //position initiale / -1 ???** TESTAR
    TablePst.Dis[0]=0; // en mm 		inutil pour notre application
    TablePst.Vmax_M[0]=VCROISIERE;	// vitesse max
//	TablePst.Acc_M[0]=2;	// acceleration des roues
    TablePst.wait[0]=0.5; // en s		attente sur un point
//	TablePst.d_Obst[0]=0;
    TablePst.ErrAng[0]=ERR_ANGm;// en mm		erreur tolere pour valider la position
    TablePst.Err_x[0]=ERR_XYm;
    TablePst.Err_y[0]=ERR_XYm;
    clear_carte();
}

void ajouter_obs(char carte[Y_MAX][X_MAX], int ix, int iy){
	carte[iy][ix]=1;
	if(iy+1<Y_MAX)carte[iy+1][ix]=1;
	if(ix+1<X_MAX)carte[iy][ix+1]=1;
	if(iy-1>=0)carte[iy-1][ix]=1;
	if(ix-1>=0)carte[iy][ix-1]=1;
	init_map(carte);
}

void supprimer_obs(char carte[Y_MAX][X_MAX], int ix, int iy){
	carte[iy][ix]=0;
	init_map(carte);
}

void reset_obs(char carte[Y_MAX][X_MAX]){
	int i, j;

	for (j=0; j<Y_MAX; j++){
		for (i=0; i<X_MAX; i++){
				carte[j][i]=0;
			}
		}
	init_map(carte);
}

char ListAnalyseur(struct SN map[Y_MAX][X_MAX],int ix, int iy, struct SN current_a){

	char isFound=0;
	int f;
	struct SN temp_node;

			if(map[iy][ix].List == LO){
				if(map[iy][ix].G>current_a.G+CARRE){
					map[iy][ix].G = current_a.G+CARRE;
					map[iy][ix].F = map[iy][ix].G+map[iy][ix].H;
					parent[map[iy][ix].iy][map[iy][ix].ix]=current_a;
	
					//Reorganiser le binary heap
					f=1;
					while(open_list[f].ix!=map[iy][ix].ix || open_list[f].iy!=map[iy][ix].iy) f++;
					while(f!=1){
						if(open_list[f].F<=open_list[f/2].F){
							temp_node=open_list[f/2];
							open_list[f/2]=open_list[f];
							open_list[f]=temp_node;
							f=f/2;
						}
						else break;
					}
					//Fin binary heap
				}
			}
			
			else if(map[iy][ix].List == VIDE){
				map[iy][ix].G = current_a.G+CARRE;
				map[iy][ix].F = map[iy][ix].G+map[iy][ix].H;
				map[iy][ix].List=LO;
				parent[map[iy][ix].iy][map[iy][ix].ix]=current_a;

				//Ajouter dans binary heap
				tailleLO++;
				f=tailleLO;
				open_list[f]=map[iy][ix];
				while(f!=1){
					if(open_list[f].F<=open_list[f/2].F){
						temp_node=open_list[f/2];
						open_list[f/2]=open_list[f];
						open_list[f]=temp_node;
						f=f/2;
					}
					else break;
				}
				//Fin binary heap
			}
			
			else if(map[iy][ix].List == ARRIVE){
				map[iy][ix].G = current_a.G+CARRE;
				map[iy][ix].F = map[iy][ix].G+map[iy][ix].H;
				parent[map[iy][ix].iy][map[iy][ix].ix]=current_a;
				isFound=1;
			}
			
		return isFound;
	
}

int abs(int e){
	if(e<0) return -e;
	else return e;
}

int arrond(double a){
	int b = (int) a;
	if( (int)(a+0.5) > b ) return (b+1);
	else return b;
}

struct SN ChercherF(){

	int aux1, aux2;
	struct SN current_a = open_list[1];
	struct SN temp_node;
	
	//Supprimer dans binary heap
	open_list[1]=open_list[tailleLO];
	tailleLO--;
	aux1=1;
	while(1){
		aux2 = aux1;
		if(2*aux2+1 <= tailleLO){
			if (open_list[aux2].F >= open_list[2*aux2].F) aux1 = 2*aux2;
			if (open_list[aux1].F >= open_list[2*aux2+1].F) aux1 = 2*aux2+1;
		}
		else if(2*aux2 <= tailleLO){
			if(open_list[aux2].F >= open_list[2*aux2].F) aux1 = 2*aux2;
		}

		if(aux2!=aux1){
			temp_node = open_list[aux2];
			open_list[aux2] = open_list[aux1];
			open_list[aux1] = temp_node;
		}
		else break;
	}
	//Fin binary heap
	return current_a;

}

int EcrireChemin(int x_depart, int y_depart, int x_arrive, int y_arrive, int startTi){
	
	int i;
	int Ti=startTi;
	double chemin_x[CI_MAX];
	double chemin_y[CI_MAX];
	unsigned int Ci=0, Ci_aux=CI_MAX-1;
	struct SN next = parent[y_arrive][x_arrive];

	map[y_arrive][x_arrive].List=CHEMIN;
	chemin_x[Ci_aux]=x_arrive*CARRE_DIS;
	chemin_y[Ci_aux]=y_arrive*CARRE_DIS;
	Ci++;
	while(map[next.iy][next.ix].List!=DEPART){
		map[next.iy][next.ix].List=CHEMIN;
		chemin_x[Ci_aux-Ci]=(double)next.ix*CARRE_DIS;
		chemin_y[Ci_aux-Ci]=(double)next.iy*CARRE_DIS;
		Ci++;
		next=parent[map[next.iy][next.ix].iy][map[next.iy][next.ix].ix];
	}
	
	chemin_x[Ci_aux-Ci]=(double)x_depart*CARRE_DIS;
	chemin_y[Ci_aux-Ci]=(double)y_depart*CARRE_DIS;

	for(i=0; i<=Ci; i++){
		chemin_x[i]=chemin_x[Ci_aux-Ci+i];
		chemin_y[i]=chemin_y[Ci_aux-Ci+i];
	}

	for(i=0; i<=Ci; i++){
		if (i==0) {
			if(chemin_x[i]>chemin_x[i+1])TablePst.Ang[Ti]=C_pi;
			else if(chemin_x[i]<chemin_x[i+1])TablePst.Ang[Ti]=0.0;
			else if(chemin_y[i]>chemin_y[i+1])TablePst.Ang[Ti]=C_3pi2;
			else TablePst.Ang[Ti]=C_pi2;
			TablePst.x[Ti]=0;
			TablePst.y[Ti]=0;
			TablePst.mode[Ti]=4;
			Ti++;
		}
		else if (i==Ci) {
			TablePst.x[Ti]=chemin_x[i];
			TablePst.y[Ti]=chemin_y[i];
			TablePst.Ang[Ti]=0;
			TablePst.mode[Ti]=5;
			Ti++;
		}
		else if (chemin_x[i-1]==chemin_x[i] && chemin_x[i+1]!=chemin_x[i]){
			TablePst.x[Ti]=chemin_x[i];
			TablePst.y[Ti]=chemin_y[i];
			TablePst.Ang[Ti]=0;
			TablePst.mode[Ti]=5;
			Ti++;
			TablePst.x[Ti]=0;
			TablePst.y[Ti]=0;
			TablePst.mode[Ti]=4;
				if(chemin_x[i+1]>chemin_x[i]){
					TablePst.Ang[Ti]=0.0;
				}
				else {
					TablePst.Ang[Ti]=C_pi;
				}
			Ti++;
		}

		else if (chemin_x[i-1]!=chemin_x[i] && chemin_x[i+1]==chemin_x[i]){
			TablePst.x[Ti]=chemin_x[i];
			TablePst.y[Ti]=chemin_y[i];
			TablePst.Ang[Ti]=0;
			TablePst.mode[Ti]=5;
			Ti++;
			TablePst.x[Ti]=0;
			TablePst.y[Ti]=0;
			TablePst.mode[Ti]=4;
				if(chemin_y[i+1]>chemin_y[i]){
					TablePst.Ang[Ti]=C_pi2;
				}
				else {
					TablePst.Ang[Ti]=C_3pi2;
				}
			Ti++;
		}
	}

	TablePst.nb=Ti;

	for(i=1; i<Ti; i++){
		TablePst.Dis[i]=0; // en mm 		inutil pour notre application
		TablePst.Vmax_M[i]=VCROISIERE;	// vitesse max		
	//	TablePst.Acc_M[i]=2;	// acceleration des roues
		TablePst.wait[i]=0.5; // en s		attente sur un point
		//TablePst.d_Obst[i]=0;
		TablePst.ErrAng[i]=ERR_ANGm;// en mm		erreur tolere pour valider la position
		TablePst.Err_x[i]=ERR_XYm;
		TablePst.Err_y[i]=ERR_XYm;
	}
	
	FlagMove.Pst=1;
	FlagMove.Start=0;
	FlagMove.Ordre=0;
	FlagMove.Avance=0;
	FlagMove.CollRob=0;

	return Ti;

}

void calculF(int x_depart, int y_depart, int x_arrive, int y_arrive){

	int j, i;	
		
	map[y_arrive][x_arrive].List=ARRIVE;
	map[y_depart][x_depart].List=DEPART;

	//Initialiser la list ouverte
	for(i=0;i<((Y_MAX+X_MAX)*2);i++) open_list[i].F=INT_MAX;
	tailleLO=0;
	
	for (j=0; j<Y_MAX; j++){
		for (i=0; i<X_MAX; i++){
			map[j][i].ix=i;
			map[j][i].iy=j;
			map[j][i].H=abs(x_arrive-map[j][i].ix) + abs(y_arrive-map[j][i].iy);
			map[j][i].G=0;
			map[j][i].F=map[j][i].H+map[j][i].G;
			if(map[j][i].List!=ARRIVE && map[j][i].List!=DEPART && map[j][i].List!=OBSTACLE) map[j][i].List=VIDE;				
		}
	}
		
}

int Pathfind(int x_depart, int y_depart, int x_arrive, int y_arrive, int startTi){
	char isFound=0;
	int endTi=0;

	if((x_depart!=x_arrive || y_depart!=y_arrive) && map[y_arrive][x_arrive].List!=OBSTACLE){ //Conditions initiales
		calculF(x_depart, y_depart, x_arrive, y_arrive);
		current=map[y_depart][x_depart];
		parent[y_arrive][x_arrive]=map[y_depart][x_depart];

	//Trouver le chemin
		while(isFound==0){
			
			//Analyse les noeuds adjacent
			if((current.iy-1)>=0) isFound = ListAnalyseur(map,current.ix,current.iy-1, current);
			if(isFound==1) break;
			if((current.ix+1)<X_MAX) isFound = ListAnalyseur(map,current.ix+1,current.iy, current);
			if(isFound==1) break;
			if((current.iy+1)<Y_MAX) isFound = ListAnalyseur(map,current.ix,current.iy+1, current);
			if(isFound==1) break;
			if((current.ix-1)>=0) isFound = ListAnalyseur(map,current.ix-1,current.iy, current);
			if(isFound==1) break;

			//Prendre le noeud avec le plus petit F
			current=ChercherF();

			if(current.F==INT_MAX) break; //LO vide, pas de solution		

			//Ajoute le noeud current à la list fermé
			map[current.iy][current.ix].List=LF;

		}
	}

	if(isFound==1) endTi = EcrireChemin(x_depart, y_depart, x_arrive, y_arrive, startTi);
	else { endTi=1; TablePst.nb=1; } //Pas de solution
	return endTi;

}

void Pathfind2 (int xDepart, int yDepart, int xArrive1, int yArrive1, int xArrive2, int yArrive2){
	
	int startTi=1;
	startTi=Pathfind(xDepart, yDepart, xArrive1, yArrive1, startTi);
	map[yDepart][xDepart].List=VIDE;
	map[yArrive1][xArrive1].List=VIDE;
	startTi=Pathfind(xArrive1, yArrive1, xArrive2, yArrive2, startTi);

}
#endif


