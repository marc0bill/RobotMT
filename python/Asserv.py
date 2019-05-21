import ReconnaissanceV2 as RV2
import serial
import constantes
import UART

def decision(ObjetsReconnues, ObjetSuivi, serial):
	"""
	BUT:
	Determiner ce que le robot doit faire en fonction de ce 
	qu'il voit

	ARGUMENT:
	ObjetsReconnues est un tableau de liste formattées comme suit:
	ObjetsReconnues[i] = (nom, probabilité, y_min, x_min, y_max, x_max)

	ObjetSuivi est le nom de l'objet à suivre (string)
	"""

	for i in range (len(ObjetsReconnues)): #On scanne tous les objets reconnues
		if ObjetsReconnues[i][0]==objetSuivi: #Si on trouve l'objet suivi
			y_min = ObjetsReconnues[i][2]
			x_min = ObjetsReconnues[i][3]
			y_max = ObjetsReconnues[i][4]
			y_min = ObjetsReconnues[i][5]
			suivre(ObjetsReconnues[i], serial)



def suivre(ObjetSuivi, serial):
	"""
	BUT : 
	Renvoyer la vitesse de chacune des 2 roues afin de
	suivre un objet en fonction de sa position et de sa taille

	ARGUMENT:
	Les 4 arguments sont les coordonnées du point supérieur gauche
	et inferieur droit de la box de l'objet
	Les x et y sont données en valeurs normalisées (de 0 à 1)
	Le points en haut à gauche est (0,0) et en bas à doite (1,1)
	Le centre de l'ecran est donc en (0.5, 0.5)

	SORTIE:
	Tuple : (vitesse_roue_droite, vitesse_roue_gauche)
	"""
	# float distanceAuCentre #distance de l'objet par rapport au centre de l'ecran
	# float ratio
	# Vitesse == "VtsM"
	# float Vit_droite = 50
	# float Vit_gauche = 50
	# float tailleX = 0, tailleY = 0 #longueur et largeur de l'objet
	# float diagonale #taille de l'objet (diagonale de la box)
	# Ksize,Kdist= 0
	# float centreObjet #

	# for i in range ObjetSuivi.length():
	# 	if ObjetSuivi[i][0] == "Cannette":
	# 		tailleY = (ObjetSuivi[i][4]-ObjetSuivi[i][2]) #y_max-y_min
	# 		tailleX = (ObjetSuivi[i][5]-ObjetSuivi[i][3]) #x_max-x_min
	# 		Size = SQRT((deltaX**2) + (deltaY**2))
	# centreObjet = (ObjetSuivi[i][3] + ObjetSuivi[i][5])/2.0
	# distance = (Middle - 0.5)
	# ratio = Size / SQRT(2)
	
	# while ratio=!0.3 and 0.2<ratio<0.8
	# 	Ksize = (ratio-0.5)/0.3
	# Kdist = distance/0.5

	#Je recommence à partir d'ici
	nomObjet = ObjetSuivi[0]
	diagonaleEcran = 1/SQRT(2)
	iteration = 0 #nombre d'iteration de la boucle effectuée
	centreObjet = 1
	(vitesse_roue_droite, vitesse_roue_gauche) = (0,0)
	K = 200 #correcteur proportionnel
	distancePoursuite = 0.3 #ratio de taille de l'objet suivie auquel le robot doit s'adapter


	#On recentre les coordonnées en prenant le centre de l'ecran
	#de coordonnées (0.5, 0.5) pour origin
	y_min = ObjetSuivi[2] - 0.5
	x_min = ObjetSuivi[3] - 0.5
	y_max = ObjetSuivi[4] - 0.5
	x_max = ObjetSuivi[5] - 0.5
	centreObjet = (x_min + x_max) /2.0

	#On s'aligne avec l'objet à suivre
	while abs(centreObjet) > TOLERANCE_ANGLE and iteration < ITERATION_MAX

		vitesse_correction = K*centreObjet 

		if centreObjet > TOLERANCE_ANGLE	
			#on tourne vers la droite (a verifier)
			(vitesse_roue_droite, vitesse_roue_gauche) = (vitesse_correction, -vitesse_correction)
		else
			#on tourne vers la gauche (a verifier)
			(vitesse_roue_droite, vitesse_roue_gauche) = (-vitesse_correction, vitesse_correction)
		ObjetSuivi = retrouverObjet(nomObjet);
		centreObjet = calculer_erreur_X(ObjetSuivi)

		iteration++

	#On determine la taille de l'objet
	tailleX = x_max - x_min
	tailleY = y_max - y_min
	diagonaleObjet = SRQT(tailleX**2 + tailleY**2)

	#On compare la taille de l'objet par rapport à la taille
	#de l'ecran afin de savoir si le robot doit avance ou reculer
	ratio = diagonaleObjet/diagonaleEcran
	iteration = 0
	while abs(ratio) > TOLERANCE_DISTANCE and iteration < ITERATION_MAX
		if ratio > distancePoursuite
			direction = MARCHE_ARRIERE
		else
			direction = MARCHE_AVANT
		iteration++
		
		
	return Vit_droite*(Ksize+Kdist),Vit_gauche*(Kdist-Ksize)
	
			
	
def retrouverObjet(nomObjet):
	iteration = 0 #nombre d'iteration de la boucle effectuée
	stop = 0
	ObjetsReconnues=RV2.Detection(category_index,image_tensor,detection_boxes,detection_scores,detection_classes,num_detections,sess)
	i = 0
	while ObjetsReconnues[i][0] != nomObjet and iteration < ITERATION_MAX and stop == 0
		i++
		if (i = ObjetsReconnues.length())
			stop = 1
	if(!stop)
		return ObjetsReconnues[i]
	else
		print("L'objet n'est plus dans le champ de vision")
		break

def calculer_erreur_X(ObjetSuivi):
	x_min = ObjetSuivi[3] - 0.5
	x_max = ObjetSuivi[5] - 0.5
	erreur_X = (x_min + x_max) /2.0
	return erreur_X




