# Récupération des données en USB

## Présentation 

Le fichier Recup_USB.py est une application facile à prendre en main de la récupération des messages envoyés en Uart sur les ports COM.
Ce code récupère, la valeur reçus sur le port USB, regarde de quel type de message il s’agit (Node US, Node IR etc...). Il va traiter ses données de façon à avoir un message d'erreur quand un obstacle est trop proche d'un des capteurs. Malheureusement le message est seulement visuel sur l'interface graphique et n'est donc pas renvoyé à la Node moteur pour dire au moteur de vite reculer car il y a un obstacle.

![alt text](https://github.com/marc0bill/RobotMT/blob/master/ressourceWikiReadme/Capture%20projet%20python.PNG)

Le fichier Test est simplement un fichier pour tester des petites parties de code pour mieux comprendre leurs fonctionnements.

Le fichier Pan_att.jpg est la photo qu'on a voulu insérer dans le message d'erreur de l'interface graphique de Recup_USB.

## Amélioration possible

Amélioration de la récupération des données sur le port COM. Les messages ne se finissent pas par "\n" donc le "readline()" ne marche pas bien.
La lecture du port COM n'est pas en temps réel ce qui est un grand problème quand on parle de système embarqué temps réel. 
Peut-être utiliser le multi-processing pour récupérer plusieurs messages et les afficher en même temps en temps réel.
Envois d'un message d'erreur à la Node moteur quand il y a un obstacle trop proche.
