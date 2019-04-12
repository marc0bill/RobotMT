from multiprocessing import Process, Queue
import tkinter as tk
from ihm.ihm import *
import time
import serial
import numpy as np
from astar.astar import *

COM_MAIN_PORT='COM34'
COM_MAIN_BAUDRATE = 9600

MAP_X_MAX = 3000.0
MAP_Y_MAX = 2000.0
DXY_ASTAR = 100


class IA:
    def __init__(self, q4Astar, q4Ihm, q4Com):
        self.q4Astar = q4Astar
        self.q4Ihm = q4Ihm
        self.q4Com = q4Com
        x_max=MAP_X_MAX
        y_max=MAP_Y_MAX
        nb_x= int(MAP_X_MAX/DXY_ASTAR)
        nb_y= int(MAP_Y_MAX/DXY_ASTAR)
        self.exitAstar = False
        ## Creation de la Map du pathfinding
        # DistanceObstacleMin=200.0, DistanceObstacleMax=2000.0
        self.map=Pathfinder(x_max, y_max, nb_x, nb_y, 350., 2000.) 
    
    def obs_from_ihm(self, mapTblNode):
        """
        
        """
        # Ajout de de la carte comme obstacles a la Map astar
        ObsMap=np.zeros((self.map.nb_x,self.map.nb_y))+600.
        for ix_obs, obsList in enumerate(mapTblNode):
            for iy_obs, obs in enumerate(obsList):
                if obs > 0:
                    for j in range(-self.map.iObsMax_y,self.map.iObsMax_y):
                        for i in range(-self.map.iObsMax_x,self.map.iObsMax_x):
                            iy=iy_obs+j
                            ix=ix_obs+i
                            if (0<=ix<self.map.nb_x) & (0<=iy<self.map.nb_y):
                                NewDist = sqrt((ix-ix_obs)**2*self.map.delta_x**2+(iy-iy_obs)**2*self.map.delta_y**2)
                                if NewDist < ObsMap[ix,iy]:
                                    ObsMap[ix,iy] = NewDist
        self.map.setObstacle(ObsMap)
        #
    def find_from_ihm(self, startStop):
        print(startStop)#'find_from_ihm','values':[self.robotCoor,self.robotStop]
        self.map.clean()
        NodeFin = self.map.pathfinding(int(startStop[0][0]),int(startStop[0][1]),startStop[0][2],
            int(startStop[1][0]),int(startStop[1][1]), VtsMax=500.,VtsAng=10.)
        TableX=[]
        TableY=[]
        TableAng=[]
        TableTpsTrajet=[]
        TableObs=[]

        if NodeFin is not None:
            NodeFin.getParcours(TableX,TableY,TableAng,TableTpsTrajet,TableObs)
            table = np.array([TableX,TableY,TableAng,TableTpsTrajet,TableObs])
            self.q4Ihm.put([{'name':'path_from_astar','values':table}])



            DeltaAng=np.convolve(TableAng,[1,-1],mode="same")
            PointAnguleux=np.where((DeltaAng>=pi/4.0)|(DeltaAng<=-pi/4.0))
            PointAnguleux=PointAnguleux[0]
            j=0
            NbPt=len(PointAnguleux)*2
            for i in PointAnguleux:
                string="PstCons %s 0 %.4s %s %s %s 4 %s 0.1 10.0 10.0 \n" % (NbPt, TableAng[i], TableX[i], TableY[i],'50','0')
                #string="TuRn %.4s %s %s %s \n" % (j, TableAng[i],Vmax,wait)
                self.q4Com.put([{'name':'write','values':string}]) # pour un envoie de la chaine de carateres sur par port COM
                j=j+1
                string="PstCons %s 0 %.4s %s %s %s 3 %s 0.05 100.0 100.0 \n" % (NbPt, TableAng[i], TableX[i], TableY[i],'50','0')
                #string="GoTo %s %s %s %s %s \n" % (j, TableX[i], TableY[i],Vmax,wait)
                self.q4Com.put([{'name':'write','values':string}])
                j=j+1
        else:
            print("No path")
        #
    def exit_astar(self, values):
        self.exitAstar=True
        #
    def mainloop(self):
        ASTAR_FUNCTION = {'obs_from_ihm':self.obs_from_ihm, 'find_from_ihm':self.find_from_ihm, 'exit':self.exit_astar}
        while not self.exitAstar :
            if not self.q4Astar.empty():
                for dic4Astar in self.q4Astar.get():
                    ASTAR_FUNCTION[dic4Astar['name']](dic4Astar['values'])
#
def process_astar(q4Astar, q4Ihm, q4Com):
    ia = IA(q4Astar, q4Ihm, q4Com)
    ia.mainloop()
#
class ComMain:
    def __init__(self, q4Astar, q4Ihm, q4Com, port, baudrate):
        self.q4Astar = q4Astar
        self.q4Ihm = q4Ihm
        self.q4Com = q4Com
        self.ser = serial.Serial()
        self.ser.baudrate = baudrate
        self.ser.port = port
        try:
            self.open_port()
        except:
            print("No port found")
            pass
        self.exitCom = False
        #
    def open_port(self):
        self.ser.open()
        print("Connected to %s with " % self.ser.port)
        #if Com_Off:
            #self.ser.write(b'Com_Off\n')
        self.ser.flushInput()
        self.ser.flushOutput()
        #
    def write(self,string):
        if self.ser.is_open:
            self.ser.write(str.encode(string))
        else:
            try:
                self.open_port()
                self.ser.write(str.encode(string))
            except:
                print(string[:-1])
        #
    def exit_com(self, values):
        self.exitCom = True
        #
    def write_vts(self, values):
        string = 'VtsM\t{}\t{} \n'.format(values[0], values[1])
        self.write(string)
        #
    def mainloop(self):
        COM_MAIN_FUNCTION = {'write':self.write, 'write_vts':self.write_vts, 'exit':self.exit_com}
        while not self.exitCom :
            if not self.q4Com.empty():
                for dic4Com in self.q4Com.get():
                    COM_MAIN_FUNCTION[dic4Com['name']](dic4Com['values'])
#
def process_com_main(q4Astar, q4Ihm, q4Com):
    comMain = ComMain(q4Astar, q4Ihm, q4Com, COM_MAIN_PORT, COM_MAIN_BAUDRATE)
    comMain.mainloop()
    



def process_ihm(q4Astar, q4Ihm, q4Com):
    root = tk.Tk()
    print(DXY_ASTAR/(MAP_X_MAX/CANVAS_WIDTH))
    ihm = Ihm(q4Astar, q4Ihm, q4Com, master=root, mapResize=MAP_X_MAX/CANVAS_WIDTH, dXY=20.)
    #Ihm = Ihm(q4Astar, q4Ihm, master=root,mapDxy=10, mapResize=5., robotSize=[300,200], robotStart=[150,150,0], robotStop=[2000,1000,0])
    ihm.mainloop()

if __name__ == '__main__':
    q4Astar = Queue()
    q4Ihm = Queue()
    q4Com = Queue()
    pIhm = Process(target=process_ihm, args=(q4Astar, q4Ihm, q4Com))
    pAstar = Process(target=process_astar, args=(q4Astar, q4Ihm, q4Com))
    pComMain = Process(target=process_com_main, args=(q4Astar, q4Ihm, q4Com))
    pIhm.start()
    pAstar.start()
    pComMain.start()
    pIhm.join()
    print('Fin IHM')
    q4Com.put([{'name':'exit','values':0}])
    q4Astar.put([{'name':'exit','values':0}])
    pAstar.join()
    pComMain.join()
#
#def f1(q):
#    time.sleep(5)
#    q.put([42, None, 'hello'])
#
#def f2(q):
#    print('start f2')
#    while q.empty() :
#        print('rien recu')
#        time.sleep(1)
#
#    print(q.get()) # conn est bloquant
#
#if __name__ == '__main__':
#    q = Queue()
#    p1 = Process(target=f1, args=(q,))
#    p2 = Process(target=f2, args=(q,))
#    p1.start()
#    p2.start()
#
#    p1.join()
#    p2.join()




