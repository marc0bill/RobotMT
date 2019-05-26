# Communication UART

La raspberry pi, executant le programme d'asserivssement, doit envoyer des commandes au microcontroleur embarqué du Robot pilotant les roues.
Toutes ces commandes s'effectueront en UART. Il faut donc que la communication UART coté raspberry et coté dsPIC soit maîtrisée et efficace.

## Qu'est-ce que l'UART ?

/////////////////////////////////////////

Le protocole UART permet de la transmission d'information entre deux systèmes différents. Celui dialogue en "ascii" et permet l'envoie et la réception d'ordre simple de manière continue.

Dans notre cas il nous permet d'envoyer des vitesse tel que : VtsM 100 100

//// Photo Uart avec Vtsm 100 100

Mais aussi de savoir les vitesses réelles des roues par rapport à la consigne.

/////////////////////////////////////////

## Communication Raspberry - Raspberry
Nous commençons par étudier la communication UART coté raspberry.
Pour pouvoir réaliser cela, nous court-circuitons la pins 8 et 10 (ou GPIO14 et GPIO15) de la carte correspondant respectivement aux pins Tx et Rx du port série de la carte.

<p align="center">
  <img src="..\..\Trucs_utiles\Presentation\images\image_pin_rasp.png">
</p> 

Nous ecrivons ensuite un script python envoyant une chaine de caractère en UART et affichant dans la console les données receptionnées (toujours via UART). En executant ce programme, nous pouvons voir que les données envoyées sont correctements reçues.

<p align="center">
  <img src="..\..\Trucs_utiles\Presentation\captures\Communication_RASP-RASP_reduite.png">
</p> 

Le programme utilisé est disponible ici : RobotMT\python\Reconnaissance\Test\com_uart_rasp_rasp.py /////////////////////Reecrire le programme 

## Communication Raspberry - PC

La communication UART de la raspberry pi avec elle même étant fonctionnel, nous décidons maintenant de tester la communication entre la raspberry pi est un terminal PC.

Pour cela nous utilisons un câble USB découpé et dénudé à une extrémité. Nous connectons les fils D+ et D- au pins Rx et Tx de la raspberry et ouvrons un termial série sur le pc (nous avons utilisé termite).

<p align="center">
  <img src="..\..\Trucs_utiles\Presentation\images\liaison_uart_raspberry_pc.png"> ////////Inserer une image du câble
</p> 

Nous utilisons le même script que précédemment et vérifions alors que le pc reçois correctement les commandes UART de la raspberry.
*Note: Penser à configurer le même baudrate sur les deux objets communiquant en UART*

La communication UART côté raspberry semble alors maîtrisée et ne devrais pas poser de problèmes par la suite.

## Communication dsPIC - PC

Le protocole de communicaiton UART du dsPIC était déjà écrit et configuré lors du début du projet.
///////////////////////////////
J'en suis là - Donovan
//////////////////////////////
