# Implementation de reconnaissance d'images au RobotMT

Le but de notre projet est l'implementation d'un algorithme de reconnaissance d'images au RobotMT afin que celui-ci puisse réagir (au travers de deplacements) à la vue de certains objets.
L'algorithme de reconnaissance d'images sera réalisé à l'aide d'un réeau de neuronnes convolutionnel.

## Etat du RobotMT lors du début du projet

Le RobotMT est en cours de devellopement mais déjà fonctionnel.
Les moteurs des roues sont contrôlés par un microcontrôleur dsPIC33JF128MC804. Le firmware est alors écrit en C. Tout les fichiers firmware (.C et .h) sont compris dans le dossier :"RobotMT\firmware\MotorDrive.X"

Sur la carte du dsPIC est ajouté un shield comportant l'elctronique de puissance nécessaire au contrôle moteur (nottament le pont en H).
Sur ce shield est encore rajouté une carte PCB permettant un accès facile aux pins d'alimentation et de communication du dsPIC.

<p align="center">
  <img src="..\ressoures\Presentation\images\PHOOOOTOOOOO.png"> /////Ajouter des images du robot
</p> 

Le robot dispose de plusieurs fonctionnalités qui peuvent lui être commandé par liaison UART. Un détail des commandes UART est disponible ici : RobotMT\firmware\DocUart.pdf

Celles que nous utiliserons principalement pour notre projet sera la suivante : "VtsM vitesseRoue1 vitesseRoue2"
Exemple : VtsM 100 -150

Nous disposons également d'une Raspberry Pi 3 à laquelle est attachée un ecran et disposant également d'une pi camera.

## Objectifs du projet

Les objectifs de notre projet sont les suivants:

- Implementer un algorithme de reconnaissance de certains objets à partir de la camera à l'aide de la Raspberry Pi

- Ecrire un programme d'asservissement des roues du robot en fonction des objets reconnus

- Realiser une communication fonctionnelle entre la Raspberry Pi et le microcontrôleur dsPIC

Le microcontrôleur dsPIC se chargera ensuite de piloter les roues du moteurs en fonction des commandes reçues et à l'aide d'une électronique de puissance. Nous pouvons donc résumer le flow de données de notre projet comme suit:

<p align="center">
  <img src="..\ressources\Presentation\images\schema_projet.png">
</p> 

## Prise en main des outils

Afin de remplir nos objectifs, nous devrons dans un premier temps prendre en main tous les outils dont nous aurons besoins.
Cela comprend :
- Au niveau software:
	- Le firmware de contrôle moteur et de communication UART du robot
	- Le fonctionnement des réseaux de neurones.
	- Les algorithmes de reconnaissance d'images, en particulier celui que nous utiliserons : tensorflow (developpé par Google)
	- Git et GitHub afin de pouvoir travailler efficacement en groupe sur un même projet
- Au niveau hardware:
	- Les circuits électriques de contrôle et de puissance du robot
	- La raspberry Pi

Une documentation détaille la prise en main de ces différents outils.


