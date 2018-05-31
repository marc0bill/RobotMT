import pandas as pd
from PortCom import *
import numpy as np
import urllib
import pygame,os
import time

def SeuilX(Val, Seuil):
    if Val>=0:
        return max(Val-Seuil,0)
    else:
        return min(Val+Seuil,0)

class monitoring(object):
    def __init__(self, ListVar):
        self.NbVal = len(ListVar)        
        self.ListVar=ListVar
        self.iVar=0
        self.indexdataframe=0
        self.datas = pd.DataFrame(index=[0])
        for VarName in ListVar:
            self.datas[VarName+"tps"]=0
            self.datas[VarName+"val"]=0
    
    def getValues(self, ser,nbTest=5):
        self.datas[self.ListVar[self.iVar]+"tps"][self.indexdataframe]= time.clock()
        self.datas[self.ListVar[self.iVar]+"val"][self.indexdataframe]= readFloat(ser,self.ListVar[self.iVar]+"?",nbTest=nbTest)
        self.iVar += 1
        if self.iVar >= self.NbVal:
            self.iVar = 0
            self.indexdataframe += 1
    
    def plot(self,x,y,linewidth=2.5, linestyle="-", marker='', RangeX=None, RangeY=None):
        plt.plot(self.datas[x], self.datas[y], linewidth=linewidth, linestyle=linestyle, marker=marker)
        if (RangeX != None):
            Xmax=max(self.datas[x])
            plt.axis([Xmax-RangeX,Xmax, None, None])
        if (RangeY != None):
            Ymax=max(self.datas[y])
            plt.axis([None, None, Ymax-RangeY, Ymax])

    def scatter(self,x,y, s=20, c=u'b', marker=u'o', cmap=None, norm=None, vmin=None, vmax=None, alpha=None, 
        linewidths=None, verts=None, hold=None, RangeX=None, RangeY=None):
        plt.scatter(self.datas[x], self.datas[y], s=s, c=c, marker=marker, cmap=cmap, norm=norm, 
            vmin=vmin, vmax=vmax, alpha=alpha, linewidths=linewidths, verts=verts, hold=hold)
        if (RangeX != None):
            Xmax=max(self.datas[x])
            plt.axis([Xmax-RangeX,Xmax, None, None])
        if (RangeY != None):
            Ymax=max(self.datas[y])
            plt.axis([None, None, Ymax-RangeY, Ymax])
        
class joystick_XBox_class(object):
    def __init__(self, VtsMax=500.0, VtsDeadzone=0.07, VtsOffSet=0.05, VtsAcc=30.0, RotMax=500.0, RotDeadzone =0.07, RotOffSet=0.05, RotAcc=30.0):
        pygame.init()
        nb_joysticks = pygame.joystick.get_count()
        disable=0
        #Bouton pour limiter la vitesse du pointeur
        LIMITER=7
        self.mon_joystick = pygame.joystick.Joystick(0)
        self.mon_joystick.init()
        self.jname= self.mon_joystick.get_name()
        
        #On compte les boutons
        self.nb_boutons = self.mon_joystick.get_numbuttons()
        
        # Init de la memoire pour les etats des bouton
        self.membstate=map(self.mon_joystick.get_button,range(self.nb_boutons))
        
        # Init de la memoire pour l' etats de la croix
        self.memhat=[False,False]
        self.hat=[False,False]
        
        #etat initial des combinaison de touche
        self.bstate_int=0
        
        self.VtsDeadzone=VtsDeadzone
        self.VtsOffSet=VtsOffSet
        self.VtsMax = VtsMax
        self.RotDeadzone =RotDeadzone 
        self.RotOffSet=RotOffSet
        self.RotMax = RotMax
        self.RotAcc = RotAcc
        self.VtsAcc = VtsAcc

        self.VtsD = 0
        self.VtsA = 0
        
        self.axe = [0.0,0.0]
    
    def getState(self):
        ev=pygame.event.get()
        #recuperation de l'etat des boutons
        bstate=map(self.mon_joystick.get_button,range(self.nb_boutons))
        # Permet de verifier si un changement d'etat a eu lieu entre 2 boucles
        bstate_ev=map(lambda c,m:c-m,bstate,self.membstate)
        # Conversion de bstate en decimal pour detecter les conbinaion de touches
        self.bstate_int=sum(map(lambda b:int(self.mon_joystick.get_button(b))*(2**b),range(self.nb_boutons)))
        # Gestion du pointeur avec les analogiques
        self.JoyRotRob= - SeuilX(-self.mon_joystick.get_axis(0) + self.RotOffSet, self.RotDeadzone )*self.RotMax*(1-self.RotDeadzone )
        self.JoyVtsRob= - SeuilX(self.mon_joystick.get_axis(2) + self.VtsOffSet, self.VtsDeadzone)*self.VtsMax*(1-self.VtsDeadzone)
        
        # Gestion des touche HAUT,BAS,GAUCHE,DROITE du clavier avec
        # la croix de la manette
        #nb_hats=self.mon_joystick.get_numhats()
        #if nb_hats>0:   
        #    self.hat=self.mon_joystick.get_hat(0)
        #    hat_ev=map(lambda hc,hm:hc!=hm,self.hat,self.memhat)  
        
        self.membstate=bstate
        self.memhat=self.hat
        
        return [self.JoyVtsRob, self.JoyRotRob]
    def getVtsMString(self):
        self.getState()
        
        if (self.VtsD + self.VtsAcc) < self.JoyVtsRob:
            self.VtsD += self.VtsAcc
        elif (self.VtsD - self.VtsAcc) > self.JoyVtsRob:
            self.VtsD -= self.VtsAcc
        else :
            self.VtsD = self.JoyVtsRob

        if (self.VtsA + self.RotAcc) < self.JoyRotRob:
            self.VtsA += self.RotAcc
        elif (self.VtsD - self.VtsAcc) > self.JoyVtsRob:
            self.VtsA -= self.RotAcc
        else :
            self.VtsA = self.JoyRotRob

        VtsM1 = int(self.VtsD - self.VtsA/2)
        VtsM2 = int(self.VtsD + self.VtsA/2)
        return "VtsM\t%s\t%s \n" % (VtsM1, VtsM2)
        
        
        