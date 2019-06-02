# -*- coding: utf-8 -*-
"""
Created on Sun May 26 12:40:14 2019

@author: ADMIN
"""

#L'application graphique a été réalisé avec Najlaa. Le but est comme dit dans le code 
#précédent, tracer de façon instantanée les données venant du montage, telles 
#que la consommation du courant. 
# Ici on a créé un excel dans lequel on a sauvegardé des données du code pour 
#ensuite les tracer. 


import tkinter as tk         # Bibliothèque graphique
import matplotlib.pyplot as plt
import numpy as np
from pylab import *
import datetime
from tkinter import * 
import pylab

from xlwt import Workbook
import xlrd
#ON = 1
#date = datetime.datetime.now()
#ladate = str(date)
#print(ladate)

I2=[0]
I1=[0]
I3=[0]
I4=[0]
tab = [str(datetime.datetime.now())]
workbook = Workbook()
i=1
dessin = 'N'

path = r"C:\Users\ADMIN\Downloads\fichier1.xls" #le chemein d'acces pour le fichier contenant les donnes

sheet = workbook.add_sheet("feuille1")
sheet.write(0,1,"temps")
sheet.write(i,1,tab[0])
sheet.write(0,2,"I_3.3V")
sheet.write(i,2,I1[i-1])
sheet.write(0,3,"I_5V")
sheet.write(i,3,I2[i-1])
sheet.write(0,4,"I_12V")
sheet.write(i,4,I3[i-1])
sheet.write(0,5,"I_22V")
sheet.write(i,5,I4[i-1])

while (ON == 1): # 10 est le nombre de cases
    i+=1
    ON = int(input("ON: "))
    #date = datetime.datetime.now()
    tab +=[str( datetime.datetime.now())] 
    #print (len(tab))
    sheet.write(i,1,tab[len(tab)-1])
    I1  +=[float(input("valeur de I1:"))] #doit etre contecter a la bonne sortie
    sheet.write(i,2,I1[len(I1)-1])
    I2  +=[float(input("valeur de I2:"))] #doit etre contecter a la bonne sortie
    sheet.write(i,3,I2[len(I2)-1])
    I3  +=[float(input("valeur de I3:"))] #doit etre contecter a la bonne sortie
    sheet.write(i,4,I3[len(I3)-1])
    I4  +=[float(input("valeur de I4:"))] #doit etre contecter a la bonne sortie
    sheet.write(i,5,I4[len(I4)-1])
    
    workbook.save(path)
    i=i+1

    #classeur = Workbook()
    
    # On ajoute une feuille au classeur
    #sheet = workbook.add_sheet("feuille2")
    #f = classeur.add_sheet('fichie3')
     #Définition de valeurs​
    
    #sheet.write(0,1,"temps")
    #for i in range(len(tab)): 
     #   sheet.write(i+1,1,tab[i])
      #  i=i+1
    
    #sheet.write(0,2,"I_3.3V")
    #for i in range(len(I1)): 
     #   sheet.write(i+1,2,I1[i])
      #  i=i+1 
    #sheet.write(0,3,"I_5V")
    #for i in range(len(I2)): 
     #   sheet.write(i+1,3,I2[i])
      #  i=i+1
    #sheet.write(0,4,"I_12V")
    #for i in range(len(I3)): 
     #   sheet.write(i+1,4,I3[i])
      #  i=i+1
    #sheet.write(0,5,"I_22V")
    #for i in range(len(I4)): 
     #   sheet.write(i+1,5,I4[i])
      #  i=i+1
    
     # Ecriture du classeur sur le disque
    #workbook.save(path)
    #print (u"Fichier créé: {}".format(path))
    ## Fichier créé: C:\chemin\vers\fichier.xls
    
   #i=i+1
dessin = input("afficher la courbe: O/N ")       
if(dessin=='O'):
            # On définit les paramètres du graphique; une seule figure
            fig = pylab.figure(1)
            manager = pylab.get_current_fig_manager()  
            courbe = pylab.plot(tab,I1)
            courbe = pylab.plot(tab,I2)
            courbe = pylab.plot(tab,I3)
            courbe = pylab.plot(tab,I4)
            
            # Définit le titre et xlabel 
            titre     = pylab.title("courant")
            #etiquette = pylab.xlabel("Retrace %f " % (t) )
            # On trace le tout
            manager.canvas.draw()
            # Lancer le graphique avec show() et le maintenir actif avec mainloop.
            manager.show()
            Tk.mainloop()  # Nécessaire pour garder le programme actif
            # On créer un "classeur"
