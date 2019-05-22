import ReconnaissanceV2 as RV2
import serial
from time import sleep

BAUDRATE = 57600
NOMBRE_DE_PASSE = 3
objetTracke = "tv"
vitesse = 200

print("Chargement du model tensorflow...")
(category_index,image_tensor,detection_boxes,detection_scores,detection_classes,num_detections,sess)=RV2.load_model()

#Configuration du port série :
print("Configuration du port serie...")
S = serial.Serial("/dev/ttyS0",baudrate)

print("Traitement des images...")
L=RV2.Detection(category_index,image_tensor,detection_boxes,detection_scores,detection_classes,num_detections,sess)


for j in range (len(L)):
	if L[j][0]==objetTracke:
		while 1:
			data="VtsM %f %f" (vitesse, vitesse)
			print("Envoie de la commande : ", data)
			S.write(data.encode('ascii'))
			#receive=S.readline(len(data))
			#print(receive.decode("utf-8"))
			sleep(1)

S.close()
