import ReconnaissanceV2 as RV2
import serial
import UART
import constantes
import Asserv_V2
import ObjetReconnu
from time import sleep

NOMBRE_DE_PASSE = 20 #Nombre de consigne à envoyer

nomObjetASuivre = "person"
nomObjetAFuir = "handbag"

print("chargement model")

(category_index,image_tensor,detection_boxes,detection_scores,detection_classes,num_detections,sess)=RV2.load_model()

print("Configuration du port serie")
#Configuration du port série :
portSerie = serial.Serial("/dev/ttyS0",constantes.BAUDRATE)
print("port serie configure")

for p in range(NOMBRE_DE_PASSE):
	print("Passe ", p)
	#Acquisition des objets reconnues
	Liste_Objets_Reconnues=RV2.Detection(category_index,image_tensor,detection_boxes,detection_scores,detection_classes,num_detections,sess)
	#Liste_Objets_Reconnues est un tableau de liste formattées comme suit:
	#Liste_Objets_Reconnues[i] = (nom, probabilité, y_min, x_min, y_max, x_max)

	for j in range(len(Liste_Objets_Reconnues)): #on scan tous les objets reconnues
		if Liste_Objets_Reconnues[j][0] == nomObjetASuivre or Liste_Objets_Reconnues[j][0] == nomObjetAFuir :
			#On crée un objet à partir de la liste recupérée de tensorflow
			Objet_Tracke = ObjetReconnu.ObjetReconnu(Liste_Objets_Reconnues[j][0], Liste_Objets_Reconnues[j][1], Liste_Objets_Reconnues[j][2], Liste_Objets_Reconnues[j][3], Liste_Objets_Reconnues[j][4], Liste_Objets_Reconnues[j][5])
			if constantes.Mode == 0 :
				alignement = Asserv_V2.aligner_robot(Objet_Tracke, portSerie)
				if alignement == 1: #Si le robot est correctement aligné, on corrige sa position
					if Objet_Tracke.nom == nomObjetASuivre :
						ordre = "suivre"
					else : #si ce n'est pas l'objet à suivre, c'est l'objet à suivre au vu d'un if precedent
						ordre = "fuir"
					position = Asserv_V2.positioner_robot(Objet_Tracke, ordre, portSerie)
           
			elif constantes.Mode == 1:
				Asserv_V2.aligner_positionner_robot(Objet_Tracke, nomObjetASuivre, portSerie)  
	sleep(constantes.DELAIS_ACQUISITION)             


portSerie.close()
