#UART
BAUDRATE = 57600

#Asservissement
TOLERANCE_ANGLE = 0.1 #distance du centre de l'objet par rapport au centre de l'écran tolérée avant de considérer que le robot est aligné avec l'objet suivi
TOLERANCE_DISTANCE = 0.1 #tolerance de taille à partir duquel le robot considère avoir remplie la consigne de distance à l'objet
ITERATION_MAX = 20 #protection contre les boucles infines

MARCHE_AVANT = 1
MARCHE_ARRIERE = -1
SUR_PLACE = 0