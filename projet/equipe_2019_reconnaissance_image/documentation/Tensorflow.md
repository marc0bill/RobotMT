# Deep Learning : Reconnaissance d'image 

On rappel que le but du projet est de permettre au Robot de se déplacer vers un objet de notre choix et d'éviter d'autres objets.
Ce dernier doit donc être capable d'identifier et de reconnaitre ces objets en temps réel. Pour cela on utilise un algorithme de reconnaissance d'image en script python.


## La libraire Tensorflow

L'algorithme de reconnaissance d'image utilise la libraire Tensorflow. C'est une librairie créée par Google qui propose une série de modèles préentrainés. Ces modèles constituent une base de données qui va permettre différencier et de classifier les différentes images extraites du flux vidéo de la caméra.

Pour récupérer les modèles il suffit de cloner le dépôt Git suivant :

https://github.com/tensorflow/models



## Le modèle MobileNetV2 + SSDLite

La reconnaissance d'image se fait en utilisant un modèle pré-entraîné MobileNet couplé avec SSD (Single-Shot multibox Detector), implémentés dans Tensorflow. Pour le projet nous avons utilisé le modèle :

```
ssdlite_mobilenet_v2_coco_2018_05_09
``` 

MobileNet est une classe de modèles. Les MobileNets sont basées sur une architecture qui utilise des réseaux de neurones convolutionnels. Ici on a pris un modèle SSDlite car c'est la version plus rapide. 

### Réseau de neurones convolutifs (CNN)
C'est un système composé de neurones, généralement répartis en plusieurs couches connectées entre elles :

#### La couche de convolution
Elle reçoit une image entrée et lorsque c'est une vidéo, on la découpe en plusieurs images. 
Son but est de repérer la présence d'un ensemble de features (matrice qui représente quelque chose comme "une oreille"...) dans ces images. Pour cela, on réalise un filtrage par convolution : on fait "glisser" une fenêtre représentant la feature sur l'image, et on calcule le produit de convolution entre la feature et chaque portion de de pixels de l'image balayée. Une feature est alors vue comme un filtre.
On récupère en sortie une feature map, qui nous indique où se situent les features dans l'image.


#### La couche de pooling 
Elle reçoit en entrée des feature maps et leur applique l'opération de pooling qui consiste à réduire la taille de l'image en préservant leurs caractéristiques importantes. On découpe l'image en petites cellules carrées de quelques pixels et sur chaque cellule on ne conserve que la valeur maximale.
Cette couche permet d'éviter la sur-information afin d'améliorer les performances et l'efficacité du réseau. 

#### La couche de correction ReLU
Elle désigne la fonction réelle non-linéaire définie par ReLU = max(0,x). Elle remplace toute les valeurs négatives reçues en entrée par des zéros.

#### La couche fully-connected
C'est la dernière couche du réseau de neurones. Elle prend en entrée notre image complètement modifiée par les convolutions et d'autres opérations et renvoie la prédiction, par exemple si l'image est plus un chien ou un chat. Pour calculer la probabilité, la couche multiplie le vecteur en entrée par la matrice contenant les poids. 

Remarque : les features et les valeurs des poids ne sont pas pré-définies mais apprises par le réseau lors de la phase d'entraînement.


## L'algorithme de reconnaissance d'image

Pour l'algorithme on a utilisé un script python existant sur internet et nous y avons apporté les modifications nécessaires.
Avec le modèle chargé, le robot est capable de détecter des objets appartenant à 90 classes différentes ainsi que la classe "aucun objet détecté". 
On réalise la détection avec en entrée une image (une frame) issues du flux vidéo et en sortie on récupère les boxes, les classes et les scores associés dans un tableau.

Chaque boxe représente une partie de l'image où un objet à été détecté. Les classes renvoie la nature de l'objet et les scores représente le niveau de confiance de la classe associée à l'objet détecté.


