import ReconnaissanceV2 as RV2
import serial
import UART
import constantes
from time import sleep

NOMBRE_DE_PASSE = 10 #Nombre de consigne à envoyer

objetSuivi = 'laptop'

(category_index,image_tensor,detection_boxes,detection_scores,detection_classes,num_detections,sess)=RV2.load_model()

#Configuration du port série :
S = serial.Serial("/dev/ttyS0",baudrate)

for p in range(NOMBRE_DE_PASSE)
	
	#ObjetsReconnues est un tableau de liste formattées comme suit:
	#ObjetsReconnues[i] = (nom, probabilité, y_min, x_min, y_max, x_max)
	ObjetsReconnues=RV2.Detection(category_index,image_tensor,detection_boxes,detection_scores,detection_classes,num_detections,sess)

	for j in range (len(ObjetsReconnues)):
		if ObjetsReconnues[j][0]==objetSuivi:
			data='VtsM 50 50'

			UART.write(S, data)
			print(UART.read(S))

			sleep(2)
			data='Stop'

			UART.write(S, data)
			print(UART.read(S))


S.close()
