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
  <img src="..\ressources\Presentation\images\image_pin_rasp.png">
</p> 

Nous ecrivons ensuite un script python envoyant une chaine de caractère en UART et affichant dans la console les données receptionnées (toujours via UART). En executant ce programme, nous pouvons voir que les données envoyées sont correctements reçues.

<p align="center">
  <img src="..\ressources\Presentation\captures\Communication_RASP-RASP_reduite.png">
</p> 

Le programme utilisé est disponible ici : "..\python\Test\com_UART_Rasp_Rasp.py

## Communication Raspberry - PC

La communication UART de la raspberry pi avec elle même étant fonctionnel, nous décidons maintenant de tester la communication entre la raspberry pi est un terminal PC.

Pour cela nous utilisons un câble USB possédant un circuit UART ainsi que les 2 fils Rx et Tx, découpé et dénudé à une extrémité. Nous connectons les fils Rx et Tx du câble respectivement aux pins Tx et Rx de la raspberry et ouvrons un termial série sur le pc (nous avons utilisé termite).

<p align="center">
  <img src="..\ressources\Presentation\images\liaison_uart_raspberry_pc.png"> ////////Inserer une image du câble
</p> 

Nous utilisons le même script que précédemment et vérifions alors que le pc reçois correctement les commandes UART de la raspberry.
*Note: Penser à configurer le même baudrate sur les deux objets communiquant en UART*

La communication UART côté raspberry semble alors maîtrisée et ne devrais pas poser de problèmes par la suite.

## Communication dsPIC - PC

Le protocole de communication UART du dsPIC était déjà écrit et configuré lors du début du projet.
Nous avons dans un premier temps tester cette communication en connectant le dsPIC au PC à l'aide du port USB. Celle-ci s'effectuant correctement, nous avons voulue tester la communication par les pin Rx et Tx du dsPIC (programmée dans le firmware en tant que telle).
Pour cela nous avons connecter notre câble USB au shield présent sur la carte d'electronique de puissance. Néanmoins nous avons été confronté au fait que la communication ne s'établissait que dans un sens. Nous avons alors pris la décision d'enlever ce shield et de repiquer les pins du circuits de puissance (et donc du dsPic) au travers d'un breadbord en solution provisoire. La communication s'est alors établie correctement dans les deux sens.

## Communication Raspberry - dsPIC

Après avoir vérifier les communications Raspberry - PC et dsPIC - PC nous avons pu vérifier la communication UART entre la raspberry et le dsPIC.

Nous avons tout d'abord utiliser un script pyhton envoyant des ordres aux robots comme VtsM 200 200 et demander le renvoie de donnée.

Les programme utilisés sont disponible ici :  "..\python\Test"