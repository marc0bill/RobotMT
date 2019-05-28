# Scripts Python

Le programme à éxécuter sur la raspberry est main_V2.py.

__ATTENTION__ : lors de la récupération des scripts python par git dans la raspberry au chemin home\pi\Desktop\RobotMT, il faut copier TOUT les fichiers contenue dans le dossier dossier home/pi/Desktop\RobotMT\projet\equipe_2019_reconnaissance_image\python\Suivie_objet dans le dossier home\pi\tensorflow1\models\research\object_detection

## Main_V2.py

Ce fichier contient le programme principale.
Nous prenons en entrée le tableau issue du programme tensorflow qui analyse les images frame par frame et dedans nous cherchons si l'objet désiré y est présent.

S'il est présent alors nous pouvons commencer à donner les ordres d'alignement et de déplacement. Nous avons réaliser deux mode, le Mode 0 où le robot tourne et avance en deux temps et le mode 1 où celui-ci effectue les deux en même temps.
Tout d'abord la fonction main va vérifier que l'objet est bien aligné avec le centre du robot via la fonction aligner_robot. Si effectivement le robot est aligné alors il va appeler des fonction afin de savoir s'il faut reculer ou avancer en fonction de la position et de la taille de l'objet.
Sinon tant que le robot n'est pas aligné le robot tournera afin d'être aligné avec sa cible.
## Asserv_V2.py

En effet, les fonctions dans Asserv_V2.py permmettent de savoir l'action à effectuer en fonction de la position relative de l'objet par rapport au robot.

Si le robot n'est pas aligné avec l'objet alors il va tout d'abord calculer l'erreur de position est via un facteur k (correcteur proportionnel) il va ajuster la position du robot en appelant les fonctions tourner_sur_place dans Mouvement.py .

Si le robot est aligné alors il va calculer la taille de l'objet par rapport à la taille de l'image et il va reculer ou avancer afin de ne pas être trop loin ni trop près du robot en appelant les fonction avancer ou reculer de Mouvement.py .

La fonction aligner_positionner est la fonction qui dans le Mode = 1 permet d'appeler les fonctions tourner_et_avancer et tourner_et_reculer en fonction des cas de  figure.
## Mouvement.py

Tout d'abord la fonction tourner_sur_place permet de faire tourner les roues dans le sens opposées afin faire tourner le robot.

Les fonctions reculer / avancer permettent de déplacer le robot en appliquant les mêmes vitesses sur les deux roues.

Les fonctions tourner_et_avancer et tourner_et_reculer permettenet déplacer les roues du robot de façon à que celui puisse avancer ou reculer en même temps que tourner.

## Constantes.py

Ce fichier python est celui où toutes les constantes sont situées, cela permet d'ajuster facilement toutes les constantes en fonction des résultats des tests.

##Uart.py

La fonction write permet d'encoder une chaine de charactère en ascii et de l'envoyer via uart, de plus elle renvoie un retour de ce qui est envoyer à la raspberry afin que nous puissions controler l'envoie des données.

La fonction read permet de recevoir et de décoder l'information uart qui lui est envoyé.

##ObjetReconnu

La fonction _init_ permet de calculer les tailles et distances de l'objet.