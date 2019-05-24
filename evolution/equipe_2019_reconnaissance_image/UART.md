# Communication UART

La raspberry pi, executant le programme d'asserivssement, doit envoyer des commandes au microcontroleur embarqué du Robot pilotant les roues.
Toutes ces commandes s'effectueront en UART. Il faut donc que la communication UART coté raspberry et coté dsPIC soit maîtrisée et efficace.

## Qu'est-ce que l'UART ?

/////////////////////////////////////////

Rédiger l'explication du protocle UART

/////////////////////////////////////////

## Communication Raspberry - Raspberry
Nous commençons par étudier la communication UART coté raspberry.
Pour pouvoir réaliser cela, nous court-circuitons la pins 8 et 10 (ou GPIO14 et GPIO15) de la carte correspondant respectivement aux pins Tx et Rx du port série de la carte.

<p align="center">
  <img src="..\..\Trucs_utiles\Presentation\\images\image_pin_rasp.png">
</p> 

Nous ecrivons ensuite un script python envoyant une chaine de caractère en UART et affichant dans la console les données receptionnées (toujours via UART). En executant ce programme, nous pouvons voir que les données envoyées sont correctements reçues.

<p align="center">
  <img src="..\..\Trucs_utiles\Presentation\captures\Communication RASP-RASP_reduite.png">
</p> 

Le programme utilisé est disponible ici : ////////////////////Reecrire le programme et ajouter le chemin ici

