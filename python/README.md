# Interface graphique du robotMT

## Getting Started

L'interface graphique sera réalisé en code python, dont voici une description rapide:
```
Python is a widely used high-level, general-purpose, interpreted, dynamic programming language. Its design philosophy emphasizes code readability, and its syntax allows programmers to express concepts in fewer lines of code than would be possible in languages such as C++ or Java. The language provides constructs intended to enable clear programs on both a small and large scale.
```
Les instructions qui vont suivre sont dans le but de vous aider à installer un logiciel permettant de simuler votre code python sur votre ordinateur.

### Les prérequis

Pour manipuler simplement votre code python avec un logiciel qui tient la route, nous vous conseillons de télécharger Anaconda.
Anaconda est  une distribution Python. A son installation, Anaconda installera Python ainsi qu’une multitude de packages.  Cela nous évite de nous ruer dans les problèmes d’incompatibilités entre les différents packages.
Finalement, Anaconda propose un outil de gestion de packages appelé Conda. Ce dernier permettra de mettre à jour et installer facilement les librairies dont on aura besoin pour nos développements

### Téléchargement d'Anaconda

Pour télécharger Anaconda, rendez-vous à la page de téléchargement (https://www.anaconda.com/download/).
Prenez la version du binaire qu’il vous faut :
Choisissez le système d’exploitation cible (Windows, Mac, etc…)
Sélectionnez la version 3.X (à l’heure de l’écriture de ces lignes, c’est la version 3.6 qui est proposée)
Si possible, privilégiez la version 64 bits

## Simuler et/ou compiler votre programme

Lors du téléchargement un terminal lié à Anaconda sera également téléchargé. Ça sera sur celui-ci qu'il faudra taper vos commandes pour simuler votre code.
Premièrement faites en sorte de vous retrouver dans la même branche que votre fichier à simuler grâce aux commandes ci-dessous:

### Rappel de commandes sur un terminal

```
cd .. => sert à sortir d'un dossier.
cd => sert à rentrer dans un dossier.
Tab => sert à rechercher un dossier grâce aux premières lettres tapées au clavier au préalable.
```
Une fois dans le bon dossier la prochaine étape est de savoir lancer la compilation et la simulation de votre fichier « .py ».

### Compilation/Simulation

Pour lancer la compilation/simulation de votre fichier, il suffit simplement de rentrer la commande suivante dans le terminal:

```
C:\ProgramData\Anaconda3\python.exe NomFichier.py
```
Si cela ne marche pas voir le lien suivant:
```
https://docs.anaconda.com/anaconda/user-guide/getting-started
```
## Quelques conseils pour débuter à coder

Si vous voulez comprendre la partie interface graphique, le lien suivant vous aidera beaucoup à comprendre:

```
http://apprendre-python.com/page-tkinter-interface-graphique-python-tutoriel
```
Et voici un autre lien qui pourrait également beaucoup vous aider pour vos premiers pas en Python:
```
https://openclassrooms.com/courses/apprenez-a-programmer-en-python
```
## A quoi correspondent les codes déjà écris

Bigblue, littleboy etc.. Sont du code python qui a pour rôle de récupérer les valeurs envoyées en Uart sur un port USB. Une fois exécuté BigBlue vous affiche une interface graphique avec la base de départ et d'arrivé du robot, le code a pour rôle de calculer le chemin le plus cours pour parvenir à l'arriver en évitant les obstacles.

