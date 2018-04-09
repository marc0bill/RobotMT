import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
from collections import deque
import time
import serial
import pygame
from pygame.locals import *


VTS_ANGULAIRE_MAX=500
VTS_LINERAIRE_MAX=500
NBSTEP = 5

def find_port(port=None, baudrate = 9600, timeout = 0.1, Requet = "V1R?", portmax = 30,Com_Off=True):
    ser = serial.Serial()
    ser.baudrate = baudrate
    if port==None:
        while True:
            try:
                ser.open()
                String = readInfo(ser,Requet,SizeMax=10)
                if(String[0:3]==Requet[0:3]):
                    print("Connected to %s with Good motor card answer" % ser.port)
                    break
            except:
                pass            
            ser.close()    
            ser.port+=1
            if ser.port > portmax:
                print("No port found")
                break
        ser.flushInput()
        ser.flushOutput()
    else:
        ser.port = port
        try:
            ser.open()
            print("Connected to %s with " % ser.port)
            if Com_Off:
                ser.write(b'Com_Off\n')
            ser.flushInput()
            ser.flushOutput()
        except:
            print("No port found")
            pass
    return ser

def readInfo(ser,Requet,SizeMax=50):
    StrVal=""
    i=0
    String=Requet+" \n"
    ser.write(String)
    actualByte=""
    actualByte=ser.read()
    while actualByte != "\n" :
        StrVal = StrVal+actualByte
        i=i+1
        if(i>=SizeMax):
            print("erreur port com : fin de mot introuvable")
            break
        actualByte=ser.read()
    return StrVal

def readFloat(ser,Requet,nbTest=5):
    for j in range(nbTest):
        String = readInfo(ser,Requet)
        if(String[0:3]==Requet[0:3]):
            return float(String[4:])
    return float('nan')


class Joystick(object):
    def __init__(self):
        # initialisation de python game
        pygame.init()
        # détermination du nombre de joystick connecté
        self.nbJoysticks = pygame.joystick.get_count()
        if self.nbJoysticks==0:
            print('Pas de Joystick détecté')
            self.monJoystick = None
        else :
            # récupération du joystick 0
            self.monJoystick = pygame.joystick.Joystick(0)
            self.monJoystick.init()
            while(self.monJoystick.get_init==False):
                pass
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
        self.gachetteD = 0
        self.gachetteG = 0

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
            valGacG = self.monJoystick.get_axis(2)
            if(self.monJoystick.get_numaxes()>5): # si gachette gauche et droite dissocie (sur raspberryPi)
                valGacD = self.monJoystick.get_axis(5)
                if valGacG != 0:
                    self.gachetteG = -1
                if valGacD != 0:
                    self.gachetteD = -1
                self.gachetteAxis = seuil((valGacG-self.gachetteG)/2.-(valGacD-self.gachetteD)/2.,self.seuilGachette)
            else: # sinon (sur PC)
                self.gachetteAxis = seuil(valGacG,self.seuilGachette)
            self.rotationRobot = - self.LeftAxishorizontal*VTS_ANGULAIRE_MAX/self.fast
            self.vtsRobot = - self.gachetteAxis*VTS_LINERAIRE_MAX*self.fast/NBSTEP
            self.VtsM1 = int(self.vtsRobot - self.rotationRobot/2)
            self.VtsM2 = int(self.vtsRobot + self.rotationRobot/2)
        if self.monJoystick != None:
            for event in pygame.event.get():    #Attente des événements
                if event.type is JOYAXISMOTION: # événement : Jostick
                    #self.monJoystick.get_axis(0) # joystick gauche : gauche/droite
                    #self.monJoystick.get_axis(1)# joystick gauche : haut/bas
                    #self.monJoystick.get_axis(2)# gachette arrière (seulement gauche sous RaspberryPi)
                    #self.monJoystick.get_axis(3)# joystick droite : haut/bas
                    #self.monJoystick.get_axis(4)# joystick droite : gauche/droite
                    #self.monJoystick.get_axis(5)# gachette arrière (droite sous RaspberryPi)
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
                        self.fast= min(self.fast+1,NBSTEP)
                        vts_mot()

class Monitoring(object):
    def __init__(self, ListVar):
        self.NbVal = len(ListVar)        
        self.ListVar=ListVar
        self.iVar=0
        self.indexdataframe=0
        self.datas = pd.DataFrame(index=[0])
        for VarName in ListVar:
            self.datas[VarName+"tps"]=0
            self.datas[VarName+"val"]=0
    
    def get_values(self, ser,nbTest=5):
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




#http://nbviewer.ipython.org/gist/damontallen/5721739
class AnalogData:
    # constr
    def __init__(self, maxLen):
        self.ax = deque([0.0]*maxLen)
        self.ay = deque([0.0]*maxLen)
        self.maxLen = maxLen

    # ring buffer
    def addToBuf(self, buf, val):
        if len(buf) < self.maxLen:
            buf.append(val)
        else:
            buf.pop()
            buf.appendleft(val)

    # add data
    def add(self, data):
        assert(len(data) == 2)
        self.addToBuf(self.ax, data[0])
        self.addToBuf(self.ay, data[1])
    
# plot class
class AnalogPlot:
    # constr
    def __init__(self, analogData):
        # set plot to animated
        self.fig, axplt = plt.subplots() #plt.ion() 
        self.axline, = axplt.plot(analogData.ax)
        self.ayline, = axplt.plot(analogData.ay)
        plt.ylim([-500, 500])

    # update plot
    def update(self, analogData):
        self.axline.set_ydata(analogData.ax)
        self.ayline.set_ydata(analogData.ay)
        self.fig.canvas.draw()
        #self.fig.canvas.flush_events()
        plt.draw()


if __name__ == '__main__':
    ser=find_port(port='COM34')
    monitor=Monitoring(["V1R", "V1C","dOR"])
    if ser.is_open:
        monitor.getValues(ser)
    joystick = Joystick()
    time_init=time.clock()

#