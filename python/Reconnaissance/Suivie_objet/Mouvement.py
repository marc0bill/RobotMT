import constantes
import serial

def avancer(vitesse, portSerie):
	commande = "VtsM %f %f" % (vitesse, vitesse)
	UART.write(portSerie, commande)
	#On l'envoie plusieurs fois car nous avon quelques soucis avec le baudrate à ce stade
	UART.write(portSerie, commande)
	UART.write(portSerie, commande)

def reculer(vitesse, portSerie):
	commande = "VtsM -%f -%f" % (vitesse, vitesse)
	UART.write(portSerie, commande)
	#On l'envoie plusieurs fois car nous avon quelques soucis avec le baudrate à ce stade
	UART.write(portSerie, commande)
	UART.write(portSerie, commande)

def tourner_sur_place(vitesse, direction, portSerie):

	if direction == "droite":
		commande = "VtsM %f -%f" % (vitesse, vitesse)
	elif direction == "gauche":
		commande = "VtsM -%f %f" % (vitesse, vitesse)
	else:
		print("Erreur : direction incorrecte") #normalement on passe jamais par là
    UART.write(portSerie, commande)
	#On l'envoie plusieurs fois car nous avon quelques soucis avec le baudrate à ce stade
	UART.write(portSerie, commande)
	UART.write(portSerie, commande)


def tourner_et_avancer(vitesse_alignement,vitesse_position, direction, portSerie):

	if direction == "droite":
		commande = "VtsM %f %f" % (vitesse_position + vitesse_alignement, vitesse_position - vitesse_alignement)    
	else direction == "gauche":
		commande = "VtsM %f %f" % (vitesse_position - vitesse_alignement, vitesse_position + vitesse_alignement)  
    else:
		print("Erreur : direction incorrecte") #normalement on passe jamais par là
    UART.write(portSerie, commande)
	#On l'envoie plusieurs fois car nous avon quelques soucis avec le baudrate à ce stade
	UART.write(portSerie, commande)
	UART.write(portSerie, commande)