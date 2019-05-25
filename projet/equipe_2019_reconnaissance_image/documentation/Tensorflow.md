# Deep Learning : Reconnaissance d'image 

On rappel que le but du projet est de permettre au Robot de se déplacer vers un objet de notre choix et d'éviter d'autres objets.
Ce dernier doit donc être capable d'identifier et de reconnaitre ces objets en temps réel. Pour cela on utilise un algorithme de reconnaissance d'image en script python.


## La libraire Tensorflow

L'algorithme de reconnaissance d'image utilise la libraire Tensorflow. C'est une librairie créée par Google qui propose une série de modèles préentrainés. Ces modèles constituent une base de données qui va permettre différencier et de classifier les différentes images extraites du flux vidéo de la caméra.

Pour récupérer les modèles il suffit de cloner le dépôt Git suivant :

https://github.com/tensorflow/models



## L'algorithme de reconnaissance


Pour l'algorithme on a utilisé un script python existant sur internet et nous y avons apporté les modifications nécessaires.
La reconnaissance d'image se fait en utilisant un modèles pré-entraîné MobileNet couplé avec SSD (Single-Shot multibox Detector), implémentés dans Tensorflow. Pour le projet nous avons utilisé le modèle :

ssdlite_mobilenet_v2_coco_2018_05_09

MobileNet est une classe de modèles. Les MobileNets sont basées sur une architecture qui utilise des réseaux de neurones convolutionnels efficaces pour les applications de vision mobile et intégrée.

### Réseau convolutionnel de neurones

Explication rapide sur les réseaux convolutionnels de neurones, CNN :


