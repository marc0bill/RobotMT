import ReconnaissanceV2 as RV2
import serial
import UART
import constantes
import Mouvement
import ObjetReconnu
from time import sleep

def aligner_robot(Objet_Tracke, portSerie):
	distance_relative = "Distance au milieu: %.2f" %Objet_Tracke.milieu_X
	print(distance_relative)

	if abs(Objet_Tracke.milieu_X) > constantes.TOLERANCE_ANGLE : #On s'aligne avec l'objet
		print("Correction de l'alignement")
		vitesse_correction = constantes.KA*Objet_Tracke.milieu_X
		
		if vitesse_correction < constantes.Vitesse_min:
			vitesse_correction = constantes.Vitesse_min
		if vitesse_correction > constantes.Vitesse_max:
			vitesse_correction = constantes.Vitesse_max
			
		if Objet_Tracke.milieu_X > 0 :
			#on tourne vers la droite (a verifier)
			#(vitesse_roue_droite, vitesse_roue_gauche) = (vitesse_correction, -vitesse_correction)
			Mouvement.tourner_sur_place(vitesse_correction, "droite", portSerie)
		else:
			#on tourne vers la gauche (a verifier)
			#(vitesse_roue_droite, vitesse_roue_gauche) = (-vitesse_correction, vitesse_correction)
			Mouvement.tourner_sur_place(vitesse_correction, "gauche", portSerie)
		sleep(constantes.DELAIS_ALIGNEMENT) #On laisse le temps au robot de tourner
		return 0 #le robot n'etait pas aligné à l'appel de la fonction, il a été corrigé depuis mais on ne sait pas encore si cela est suffisant
	else:
		print("Robot aligné")
		return 1 #le robot est aligné à l'appel de la fonction

def positioner_robot(Objet_Tracke, ordre, portSerie):

	if ordre == "suivre":
		print("En poursuite")
		consigne = constantes.DISTANCE_SUIVIE
	else:
		print("En fuite")
		consigne = constantes.DISTANCE_FUITE
	delta_D = Objet_Tracke.ratio - consigne
	taille_relative = "Taille relative:  %.2f" % Objet_Tracke.ratio
	print(taille_relative)
	#On compare la taille de l'objet par rapport à la taille
	#de l'ecran afin de savoir si le robot doit avance ou reculer
	#afin de respecter la consigne de distance (variant en fonction de l'ordre)
	if abs(delta_D) > constantes.TOLERANCE_DISTANCE: #On ajuste la position du robot
		print("Correction de la position")
		vitesse_correction = constantes.KP*abs(delta_D)
		
		if vitesse_correction < constantes.Vitesse_min:
			vitesse_correction = constantes.Vitesse_min
		if vitesse_correction > constantes.Vitesse_max:
			vitesse_correction = constantes.Vitesse_max
		
		if delta_D < 0: #le robot est trop loin
			Mouvement.avancer(vitesse_correction, portSerie)
		else:
			Mouvement.reculer(vitesse_correction, portSerie)
		sleep(constantes.DELAIS_POSITIONNEMENT)
		return 0
	else:
		UART.write(portSerie, "VtsM 0 0 ")
		UART.write(portSerie, "VtsM 0 0 ")
		UART.write(portSerie, "VtsM 0 0 ")
		print("Robot positionné")
		return 1


def aligner_positionner_robot(Objet_Tracke, nomObjetASuivre, portSerie):

	if Objet_Tracke.nom == nomObjetASuivre :
		ordre = "suivre"
	else : #si ce n'est pas l'objet à suivre, c'est l'objet à suivre au vu d'un if precedent
		ordre = "fuir"

	if ordre == "suivre":
		consigne = constantes.DISTANCE_SUIVIE
	else:
		consigne = constantes.DISTANCE_FUITE

	delta_D = Objet_Tracke.ratio - consigne 

	if abs(Objet_Tracke.milieu_X) > constantes.TOLERANCE_ANGLE : #On s'aligne avec l'objet

		vitesse_alignement = constantes.KA*Objet_Tracke.milieu_X

		if Objet_Tracke.milieu_X > 0 :
			#on tourne vers la droite (a verifier)
			#(vitesse_roue_droite, vitesse_roue_gauche) = (vitesse_correction, -vitesse_correction)
			direction = "droite"
		else:
			#on tourne vers la gauche (a verifier)
			#(vitesse_roue_droite, vitesse_roue_gauche) = (-vitesse_correction, vitesse_correction)
			direction = "gauche"


    	#On compare la taille de l'objet par rapport à la taille
    	#de l'ecran afin de savoir si le robot doit avance ou reculer
    	#afin de respecter la consigne de distance (variant en fonction de l'ordre)
		if abs(delta_D) > constantes.TOLERANCE_DISTANCE: #On ajuste la position du robot

			vitesse_position = constantes.KP*delta_D

		if delta_D < 0: #le robot est trop loin
			Mouvement.tourner_et_avancer(vitesse_alignement, vitesse_position, direction, portSerie)
		else:
			Mouvement.tourner_et_reculer(vitesse_alignement, vitesse_position, direction, portSerie)

