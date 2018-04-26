import tkinter as tk
import tkinter.ttk as ttk

import numpy as np

class Application(tk.Frame):
    def __init__(self, master=None):
        super().__init__(master)
        
        self.mapDxy = 20
        self.mapWidth = 600
        self.mapHeight = 400

        self.mapLstSquare=[]
        # Table des obstacles
        self.mapTblNode = np.zeros((int(self.mapWidth/self.mapDxy),int(self.mapHeight/self.mapDxy)))
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
        self.note.add(self.tab1, text = "Map",compound=tk.TOP)#, image=scheduledimage)
        self.note.add(self.tab2, text = "Monitor")

        # Création d'un widget Canvas (zone graphique)
        self.canevas = tk.Canvas(self.tab1, width = self.mapWidth, height =self.mapHeight, bg ='white')

        # La méthode bind() permet de lier un événement avec une fonction
        self.canevas.bind('<Button-1>',self.map_clic) # évévement clic gauche (press)
        self.canevas.bind('<B1-Motion>',self.map_drag) # événement bouton gauche enfoncé (hold down)
        self.canevas.bind('<ButtonRelease-1>',self.map_release) # événement bouton gauche relaché

        self.canevas.focus_set()
        self.note.pack()
        self.canevas.pack(side=tk.LEFT, padx=5, pady=5)
        
        self.b1 = ttk.Button(self.tab1, text ='Save', command = self.map_save)
        self.b2 = ttk.Button(self.tab1, text ='Erase', command = self.map_erase)
        self.b3 = ttk.Button(self.tab1, text ='Reload', command = self.map_reload, style="C.TButton")
        self.b4 = ttk.Button(self.tab1, text ='Find', command = self.map_find, state=tk.DISABLED )
        self.b1.pack(padx=5,pady=5)
        self.b2.pack(padx=5,pady=5)
        self.b3.pack(padx=5,pady=5)
        self.b4.pack(padx=5,pady=5)

        self.map_reload()

        # Création d'un widget Button (bouton Quitter)
        ttk.Button(self.master, text ='Quitter', command = self.master.destroy).pack(side=tk.LEFT,padx=5,pady=5)

    def map_release(self, event):
        # position du pointeur de la souris
        X = int(event.x/self.mapDxy)
        Y = int(event.y/self.mapDxy)
        # Ajout d'un element dans la Table des obstacles
        self.mapTblNode[X][Y] = 1
    
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
            self.mapLstSquare += [self.canevas.create_rectangle(X,Y,X+self.mapDxy,Y+self.mapDxy,fill='green')]
            self.mapIdSquare = 0
        else:
            for iC, Carre in enumerate(self.mapLstSquare):
                # coordonnées de l'objet
                [xmin,ymin,xmax,ymax] = self.canevas.coords(Carre)
                if xmin<=X<xmax and ymin<=Y<ymax:
                    self.mapIdSquare = iC
                    return
            self.mapLstSquare += [self.canevas.create_rectangle(X,Y,X+self.mapDxy,Y+self.mapDxy,fill='green')]
            self.mapIdSquare = iC+1

    def map_drag(self, event):
        """ Gestion de l'événement bouton gauche enfoncé """
        X = int(event.x/self.mapDxy)*self.mapDxy
        Y = int(event.y/self.mapDxy)*self.mapDxy

        if self.mapIdSquare is not None:
            Square = self.mapLstSquare[self.mapIdSquare]
            # limite de l'objet dans la zone graphique
            if X<0: X=0
            if X>self.mapWidth: X=self.mapWidth
            if Y<0: Y=0
            if Y>self.mapHeight: Y=self.mapHeight
            # mise à jour de la position de l'objet (drag)
            self.canevas.coords(Square,X,Y,X+self.mapDxy,Y+self.mapDxy)

    def map_erase(self):
        """ Efface la zone graphique """
        self.mapClickDetection = None
        self.mapLstSquare = []
        self.mapTblNode = np.zeros((int(self.mapWidth/self.mapDxy),int(self.mapHeight/self.mapDxy)))
        self.canevas.delete(tk.ALL)
        for i in range(int(self.mapHeight/self.mapDxy)):
            self.canevas.create_line(0,self.mapDxy*i,self.mapWidth,self.mapDxy*i, fill='#999999')
        for i in range(int(self.mapWidth/self.mapDxy)):
            self.canevas.create_line(self.mapDxy*i,0,self.mapDxy*i,self.mapHeight, fill='#999999')
    
    def map_save(self):
        np.savetxt("obstacle.csv", self.mapTblNode, delimiter=";")
    
    def map_reload(self):
        self.map_erase()
        try:
            self.mapTblNode = np.genfromtxt("obstacle.csv", delimiter=";")
        except:
            pass
        for Node in np.argwhere(self.mapTblNode>0):
            X = Node[0]*self.mapDxy
            Y = Node[1]*self.mapDxy
            self.mapLstSquare += [self.canevas.create_rectangle(X,Y,X+self.mapDxy,Y+self.mapDxy,fill='green')]
        
    def map_find(self):
        return


if __name__ == '__main__':
    root = tk.Tk()
    app = Application(master=root)
    app.mainloop()