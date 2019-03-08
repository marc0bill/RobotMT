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


=======
# Projet Robot Polytech département MT

Le département Microélectronique et Télécommunications de Polytech Marseille développe son propre robot de A à Z. Chaque année le projet s'améliore grâce aux élèves de 4ème année. Ce robot, de type coupe de France de robotique, peut se déplacer de façon autonome dans son environnement, déplacer des objets, et ramasser des balles (tennis ou ping-pong).

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

### Prerequisites

What things you need to install the software and how to install them

```
Give examples
```

### Installing

A step by step series of examples that tell you have to get a development env running

Say what the step will be

```
Give the example
```

And repeat

```
until finished
```

End with an example of getting some data out of the system or using it for a little demo

## Running the tests

Explain how to run the automated tests for this system

### Break down into end to end tests

Explain what these tests test and why

```
Give an example
```

### And coding style tests

Explain what these tests test and why

```
Give an example
```

## Contributing

Please read [CONTRIBUTING.md](https://gist.github.com/PurpleBooth/b24679402957c63ec426) for details on our code of conduct, and the process for submitting pull requests to us.

## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/your/project/tags). 

## Authors

* **Marc Bocquet** - *Initial work* - [marc0bill](https://github.com/marc0bill)

See also the list of [contributors](https://github.com/your/project/contributors) who participated in this project.


