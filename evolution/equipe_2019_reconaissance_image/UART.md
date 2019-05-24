# Communication UART

La raspberry pi, executant le programme d'asserivssement, doit envoyer des commandes au microcontroleur embarqué du Robot pilotant les roues.
Toutes ces commandes s'effectueront en UART. Il faut donc que la communication UART coté raspberry et coté dsPIC soit maîtrisée et efficace.

## Qu'est-ce que l'UART ?

## Communication Raspberry - Raspberry
Nous commençons par étudier la communication UART coté raspberry.
Pour pouvoir réaliser cela, nous court-circuitons la pins 8 et 10 (ou GPIO14 et GPIO15) de la carte correspondant respectivement aux pins Tx et Rx du port série de la carte.

<p align="center">
  <img src="C:\Users\McDon\Desktop\Projet_SE3A\RobotMT\Trucs_utiles\Presentation\image_pin_rasp.png">
</p> 