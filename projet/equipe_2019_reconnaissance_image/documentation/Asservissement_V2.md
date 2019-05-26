# Asservissement

L'asservissement du robot est le lien (sous forme de programme python) entre les résultats de l'algorithme tensorflow et les ordres de commande des roues.

L'objectif est de faire en sorte que les roues s'actionnent de manière cohérente par rapport aux objets détectés.
A titre d'éxemple, le scénario que nous avons considéré est le suivant : le robot doit suivre un certain objet et en fuire un autre.

## Entrées et sorties du programme d'asservissement

A l'heure actuelle, l'entré de ce programme est un tableau de listes python comportant les résultats de l'algorithme tensorflow, préformattés de manière à fournier le nom de l'objet reconnus, le degré de certitude de la reconnaissance, et les coordonnées des 2 points délimitant la "box" de l'objet reconnus afin de le situer dans le plan de la caméra.contrô

Les sortie du programme sont des chaines de caractères envoyées en UART au microcontrôleur dsPIC qui se cahrgera de piloter les roues en fonction.

## Mode d'asservissement en 2 temps

Nous avons commencé par considérer un asservissement en 2 temps. A la reconnaissance d'un objet (à fuir ou à suivre), le robot va dans un premier temps effectuer une rotation sur place afin de se positionner en face de cet objet. Dans un second temps, il va s'approcher ou s'éloigner de ce dernier en fonction du type d'objet et de sa distance à celui-ci.

### Formattage des entrées

Lors de la récupération des entrées du programmes, nous créons un objets python définissant l'objet reconnues.
L'algorithme tensorflow nous permet de récuperer les coordonnées des points définissant une "box" dans lequel est contenue l'objet dans le plan de la caméra. Ces coordonnées sont normalisées (par tensorflow) dans un plan ayant pour origine le coin supérieur gauche du champ de reconnaissance (c'est à dire de la vidéo récupérée). Le coin inférieur droit a alors pour coordonnées (1,1). Une première étape consiste à effectuer un changement de repère afin que ces coordonnées soient exprimées dans un repère ayant pour origine le centre du champ de reconnaissance. Le coin supérieur gauche aura alors pour coordonnées (-0.5, 0.5) et le coin supérieur droit (0.5, -0.5). Cela sera plus adaptés pour les prises de décision.
Nous déduisons ensuite la position (sur l'axe des abscisses) du centre de l'objet ainsi que plusieurs autres caractéristiques telles que ses dimensions. Ces valeurs seront utiles lors des calculs suivants. Ainsi une fois crée, l'objet python possède les attributs suivants:
- nom de l'objet reconnus
- degré de certitude de la reconnaissance
- coordonnées des 2 points délimiants la box (dans le nouveau repère)
- distance (selon x) du centre de la box à l'origine du repère
- longueur et largeur de la box
- diagonale de la box (taille absolue de l'objet)
- ratio de la diagonale de la box par rapport à la diagonale du champ de reconnaissance (taille relative de l'objet)

### Phase d'alignement

#### Déclenchement

La phase d'alignement est déclenchée lorsque le robot reconnait un objet qui doit lui entrainee une réaction (que ce soit une fuite ou une poursuite) et qu'il n'est pas au préalablement en face de ce dernier.

Ainsi la consigne d'alignement est une distance entre le centre de la box et l'origine du repère de 0 (puisque nous avons changé de repère). Nous accordons cependant une certaine tolérance par rapport à cette consigne de manière à ce que le robot ne corrige pas son alignement en permanence sans jamais arrivé exactement à remplir la consigne.

#### Définition de la vitesse et du sens de rotation

Si cette distance est supérieur à la tolérance, nous définissions une vitesse de rotation à l'aide d'un correcteur proportionnel. Ainsi plus le centre de la box est loin de l'originr du repère (c'est à dire plus le robot est décentré par rapport à l'objet), plus la vitesse de rotation sera élevée.
Le signe de la distance du centre de la box à l'origine du repère définiras le sens de rotation.

#### Commande de rotation

Afin d'effectuer une rotation sur place, la vitesse déterminées précédement est assignée à une roue, et son opposé et assignée à l'autre roue. En fonction du signe de celle-ci, le robot effectuera une rotation vers la droite ou vers la gauche.
Le programme d'asservissement comprend ensuite un temps de pause pour permettre au robot de répondre à la consigne.

Une fois ce délais passé le programme d'asservissement reboucle est l'alignement est réévalué. Si celui-ci n'est toujours pas satisfaisant, une nouvelle consigne d'alignement est déclenchée. Cependant si l'alignement entre dans l'intervalle de tolérance, la phase de positionnement est autorisée.

### Phase de positionnement

#### Déclenchement

La phase d'alignement est déclenchée uniquement lorsque la phase d'alignement a jugé un alignement acceptable (principe de l'asservissment en 2 temps).

#### Définition de la vitesse et du sens de déplacement










## Perspectives d'amélioration
- Définir des degrés de priorités entre les objets
- Ajuster les constantes d'asservissmenet (correcteurs proportionnels, consignes de tailles, tolérances aux consignes...) en écrivant des cripts renvoyants en permanence (dans la console par exemple) des informations sur ce que le robot voit. Il faut ensuite éxécuter ces différents scripts en éloignant, approchants et tournant autour des objets au robot afin d'affiner ces constantes.
- A chaque action, une réanalyse complete du champ de vision du robot est effectuer. On peut peut être imaginer un système de verrouillage sur les objets voulus afin de gagner en temps d'execution et donc en temps de reaction du robot.


