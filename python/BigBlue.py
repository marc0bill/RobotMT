from multiprocessing import Process, Queue
import tkinter as tk
from ihm.ihm import Ihm
import time




from astar.astar import *

import numpy as np




def process_ihm(q2astar):
    root = tk.Tk()
    ihm = Ihm(q2astar, master=root)
    #Ihm = Ihm(q2astar, master=root,mapDxy=10, mapResize=5., robotSize=[300,200], robotStart=[150,150,0], robotStop=[2000,1000,0])
    ihm.mainloop()

if __name__ == '__main__':
    q2astar = Queue()
    pIhm = Process(target=process_ihm, args=(q2astar,))
    pIhm.start()
    pIhm.join()
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






# 
# START=[300,300]
# 
# 
# x_max=3000.0
# y_max=2000.0
# nb_x=30
# nb_y=20
# 
# 
# 
# 
# 
# ## Creation de la Map du pathfinding
# Map=Pathfinder(x_max, y_max, nb_x, nb_y, 150., 500.)
# # ATTENTION LES TYPES DOIVENT ETRE RESPECTER : CORRIGER CELA DANS LE SOURCE astar.py
# 
# # Ajout de de la carte comme obstacles a la Map astar
#         ObsMap=np.zeros((self.nbX,self.nbY))+600.
#         for ix_obs, obsList in enumerate(self.mapTblNode):
#             for iy_obs, obs in enumerate(obsList):
#                 if obs > 0:
#                     for j in range(-Map.iObsMax_y,Map.iObsMax_y):
#                         for i in range(-Map.iObsMax_x,Map.iObsMax_x):
#                             iy=iy_obs+j
#                             ix=ix_obs+i
#                             if (0<=ix<self.nbX) & (0<=iy<self.nbY):
#                                 NewDist = sqrt((ix-ix_obs)**2*Map.delta_x**2+(iy-iy_obs)**2*Map.delta_y**2)
#                                 if NewDist < ObsMap[ix,iy]:
#                                     ObsMap[ix,iy] = NewDist   
#         Map.setObstacle(ObsMap)
#         # Calcul du plus court Chemin
        # 
#         Map.clean()
#         NodeFin = Map.pathfinding(int(START[0]*self.mapResize),int(START[1]*self.mapResize),0,
#                                   int(STOP[0]*self.mapResize),int(STOP[1]*self.mapResize),
#                                   VtsMax=500.,VtsAng=10.)
#         TableX=[]
#         TableY=[]
#         TableAng=[]
#         TableTpsTrajet=[]
#         TableObs=[]
#         if NodeFin is not None:
#             NodeFin.getParcours(TableX,TableY,TableAng,TableTpsTrajet,TableObs)
# 
# 
#             XXX=np.array(TableX[1:-1])/self.mapResize
#             YYY=np.array(TableY[1:-1])/self.mapResize
#             for i, X in enumerate(XXX):
#                 self.mapLstPath += [self.canevas.create_rectangle(X,YYY[i] ,X+self.mapDxy,YYY[i]+self.mapDxy,fill='blue',width=0)]
# 
#             DeltaAng=np.convolve(TableAng,[1,-1],mode="same")
#             PointAnguleux=np.where((DeltaAng>=pi/4.0)|(DeltaAng<=-pi/4.0))
#             PointAnguleux=PointAnguleux[0]
#             j=0
#             NbPt=len(PointAnguleux)*2
#             for i in PointAnguleux:
#                 String="PstCons %s 0 %.4s %s %s %s 4 %s 0.1 10.0 10.0 \n" % (NbPt, TableAng[i], TableX[i], TableY[i],'50','0')
#                 #String="TuRn %.4s %s %s %s \n" % (j, TableAng[i],Vmax,wait)
#                 #ser.write(String) # pour un envoie de la chaine de carateres sur par port COM
#                 print(String[:-1])
#                 j=j+1
#                 String="PstCons %s 0 %.4s %s %s %s 3 %s 0.05 100.0 100.0 \n" % (NbPt, TableAng[i], TableX[i], TableY[i],'50','0')
#                 #String="GoTo %s %s %s %s %s \n" % (j, TableX[i], TableY[i],Vmax,wait)
#                 #ser.write(String) # pour un envoie de la chaine de carateres sur par port COM
#                 print(String[:-1])
#                 j=j+1
#         else:
#             print("No path")
