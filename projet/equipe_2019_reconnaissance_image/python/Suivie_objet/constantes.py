import math
#General
DIAGONALE_ECRAN = math.sqrt(2) #Valeur normalisé de la diagonale de l'ecran
DELAIS_ACQUISITION = 0 #Delais en seconde entre chaque traitement d'image

#UART
BAUDRATE = 57600

#Asservissement
TOLERANCE_ANGLE = 0.2 #distance du centre de l'objet par rapport au centre de l'écran tolérée avant de considérer que le robot est aligné avec l'objet suivi
TOLERANCE_DISTANCE = 0.1 #tolerance de taille à partir duquel le robot considère avoir remplie la consigne de distance à l'objet
KA = 250 #correcteur proportionnel de vitesse lié à l'alignement
KP = 500 #correcteur proportionnel de vitesse lié à la position
DELAIS_ALIGNEMENT = 0.5 #Delais en seconde laissé au robot pour corriger son alignement
DELAIS_POSITIONNEMENT = 0.5 #Delais en seconde laissé au robot pour corriger sa position
DISTANCE_SUIVIE = 0.5 #consigne de ratio de taille que l'objet doit occuper sur l'ecran pour être considéré à bonne distance lors d'une poursuite
DISTANCE_FUITE = 0.2#consigne de ratio de taille que l'objet doit occuper sur l'ecran pour être considéré à bonne distance lors d'une fuite
Vitesse_min = 75 #vitesse min acceptée
Vitesse_max = 175 #vitesse max acceptée
#Mode de déplacement
Mode = 0 #Mettre 0 si on souhaite avancer et se positionner en 2 temps. Mettre 1 si si on souhaite avancer et se positionner en même temps
