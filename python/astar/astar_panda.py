import pandas as pd
import numpy as np
from math import *

def calcul_H(voisin):
	return sqrt((voisin.X-voisin.X_fin)**2+(voisin.Y-voisin.Y_fin)**2)

def calcul_G(voisin):
	voisin['G']=G_current+sqrt((voisin.X-voisin.X_current)**2+(voisin.Y-voisin.Y_current)**2)

def astar_dis(carte,id_current):
	X_current=carte['X'][id_current]
	Y_current=carte['Y'][id_current]
	G_current=carte['G'][id_current]
	carte.set_value(id_current, 'Noeud', 'close')
	#liste=(carte.X<=X_current+1)&(carte.X>=X_current-1)&(carte.Y<=Y_current+1)&(carte.Y>=Y_current-1) & (carte.Noeud!='close')
	voisin=carte[(carte.X<=X_current+1)&(carte.X>=X_current-1)&(carte.Y<=Y_current+1)&(carte.Y>=Y_current-1) & (carte.Noeud!='close')]
	voisin['G']=G_current+sqrt((voisin.X-voisin.X_current)**2+(voisin.Y-voisin.Y_current)**2)
	voisin['H']=sqrt((voisin.X-voisin.X_fin)**2+(voisin.Y-voisin.Y_fin)**2)
	voisin['Fnew']=voisin['H']+voisin['G']
	carte['Noeud'].ix[voisin.index]='open'
	#carte['Noeud'].ix[liste]='open'
	liste_F=voisin[(voisin['F']>voisin['Fnew'])]
	carte['idParent'].ix[liste_F.index]=id_current
	#carte['F'].ix[liste_F.index]=voisin['Fnew']
	#carte['G'].ix[liste_F.index]=voisin['G']
	carte['F'].ix[voisin.index]=voisin['Fnew']
	carte['G'].ix[voisin.index]=voisin['G']
	id_next=carte[carte.Noeud=='open'].F.idxmin()
	return id_next
#
def astar_pathfind(carte,start,fin):
	id_current=carte[(carte.X==start[0])&(carte.Y==start[1])].index[0]
	id_fin=carte[(carte.X==fin[0])&(carte.Y==fin[1])].index[0]
	carte.set_value(id_current,'G', 0)
	while (carte['X'][id_current]!=fin[0]) & (carte['Y'][id_current]!=fin[1]):
		id_current=astar_dis(carte,id_current)
	return carte
#