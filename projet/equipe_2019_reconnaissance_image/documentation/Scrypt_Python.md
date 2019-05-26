Nous avons donc créer un scrypt pyhton qui permet en fonction des éléments issues de tensorflow, c'est à dire le nom de l'objet et ces positions spatiales, de renvoyer un ordre UART compréhensible au dsPIC.
Voici so descriptif ci-dessous:

###Main_V2.py

Nous prenons en entrée le tableau issue du programme tensorflow qui analyse les images frame par frame et dedans nous cherchons si l'objet désiré y est présent.

S'il est présent alors nous pouvons commencer à donner les ordres d'alignement et de déplacement. Nous avons réaliser deux mode, le Mode 0 où le robot tourne et avance en deux temps et le mode 1 où celui-ci effectue les deux en même temps. Nous nous poserons dans le mode 0 pour l'explication du code.

Tout d'abord la fonction main va appeler des fonction afin de savoir s'il faut reculer ou avancer en fonction de la position et de la taille de l'objet.

## Asserv_V2.py

En effet, les fonctions dans Asserv_V2.py permmettent de savoir l'action à effectuer en fonction de la position relative de l'objet par rapport au robot.

Si le robot n'est pas aligné avec l'objet alors il va tout d'abord calculer l'erreur de position est via un facteur k (correcteur proportionnel) il va ajuster la position du robot en appelant les fonctions tourner_sur_place dans Mouvement.py .

Si le robot est aligné alors il va calculer la taille de l'objet par rapport à la taille de l'image et il va reculer ou avancer afin de ne pas être trop loin ni trop près du robot en appelant les fonction avancer ou reculer de Mouvement.py .
## Mouvement.py

Tout d'abord la fonction tourner_sur_place permet de faire tourner les roues dans le sens opposées afin faire tourner le robot.

Les fonctions reculer / avancer permettent de déplacer le robot en appliquant les mêmes vitesses sur les deux roues.