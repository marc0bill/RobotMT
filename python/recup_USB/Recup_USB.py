from multiprocessing import Process, Queue
from tkinter import *
from ihm.ihm import *
import time
import serial
import numpy as np
from astar.astar import *


# création de l'objet type serial (port usb)
"""ser = serial.Serial (
port = 'COM8',
baudrate = 57600,
parity = serial.PARITY_NONE,
stopbits = serial.STOPBITS_ONE,
bytesize = serial.EIGHTBITS,
timeout = 1
)"""
fenetre = Tk()
counter=0
x="579.x1810.x16392.x1899"
#x="abcd"
#x = ser.readline()
type_capteur = x[0:3]

canvas = Canvas(fenetre, width=300, height=300, background='white')

l = LabelFrame(fenetre, text="message reçu", padx=20, pady=20)
l.pack(fill="both", expand="yes")
Label(l, text=x).pack()

type_capteur = int(type_capteur)


if type_capteur == 579 :
	distance = x[18:22]
	distance = int(distance)
	l = LabelFrame(fenetre, text="capteur infrarouge", padx=20, pady=20)
	l.pack(fill="both", expand="yes")
	Label(l, text=distance).pack()
	
	if distance < 2000 :
		fenetre_err = Tk()
		#photo = PhotoImage(file="C:/Users/d16022995/Desktop/RobotMT/python/pan_att.jpeg")
		canvas = Canvas(fenetre_err, width=400, height=160, background='white')
		txt = canvas.create_text(200, 40, text="le robot s'approche d'une paroi. Attention!!", font="Arial 16", fill="red")
		#canvas.create_image(200, 80, anchor=NW, image=photo)
		canvas.pack()
		

if type_capteur == 519 :
	distance = x[18:22]
	distance = int(distance)
	l = LabelFrame(fenetre, text="capteur ultrason", padx=20, pady=20)
	l.pack(fill="both", expand="yes")
	Label(l, text=distance).pack()
	
	if distance < 2000 :
		fenetre_err = Tk()
		#photo = PhotoImage(file="pan_att.png")
		canvas = Canvas(fenetre_err, width=400, height=160, background='white')
		txt = canvas.create_text(200, 40, text="le robot s'approche d'une paroi. Attention!!", font="Arial 16", fill="red")
		#canvas.create_image(200, 80, anchor=NW, image=photo)
		canvas.pack()


canvas.pack()
fenetre.mainloop()




"""ouverture de la liasion série
port.open()

vérifie que le port est ouvert
if not (port.isopen()) :
	print ('erreur d\'ouverture du port !')
	exit(1)

Création d'un widget Canvas (zone graphique)"""

