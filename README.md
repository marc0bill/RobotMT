# Project Robot Polytech département MT

Le projet consiste à réaliser un robot automne de type "coupe de France de robotique (Eurobot)".
Le robot MT contient une batterie, des moteurs et des capteurs. Des UCEs (Unité de commande électronique) sont mis en place pour gérer les différents périphériques du robot. Ces UCEs ou ECU(acronyme Anglais) se communiquent par le bus CAN. Le choix du protocole CAN est expliqué dans les Wikis.  

## Getting Started
Vous trouvez dans le dossier de ce projet:
-le dossier "carte": les schémas des UCEs employées.
-le dossier "Firmware": les firmwares des UCEs codé en C. (le principe de la compilation conditionnelle est utilisé dans le code => Un seul projet.X peut servir pour implémenter deux firmware différents sur deux UCEs différentes. Il suffit de de changer le nom du node dans le fichier node.h du projet.X )
-Le dossier python: Les codes pythons utilisées.


### Prerequisites

Logiciel à télécharger:

On utilise des contrôleurs de type dsPIC33FJ128MC804(digital signal controler) (Microchip), il faudrait donc télécharger :
```
MPLAPX IDE
```

```
Compilateur XC16
```

Des schémas électriques des UCEs sont disponible en format .pdf, mais si vous souhaitez les modifier ou voir une vision plus profonde, il faudrait télécharger :
```
EAGLE
```

Pour visualiser les données reçus par l'UART sur votre PC, téléchargez une application terminale simple de porte série 
```
Termite
```
ou
```
CoolTerm
```



## Authors

* **Marc Bocquet** - *Initial work* - [marc0bill](https://github.com/marc0bill)

See also the list of [contributors](https://github.com/your/project/contributors) who participated in this project.


