import time
from PinceClass import PinceClass
import pygame
from pygame.locals import *
import serial

RotMax=100
VtsMax=100

def Seuil(Val,Seuil=0.08):
    
    if Val>=Seuil:
        return Val-Seuil
    else:
        if Val<=-Seuil:
            return Val+Seuil
        else:
            return 0



portMot = serial.Serial()
portMot.baudrate = 9600
portMot.port = "/dev/ttyUSB0"
try:
    portMot.open()
    print "Connected to %s" % portMot.port
except :
    print "Error openning the port!"
    exit()

# Definition de la Pince
Pince=PinceClass()

# Initialisation du Jostick
pygame.init()
nb_joysticks = pygame.joystick.get_count()
if nb_joysticks==0:
    print 'Pas de Joystick detecte'
mon_joystick = pygame.joystick.Joystick(0)
mon_joystick.init()
jname= mon_joystick.get_name()
#On compte les boutons
nb_boutons = mon_joystick.get_numbuttons()
# Init de la memoire pour les etats des bouton
pygame.event.get()
bstate=map(mon_joystick.get_button,range(nb_boutons))
JoyVtsRob=0
while(bstate[1]!=1):
    time.sleep(0.01)
    for event in pygame.event.get():	#Attente des evenements
        if event.type is JOYAXISMOTION: # evenement : Jostick
            JoyRotRob= - Seuil(mon_joystick.get_axis(0),Seuil=0.1)*RotMax
            Val = mon_joystick.get_axis(5)
            JoyVtsRob = JoyVtsRob + Val*30 - JoyVtsRob/500*30
            #    JoyVtsRob= -(mon_joystick.get_axis(2)+1)*VtsMax/2
            #JoyVtsRob= - Seuil(mon_joystick.get_axis(1),Seuil=0.1)*VtsMax
            VtsM1 = int(JoyVtsRob - JoyRotRob/2)
            VtsM2 = int(JoyVtsRob + JoyRotRob/2)
            portMot.write("VtsM\t%s\t%s \n" % (VtsM1, VtsM2))
            #mon_joystick.get_axis(0)# joystick gauche : gauche/droite
            #mon_joystick.get_axis(1)# joystick gauche : haut/bas
            #mon_joystick.get_axis(2)# gachette arriere
            Pince.Ascenseur(int(-1000*Seuil(mon_joystick.get_axis(4)))) # joystick droite : haut/bas
            #mon_joystick.get_axis(3)# joystick droite : gauche/droite
            pass
        if event.type is 9: # evenement : croix directionnelle
            print 'HAT'
        if (event.type is 10) or (event.type is 11): # evenement : bouton
            #recuperation de l'etat des boutons
            bstate=map(mon_joystick.get_button,range(nb_boutons))
            bstate_int=sum(map(lambda b:int(bstate[b])*(2**b),range(nb_boutons)))
            if bstate_int == 1:
                Pince.Open()
            if bstate_int == 4:
                Pince.Close()



portMot.write("VtsM 0 0 \n")

#Pince.Up()
#Pince.Down()
#time.sleep(1)
#Pince.Stop()

#Pince.Led_OFF()