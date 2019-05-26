# Asservissement

L'asservissement du robot est le lien (sous forme de programme python) entre les résultats de l'algorithme tensorflow et les ordres de commande des roues.

L'objectif est de faire en sorte que les roues s'actionnent de manière cohérente par rapport aux objets détectés.
A titre d'éxemple, le scénario que nous avons considéré est le suivant : le robot doit suivre un certain objet et en fuir un autre.

## Entrées et sorties du programme d'asservissement

A l'heure actuelle, l'entrée de ce programme est un tableau de listes python comportant les résultats de l'algorithme tensorflow, préformattés de manière à fournir le nom de l'objet reconnus, le degré de certitude de la reconnaissance, et les coordonnées des 2 points délimitant la "box" de l'objet reconnu afin de le situer dans le plan de la caméra.

Les sorties du programme sont des chaines de caractères envoyées en UART au microcontrôleur dsPIC qui se chargera de piloter les roues en fonction.

## Mode d'asservissement en 2 temps

Nous avons commencé par considérer un asservissement en 2 temps. A la reconnaissance d'un objet (à fuir ou à suivre), le robot va dans un premier temps effectuer une rotation sur place afin de se positionner en face de cet objet. Dans un second temps, il va s'approcher ou s'éloigner de ce dernier en fonction du type d'objet et de sa distance à celui-ci. Voici le logigramme de l'algorithme du programme principal étant éxécuté par le robot, en détaillant l'asservissement:

<p align="center">
  <img src="..\ressources\Presentation\images\logigramme_algo.png"> 
</p>

### Formattage des entrées

Lors de la récupération des entrées du programme, nous créons un objets python définissant l'objet reconnu.
L'algorithme tensorflow nous permet de récuperer les coordonnées des points définissant une "box" dans laquelle est contenu l'objet dans le plan de la caméra. Ces coordonnées sont normalisées (par tensorflow) dans un plan ayant pour origine le coin supérieur gauche du champ de reconnaissance (c'est à dire de la vidéo récupérée). Le coin inférieur droit a alors pour coordonnées (1,1). Une première étape consiste à effectuer un changement de repère afin que ces coordonnées soient exprimées dans un repère ayant pour origine le centre du champ de reconnaissance. Le coin supérieur gauche aura alors pour coordonnées (-0.5, 0.5) et le coin supérieur droit (0.5, -0.5). Cela sera plus adapté pour les prises de décision.
Nous déduisons ensuite la position (sur l'axe des abscisses) du centre de l'objet ainsi que plusieurs autres caractéristiques telles que ses dimensions. Ces valeurs seront utiles lors des calculs suivants. Ainsi une fois crée, l'objet python possède les attributs suivants:
- nom de l'objet reconnu
- degré de certitude de la reconnaissance
- coordonnées des 2 points délimiants la box (dans le nouveau repère)
- distance (selon x) du centre de la box à l'origine du repère
- longueur et largeur de la box
- diagonale de la box (taille absolue de l'objet)
- ratio de la diagonale de la box par rapport à la diagonale du champ de reconnaissance (taille relative de l'objet)

### Phase d'alignement

#### Déclenchement

La phase d'alignement est déclenchée lorsque le robot reconnait un objet qui doit lui entrainer une réaction (que ce soit une fuite ou une poursuite) et qu'il n'est pas au préalablement en face de ce dernier.

Ainsi la consigne d'alignement est une distance entre le centre de la box et l'origine du repère de 0 (puisque nous avons changé de repère). Nous accordons cependant une certaine tolérance par rapport à cette consigne de manière à ce que le robot ne corrige pas son alignement en permanence sans jamais arrivé exactement à remplir la consigne.

#### Définition de la vitesse et du sens de rotation

Si la distance du centre de la box à l'origine est supérieure à la tolérance, nous définissions une vitesse de rotation à l'aide d'un correcteur proportionnel. Ainsi plus le centre de la box est loin de l'origine du repère (c'est à dire plus le robot est décentré par rapport à l'objet), plus la vitesse de rotation sera élevée.
Le signe de la distance du centre de la box à l'origine du repère définira le sens de rotation.

#### Commande de rotation

Afin d'effectuer une rotation sur place, la vitesse déterminée précédement est assignée à une roue, et son opposé et assignée à l'autre roue. En fonction du signe de celle-ci, le robot effectuera une rotation vers la droite ou vers la gauche.

Le programme d'asservissement comporte ensuite un temps de pause pour permettre au robot de répondre à la consigne.
Une fois ce délais passé le programme d'asservissement reboucle est l'alignement est réévalué. Si celui-ci n'est toujours pas satisfaisant, une nouvelle consigne d'alignement est déclenchée. Cependant si l'alignement entre dans l'intervalle de tolérance, la phase de positionnement est autorisée.

### Phase de positionnement

#### Déclenchement

La phase de positionnement est déclenchée uniquement lorsque la phase d'alignement a jugé un alignement acceptable (principe de l'asservissment en 2 temps).

#### Définition de la vitesse et du sens de déplacement

La taille relative de la box (déterminée lors de la construction de l'objet python) va permettre de determminer la vitesse et le sens de rotation.
Dans un premier temps, une consigne de taille relative est attribuée en fonction de l'objet reconnu (si celui-ci est à suivre ou à fuir).
Ensuite, la taille relative de la box est comparée à cette consigne. Si la taille effective est plus grande que la consigne, le robot est trop près de l'objet et doit donc reculer, la vitesse appliquée aux roues sera donc négative. A l'inverse, si la taille mesurée est plus petite que la consigne, le robot est trop loin de l'objet. il doit donc avancer et la vitesse appliquée aux roues sera positive.
Là encore, nous effectuons la comparaison mesure/consigne en considérant une certaine tolérance.
Afin de déteminer la valeur de la vitesse à appliquer aux deux roues, nous utilisons encore une fois un correcteur proportionnel, appliqué à la différence entre la consigne et la mesure de la taille. Ainsi plus le robot est loin de la consigne voulue (dans un sens ou dans l'autre), plus il se deplacera rapidement.

### Commande de déplacement

Afin d'effectuer un déplacement en ligne droite, la même vitesse est assignée aux 2 roues. En fonction du signe de celle-ci , le robot avancera ou reculera.

Le programme d'asservissement comporte ensuite un temps de pause pour permettre au robot de répondre à la consigne.
Une fois ce délais passé le programme d'asservissement reboucle est la taille de l'objet est réévaluée. Si celle-ci n'est toujours pas satisfaisante, une nouvelle consigne de positionnement est déclenchée. Cependant si l'alignement entre dans l'intervalle de tolérance autour de la consigne, le robot est correctement positionné et s'arrête.

## Mode d'asservissment 1 temps

Afin d'optimiser la fluidité et la rapidité des déplacements du robot, un mode d'asservissement en un seul temps serait préférable au système en deux temps que nous avons implémenté.
Le fonctionnement en différents modes est pris en compte dans le programme principale par une évaluation de la constante "mode" du fichier constante.py.
Un mode d'asservissement en 1 temps consisterais à évaluer la consigne d'angle et de position en même temps, puis que le robot effectue un seul mouvement corrigeant son alignement et son eloignement par rapport à l'objet en même temps. Nous n'avons pas eu le temps d'implementer ce mode. Les fonctions et la partie du programme principale le concernant sont donc à écrire.


## Perspectives d'amélioration

Notre asservissement primaire peut être amélioré de bien des façons. Voici quelques idées auxquelles nous avons pensé mais que nous n'avons malheuresement pas eu le temps d'implementer:

- Définition de degrés de priorités entre les objets
	> Que se passerait-il si le robot reconnaissait plusieurs objets en même temps? Il est (à l'heure actuelle) programmé pour reconnaitre jusqu'à 4 objets en même temps (cela est décrit dans notre documentation concernant tensorflow). Devrait-il fuir un objet plutôt que de suivre un autre? Si 2 objets sont à suivre, lequel est le plus important? Il serait intéressant de définir certains niveau de priorité entre les objets ou du moins les actions à effectuer.
- Ajustement des constantes d'asservissement 
	> L'asservissement ayant écrit durand les dernièes phases de notre projets (suite aux NOMBREUX problèmes rencontrés), les constantes d'asservissement ont étais définit de manière arbitraire et non à la suite de test rigoureux. Les constantes en questions sont contenues dans le fichier constantes.py et sont les suivantes:
	- TOLERANCE_ANGLE : intervalle de tolérance d'alignement du robot autour de la consigne
	- TOLERANCE_DISTANCE : intervalle de tolérance d'éloignement du robot par rapport à la consigne
	- KA : correcteur proportionnel de vitesse de rotation
	- KP : correcteur proportionnel de vitesse de positionnement
	- DELAIS_ALIGNEMENT : délais en secondes laissé au robot pour ajuster son alignement à la suite d'une commande
	- DELAIS_POSIITONNEMENT : délais en secondes laissé au robot pour ajuster sa position à la suite d'une commande
	- DISTANCE_SUIVIE : consigne de taille relative que la box de l'objet doit avoir lorsque le robot poursuit l'objet reconnus
	- DISTANCE_FUITE : consigne de taille relative que la box de l'objet doit avoir lorsque le robot fuit l'objet reconnus
	Afin d'ajuster toutes ces constantes efficacement, il serait peut-être judicieux d'ecrire pour chacune d'entre elles un script python de test renvoyant des informations en permance sur ce que voit le robot (par éxemple dans la console de la raspberry). Ainsi en approchant, eloignant, decentrant des objets, ect... et en observant les réponses du robot, nous pourrions efficacement ajuster ces réglages.
- Optimisation du traitement des résulats tensorflow
	> A chaque action, une réanalyse complete du champ de vision du robot est effectuée. Nous pouvons peut-être imaginer un système de verrouillage sur les objets voulus afin de gagner en temps d'execution et donc en temps de reaction du robot.
- Optimisation des correcteurs
	> Nous avons utiliser des correcteurs proportionnels qui sont la forme la plus simple de correctuers. Nous pouvons imaginer remplacer ces derniers par des correcteurs intégrals ou à action dérivé pour respectivement améliorer la précision ou la rapidité du système (voir d'autres types de correcteurs selon les besoins).
- Asservissement des pinces
	> Le robot possède des pinces en façade avant. Nous pouvons imaginer un programme d'asservissement de ces dernières une fois la position corrigé correctement afin qu'il puisse récupérer un objet posé au sol.


