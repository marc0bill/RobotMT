import constantes
import serial
import UART

def avancer(vitesse, portSerie):
	print("En marche avant")
	commande = "VtsM  "
	commande1 = " %.0f " %vitesse
	commande2 = " %.0f " %vitesse
	UART.write(portSerie, commande)
	#On l'envoie plusieurs fois car nous avon quelques soucis avec le baudrate à ce stade
	UART.write(portSerie, commande1)
	UART.write(portSerie, commande2)

def reculer(vitesse, portSerie):
	print("En marche avant")
	commande = "VtsM  "
	commande1 = " -%.0f " %vitesse
	commande2 = " -%.0f " %vitesse
	UART.write(portSerie, commande)
	#On l'envoie plusieurs fois car nous avon quelques soucis avec le baudrate à ce stade
	UART.write(portSerie, commande1)
	UART.write(portSerie, commande2)

def tourner_sur_place(vitesse, direction, portSerie):
	print("On tourne a ", direction)
	if direction == "droite":
		commande = "VtsM %.0f %.0f " %(vitesse, -vitesse)
	elif direction == "gauche":
		commande = "VtsM %.0f %.0f " %(-vitesse, vitesse)
	else:
		print("Erreur : direction incorrecte") #normalement on passe jamais par là

	UART.write(portSerie, commande)
	#On l'envoie plusieurs fois car nous avon quelques soucis avec le baudrate à ce stade
	UART.write(portSerie, commande)
	UART.write(portSerie, commande)


def tourner_et_avancer(vitesse_alignement,vitesse_position, direction, portSerie):
	if direction == "droite":
		commande = "VtsM %.0f %.0f\n" %(vitesse_position + vitesse_alignement, vitesse_position - vitesse_alignement)    
	elif direction == "gauche":
		commande = "VtsM %.0f %.0f\n" %(vitesse_position - vitesse_alignement, vitesse_position + vitesse_alignement)  
	else:
		print("Erreur : direction incorrecte") #normalement on passe jamais par là
	UART.write(portSerie, commande)
	#On l'envoie plusieurs fois car nous avon quelques soucis avec le baudrate à ce stade
    #UART.write(portSerie, commande)
    #UART.write(portSerie, commande)
	
	
	
	
def tourner_et_reculer(vitesse_alignement,vitesse_position, direction, portSerie):
	if direction == "droite":
		commande = "VtsM %f %f" %(-vitesse_position + vitesse_alignement, -vitesse_position - vitesse_alignement)    
	elif direction == "gauche":
		commande = "VtsM %f %f" %(-vitesse_position - vitesse_alignement, -vitesse_position + vitesse_alignement)  
	else:
		print("Erreur : direction incorrecte") #normalement on passe jamais par là
	UART.write(portSerie, commande)
	
	
	
	