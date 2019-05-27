# Contrôle des moteurs des roues

Le microcontrôleur dsPIC33FJ128MC804 est chargé de l'asservissement des moteurs contrôlant les roues à partir de commande UART (fournis dans notre cas par la raspberry).

La majeure partie des programmes (firmware) codés en langage C contrôlant le robot nous étaient fournis.

## Actionnement des roues

Un premier travail consistait à comprendre le système d'actionnement et de pilotage des roues.

Les moteurs sont contrôlés par l'envoie designaux de PWM ("Pulse width modulation" autrement dit, modulation de largeures d'impulsions). Ces signaux carrés de rapport cyclique variable sont générés par le dsPIC puis envoyés sur un shield comportant une électronique de puissance et notamment un pont en H servant à driver la puissance nécessaire à l'actionnement voulue des machines à courants continues (MCC) étant rattachées à chacune des deux roues. Les sorties du pont en H sont alors des signaux PWM amplifiés. Les MCC "voient" une tension d'induit moyenne proportionnelle aux rapport cyclique de ces signaux. Nous pouvons alors par ce principe obtenir une tension variant entre 0V et la tension d'alimentation.
> Note: dans notre cas la tension d'alimentation est de 22V et non 24V car correspondant à la tension fournie par les futures batteries embarquées dans le robot.

Un contrôle simple, rapide et efficace de la tension d'induit des MCC permet alors de contrôler efficacement la vitesse des roues du robot.

Le pont en H permet également de contrôler le sens de rotation des roues, ce qui sera utile pour ordonner au robot d'effectuer des marches arrières ou des rotations. 

## Compréhension du firmware

Un second travail consistait à comprendre comment le programme fonctionnait afin de pouvoir l'exploiter.

En se plongeant dans le code, nous avons pu nous rendre compte que nous pouvions donner des consignes de vitesses mais aussi de positions et d'angles. Il y avait déja différents modes implantés : avancer en x et y, reculer en x et y, ajustement de l'angle... Il y a la possibilité de définir une vitesse de déplacement simple ou une vitesse angulaire. Il y a des fonctions qui permettent de limiter la vitesse ainsi que l'accélération, d'autres qui calculent les erreurs de positions, vitesses ou angles.
Pour notre projet, nous avons utiliser uniquement la commande de vitesse mais il est possible d'envisager la prise en compte d'autres modes de commande afin d'optimiser l'asservissement du robot.

Le firmware implanté permet de convertir une entrée UART (issue de la raspberry) dans notre cas) en signaux PWM. Dans le fichier "uart.c" se trouve une routine d'interruption permettant de parcourir les données reçue via UART charactère par charactère. Ces charactère vont être regroupés en chaîne de charactère grâce aux espaces. Ces chaînes vont ensuite être traité par le code de "uartassig.c". Celui-ci va permettre de différiencer les ordres reçus.

Le firmware possède plusieurs mode de fonctionnement, cela permet de choisir si le robot reçoit une consigne de position, de vitesse ou d'angle et si nous choisissons d'appliquer l'ordre tel quel ou s'il faut asservir le système en fonction de l'erreur mesurée par rapport à la consigne.

Afin de réaliser nos tests nous sommes rester dans le mode de consigne Consigne.mode = 0 afin de toujours appliquer exactement la consigne d'entrée sans prendre en compte le retour réelle.

## Problèmes rencontrés

Aux premiers abords, le code permettant de piloter les moteurs est extremement dense et il nous a donc fallu beaucoup de temps pour le comprendre et l'utiliser.

