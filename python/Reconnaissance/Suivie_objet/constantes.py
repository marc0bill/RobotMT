#General
DIAGONALE_ECRAN = 1/SQRT(2) #Valeur normalisé de la diagonale de l'ecran

#UART
BAUDRATE = 57600

#Asservissement
TOLERANCE_ANGLE = 0.1 #distance du centre de l'objet par rapport au centre de l'écran tolérée avant de considérer que le robot est aligné avec l'objet suivi
TOLERANCE_DISTANCE = 0.05 #tolerance de taille à partir duquel le robot considère avoir remplie la consigne de distance à l'objet
ITERATION_MAX = 20 #protection contre les boucles infines
KV = 200 #correcteur proportionnel de vitesse
DELAIS_ALIGNEMENT = 5 #Delais en seconde laissé au robot pour corriger son alignement
DELAIS_POSITIONNEMENT = 1 #Delais en seconde laissé au robot pour corriger sa position
DISTANCE_SUIVIE = 0.3 #consigne de ratio de taille que l'objet doit occuper sur l'ecran pour être considéré à bonne distance lors d'une poursuite
DISTANCE_FUITE = 0.1#consigne de ratio de taille que l'objet doit occuper sur l'ecran pour être considéré à bonne distance lors d'une fuite
