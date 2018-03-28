import tkinter as tk
import tkinter.ttk as ttk
import PIL.Image
import PIL.ImageTk

from joystick import Joystick

from scipy.constants import pi
import numpy as np

from multiprocessing import Queue

CANVAS_WIDTH = 600
CANVAS_HEIGHT = 400
COLOR_OBS = '#999999'
COLOR_LINE = '#999999'
COLOR_ROBOT = '#42BCFF'
COLOR_DESTINATION = 'red'
OBSTACLE = -1
CERCLE_JOYSTICK = 5

class Ihm(tk.Frame):
    def __init__(self, q2astar, master, mapDxy=20, mapResize=5., robotSize=[300,200], robotStart=[150,100,0], robotStop=[2000,1000,0]):
        super().__init__(master)
        self.joystick = Joystick()
        self.mapDxy = int(mapDxy)
        self.mapResize = mapResize
        self.nbX = int(CANVAS_WIDTH/mapDxy)
        self.nbY = int(CANVAS_HEIGHT/mapDxy)
        self.robotSize = np.array([robotSize[0],robotSize[1],np.sqrt(300**2+200**2),] )/mapResize/2
        self.robotCoor = robotStart
        self.robotStop = robotStop
        self.mapLstSquare=[]
        self.mapLstPath = []
        # Table des obstacles
        self.mapTblNode = np.zeros((self.nbX,self.nbY))
        self.mapIdSquare = None
        
        self.master.title('Robot')
        # Force la taille de la fenetre
        self.master.geometry("800x480+0+0")
        #supprime la bar de titre de la fenetre
        #self.master.overrideredirect(tk.TRUE)
        
        # Création notebook (onglet)
        self.note = ttk.Notebook(self.master)
        self.tab1 = ttk.Frame(self.note)
        self.tab2 = ttk.Frame(self.note)
        self.tab3 = ttk.Frame(self.note)
        self.note.add(self.tab1, text = "Map",compound=tk.TOP)#, image=scheduledimage)
        self.note.add(self.tab2, text = "Monitor")
        self.note.add(self.tab3, text = "Joystick")

        # Création d'un widget Canvas (zone graphique)
        self.canevas = tk.Canvas(self.tab1, width=CANVAS_WIDTH, height=CANVAS_HEIGHT, bg='white')

        # Création d'un widget Canvas (zone graphique)
        self.canevasJoystick = tk.Canvas(self.tab3, width=110, height=100, bg='white')

        # La méthode bind() permet de lier un événement avec une fonction
        self.canevas.bind('<Button-1>',self.map_clic) # évévement clic gauche (press)
        self.canevas.bind('<B1-Motion>',self.map_drag) # événement bouton gauche enfoncé (hold down)
        self.canevas.bind('<ButtonRelease-1>',self.map_release) # événement bouton gauche relaché

        self.canevas.focus_set()
        self.canevasJoystick.focus_set()
        self.note.pack()
        self.canevas.pack(side=tk.LEFT, padx=5, pady=5)
        self.labVtsM = tk.Label(self.tab3, text='VtsM 0 0')
        self.labGear = tk.Label(self.tab3, text='gear ratio: {}'.format(self.joystick.fast))
        self.labVtsM.grid(column=0, row=0)
        self.labGear.grid(column=0, row=1)
        #self.canevasJoystick.pack(side=tk.LEFT)#, padx=5, pady=5)
        self.canevasJoystick.grid(column=0, row=2)
        
        self.canevasJoystick.create_line(0,50,110,50, fill=COLOR_LINE)
        self.canevasJoystick.create_line(50,0,50,100, fill=COLOR_LINE)
        self.canevasJoystick.create_line(100,0,100,100, fill=COLOR_LINE)
        x = self.joystick.LeftAxishorizontal*40+50 # joystick gauche : gauche/droite
        y = self.joystick.LeftAxisVertical*40+50 # joystick gauche : haut/bas
        z = self.joystick.gachetteAxis*40+50
        self.cercleJoystick = self.canevasJoystick.create_oval(x-CERCLE_JOYSTICK, 
            y-CERCLE_JOYSTICK, x+CERCLE_JOYSTICK, y+CERCLE_JOYSTICK, fill=COLOR_ROBOT,width=0)
        self.rectangleJoystick = self.canevasJoystick.create_rectangle(100,z-2,110,z+2,fill=COLOR_ROBOT,width=0)

        self.b1 = ttk.Button(self.tab1, text ='Save', command = self.map_save)
        self.b2 = ttk.Button(self.tab1, text ='Erase', command = self.map_erase)
        self.b3 = ttk.Button(self.tab1, text ='Reload', command = self.map_reload, style="C.TButton")
        self.b4 = ttk.Button(self.tab1, text ='Find', command = self.map_find)
        self.b1.pack(padx=5,pady=5)
        self.b2.pack(padx=5,pady=5)
        self.b3.pack(padx=5,pady=5)
        self.b4.pack(padx=5,pady=5)

        self.map_reload()
            
        # Création d'un widget Button (bouton Quitter)
        ttk.Button(self.master, text ='Quitter', command = self.master.destroy).pack(side=tk.LEFT,padx=5,pady=5)
        
        self.after(100, self.refresh_joystick)

    def refresh_joystick(self):
        self.joystick.refresh_vts_mot()
        x = self.joystick.LeftAxishorizontal*40+50 # joystick gauche : gauche/droite
        y = self.joystick.LeftAxisVertical*40+50 # joystick gauche : haut/bas
        z = self.joystick.gachetteAxis*40+50
        coords = (x-CERCLE_JOYSTICK, y-CERCLE_JOYSTICK, x+CERCLE_JOYSTICK, y+CERCLE_JOYSTICK)
        self.canevasJoystick.coords(self.cercleJoystick, coords)
        self.canevasJoystick.coords(self.rectangleJoystick, (100,z-2,110,z+2))
        self.labVtsM.config(text='VtsM {} {}'.format(self.joystick.VtsM1,self.joystick.VtsM2))
        self.labGear.config(text='gear ratio: {}'.format(self.joystick.fast))
        self.after(100, self.refresh_joystick)
        

    def map_release(self, event):
        if (self.mapIdSquare is not None) and (self.mapIdSquare >1):
            # position du pointeur de la souris
            X = int(event.x/self.mapDxy)
            Y = int(event.y/self.mapDxy)
            # Ajout d'un element dans la Table des obstacles
            self.mapTblNode[X][Y] = OBSTACLE
    
    def map_clic(self, event):
        """ Gestion de l'événement Clic gauche """
        self.mapIdSquare = None

        # position du pointeur de la souris
        X = int(event.x/self.mapDxy)
        Y = int(event.y/self.mapDxy)
        # Retrait d'un element dans la Table des obstacles
        # L'ajout se fait lors du release du clic gauche
        self.mapTblNode[X][Y] = 0
        X *= self.mapDxy
        Y *= self.mapDxy

        if not(self.mapLstSquare):
            self.mapLstSquare += [self.canevas.create_rectangle(X,Y,X+self.mapDxy,Y+self.mapDxy,fill=COLOR_OBS,width=0)]
            self.mapIdSquare = 0
        else:
            canvas = event.widget
            item_ids = self.canevas.find_closest(event.x, event.y)
            for iC, Carre in enumerate(self.mapLstSquare):
                # coordonnées de l'objet
                coords=self.canevas.coords(Carre)
                [xmin,ymin,xmax,ymax] = coords[:4]
                if xmin<=X<xmax and ymin<=Y<ymax:
                    self.mapIdSquare = iC
                    return
            self.mapLstSquare += [self.canevas.create_rectangle(X,Y,X+self.mapDxy,Y+self.mapDxy,fill=COLOR_OBS,width=0)]
            self.mapIdSquare = iC+1

    def map_drag(self, event):
        """ Gestion de l'événement bouton gauche enfoncé """
        X = int(event.x/self.mapDxy)*self.mapDxy
        Y = int(event.y/self.mapDxy)*self.mapDxy

        if self.mapIdSquare is not None:
            Square = self.mapLstSquare[self.mapIdSquare]
            if X<0 or X>CANVAS_WIDTH or Y<0 or Y>CANVAS_HEIGHT:
                self.canevas.delete(Square)
                self.mapLstSquare.pop(self.mapIdSquare)
                self.mapIdSquare = None
            else:
            # mise à jour de la position de l'objet (drag)
                self.canevas.coords(Square,X,Y,X+self.mapDxy,Y+self.mapDxy)
                #self.mapIdSquare = None
    def rob_coord(self, xya):
        phi = np.arccos(self.robotSize[0]/self.robotSize[2])
        x0 = xya[0]/self.mapResize + self.robotSize[2]*np.cos(xya[2]+phi)
        y0 = xya[1]/self.mapResize + self.robotSize[2]*np.sin(xya[2]+phi)
        x1 = xya[0]/self.mapResize + self.robotSize[2]*np.cos(xya[2]+pi-phi)
        y1 = xya[1]/self.mapResize + self.robotSize[2]*np.sin(xya[2]+pi-phi)
        x2 = xya[0]/self.mapResize + self.robotSize[2]*np.cos(xya[2]+pi+phi)
        y2 = xya[1]/self.mapResize + self.robotSize[2]*np.sin(xya[2]+pi+phi)
        x3 = xya[0]/self.mapResize + self.robotSize[2]*np.cos(xya[2]-phi)
        y3 = xya[1]/self.mapResize + self.robotSize[2]*np.sin(xya[2]-phi)
        return [x0,y0,x1,y1,x2,y2,x3,y3]

    def map_erase(self):
        """ Efface la zone graphique """
        self.mapClickDetection = None
        self.mapLstSquare = []
        self.mapTblNode = np.zeros((self.nbX,self.nbY))
        self.canevas.delete(tk.ALL)

        for i in range(0,self.nbY*self.mapDxy,self.mapDxy):
            self.canevas.create_line(0,i,CANVAS_WIDTH,i, fill=COLOR_LINE)
        for i in range(0,self.nbX*self.mapDxy,self.mapDxy):
            self.canevas.create_line(i,0,i,CANVAS_HEIGHT, fill=COLOR_LINE)
            
    def map_save(self):
        np.savetxt("obstacle.csv", self.mapTblNode, delimiter=";")
    
    def map_reload(self):
        self.map_erase()
        try:
            self.mapTblNode = np.genfromtxt("obstacle.csv", delimiter=";")
        except:
            pass
        Node = np.argwhere((self.mapTblNode>0) & (self.mapTblNode<=2*pi))
        if len(Node)>0:
            X = (Node[0][0]+0.5)*self.mapDxy*self.mapResize
            Y = (Node[0][1]+0.5)*self.mapDxy*self.mapResize
            ang = self.mapTblNode[Node[0][0],Node[0][1]]%(2*pi)
            self.robotCoor = [X, Y, ang]
        self.mapLstSquare = [self.canevas.create_polygon(self.rob_coord(self.robotCoor), fill=COLOR_ROBOT)]
        # STOP
        Node = np.argwhere(self.mapTblNode>2*pi)
        if len(Node)>0:
            X = (Node[0][0]+0.5)*self.mapDxy*self.mapResize
            Y = (Node[0][1]+0.5)*self.mapDxy*self.mapResize
            ang = self.mapTblNode[Node[0][0],Node[0][1]]%(2*pi)
            self.robotStop = [X, Y, ang]
        self.mapLstSquare = [self.canevas.create_polygon(self.rob_coord(self.robotStop), fill=COLOR_DESTINATION)]

        for Node in np.argwhere(self.mapTblNode==OBSTACLE):
            X = Node[0]*self.mapDxy
            Y = Node[1]*self.mapDxy
            self.mapLstSquare += [self.canevas.create_rectangle(X,Y,X+self.mapDxy,Y+self.mapDxy,fill=COLOR_OBS,width=0)]

        
        
    def map_find(self):    
        for i in range(len(self.mapLstPath)):
            self.canevas.delete(self.canevas.delete(self.mapLstPath[i]))
        
        START = self.canevas.coords(self.mapLstSquare[0])[:2]
        STOP = self.canevas.coords(self.mapLstSquare[1])[:2]

        print("envoie de la map d'obstacle fixe au pathfinding")
        #q2astar.put([{'name':'mapTblNode','values':self.mapTblNode}])
        return



if __name__ == '__main__':
    root = tk.Tk()
    q2astar = Queue()
    Ihm = Ihm(q2astar, master=root)
    #Ihm = Ihm(q2astar, master=root,mapDxy=10, mapResize=5., robotSize=[300,200], robotStart=[150,150,0], robotStop=[2000,1000,0])
    Ihm.mainloop()