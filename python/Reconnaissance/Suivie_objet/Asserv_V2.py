import ReconnaissanceV2 as RV2
import serial
import UART
import constantes
import ObjetReconnu
from time import sleep

def aligner_robot(Objet_Tracke, portSerie):

	if abs(Objet_Tracke.milieu_X) > TOLERANCE_ANGLE : #On s'aligne avec l'objet

		vitesse_correction = KV*Objet_Tracke.milieu_X

		if Objet_Tracke.milieu_X > TOLERANCE_ANGLE	:
			#on tourne vers la droite (a verifier)
			#(vitesse_roue_droite, vitesse_roue_gauche) = (vitesse_correction, -vitesse_correction)
			Mouvement.tourner_sur_place(vitesse_correction, "droite")
		else:
			#on tourne vers la gauche (a verifier)
			#(vitesse_roue_droite, vitesse_roue_gauche) = (-vitesse_correction, vitesse_correction)
			Mouvement.tourner_sur_place(vitesse_correction, "droite")
		sleep(DELAIS_ALIGNEMENT) #On laisse le temps au robot de tourner
		return 0 #le robot n'etait pas aligné à l'appel de la fonction, il a été corrigé depuis mais on ne sait pas encore si cela est suffisant
	else:
		return 1 #le robot est aligné à l'appel de la fonction

def positioner_robot(Objet_Tracke, ordre, portSerie):

	if ordre == "suivre":
		consigne = DISTANCE_SUIVIE
	else:
		consigne = DISTANCE_FUITE

	delta_D = Objet_Tracke.ratio - consigne

	#On compare la taille de l'objet par rapport à la taille
	#de l'ecran afin de savoir si le robot doit avance ou reculer
	#afin de respecter la consigne de distance (variant en fonction de l'ordre)
	if abs(delta_D) > TOLERANCE_DISTANCE: #On ajuste la position du robot

		vitesse_correction = KP*delta_D

		if delta_D < 0: #le robot est trop loin
			Mouvement.avancer(vitesse_correction)
		else:
			Mouvement.reculer(vitesse_correction)

		sleep(DELAIS_POSITIONNEMENT)


