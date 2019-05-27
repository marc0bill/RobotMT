import math
#General
DIAGONALE_ECRAN = math.sqrt(2) #Valeur normalisé de la diagonale de l'ecran
DELAIS_ACQUISITION = 2 #Delais en seconde entre chaque traitement d'image

#UART
BAUDRATE = 57600

#Asservissement
TOLERANCE_ANGLE = 0.1 #distance du centre de l'objet par rapport au centre de l'écran tolérée avant de considérer que le robot est aligné avec l'objet suivi
TOLERANCE_DISTANCE = 0.05 #tolerance de taille à partir duquel le robot considère avoir remplie la consigne de distance à l'objet
KA = 1000 #correcteur proportionnel de vitesse lié à l'alignement
KP = 1000 #correcteur proportionnel de vitesse lié à la position
DELAIS_ALIGNEMENT = 0.5 #Delais en seconde laissé au robot pour corriger son alignement
DELAIS_POSITIONNEMENT = 0.5 #Delais en seconde laissé au robot pour corriger sa position
DISTANCE_SUIVIE = 0.4 #consigne de ratio de taille que l'objet doit occuper sur l'ecran pour être considéré à bonne distance lors d'une poursuite
DISTANCE_FUITE = 0.2#consigne de ratio de taille que l'objet doit occuper sur l'ecran pour être considéré à bonne distance lors d'une fuite

#Mode de déplacement
Mode = 0 #Mettre 0 si on souhaite avancer et se positionner en 2 temps. Mettre 1 si si on souhaite avancer et se positionner en même temps
