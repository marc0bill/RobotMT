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

while(NOMBRE_DE_PASSE < 10)