import pygame
from pygame.locals import *


VTS_ANGULAIRE_MAX=500
VTS_LINERAIRE_MAX=500
nbStep = 5







class Joystick(object):
    def __init__(self):
        # initialisation de python game
        pygame.init()
        # détermination du nombre de joystick connecté
        self.nbJoysticks = pygame.joystick.get_count()
        if self.nbJoysticks==0:
             print('Pas de Joystick détecté')

        # récupération du joystick 0
        self.monJoystick = pygame.joystick.Joystick(0)
        self.monJoystick.init()
        self.jname= self.monJoystick.get_name()
        #On compte les boutons
        self.nbBoutons = self.monJoystick.get_numbuttons()
        # Etats des bouton
        self.bstate=list(map(self.monJoystick.get_button,range(self.nbBoutons)))
        self.bstate_int=0
        self.fast = 1
        self.seuilJoystick = 0.25
        self.seuilGachette = 0.1
        self.LeftAxishorizontal = 0.
        self.LeftAxisVertical = 0.
        self.gachetteAxis = 0.
        self.VtsM1 = int(0)
        self.VtsM2 = int(0)

    def refresh_vts_mot(self):
        def vts_mot():
            def seuil(val,valMin):
                """
                    Fonction de seuillage
                          ^      /
                          |     /
                          |    /
                -valMin___|___/
                      /   |   valMin
                     /    |
                    /     |
                """
                coef = 1/(1 - valMin)
                if val>valMin:
                    return (val-valMin)*coef
                else:
                    if -val>valMin:
                        return (val+valMin)*coef
                    else:
                        return 0
            self.LeftAxishorizontal = seuil(self.monJoystick.get_axis(0),self.seuilJoystick)
            self.LeftAxisVertical = seuil(self.monJoystick.get_axis(1),self.seuilJoystick)
            self.gachetteAxis = seuil(self.monJoystick.get_axis(2),self.seuilGachette)
            self.rotationRobot = - self.LeftAxishorizontal*VTS_ANGULAIRE_MAX/self.fast
            self.vtsRobot = - self.gachetteAxis*VTS_LINERAIRE_MAX*self.fast/nbStep
            self.VtsM1 = int(self.vtsRobot - self.rotationRobot/2)
            self.VtsM2 = int(self.vtsRobot + self.rotationRobot/2)
            print("VtsM\t%s\t%s \n" % (self.VtsM1, self.VtsM2))

        for event in pygame.event.get():    #Attente des événements
            if event.type is JOYAXISMOTION: # événement : Jostick
                #self.monJoystick.get_axis(0) # joystick gauche : gauche/droite
                #self.monJoystick.get_axis(1)# joystick gauche : haut/bas
                #self.monJoystick.get_axis(2)# gachette arrière
                #self.monJoystick.get_axis(3)# joystick droite : haut/bas
                #self.monJoystick.get_axis(4)# joystick droite : gauche/droite
                vts_mot()
                pass
            if event.type is 9: # événement : croix directionnelle
                print('HAT')
            if (event.type is 10) or (event.type is 11): # événement : bouton
                self.bstate=list(map(self.monJoystick.get_button,range(self.nbBoutons)))
                self.bstate_int=sum(list(map(lambda b:int(self.bstate[b])*(2**b),range(self.nbBoutons))))
                
                if self.bstate_int is 1:
                    print('SLOW')
                    self.fast = max(self.fast-1,1)
                    vts_mot()
                if self.bstate_int is 2:
                    #close
                    pass
                if self.bstate_int is 3:
                    #close
                    pass
                if self.bstate_int is 4:
                    print('FAST')
                    self.fast= min(self.fast+1,nbStep)
                    vts_mot()

