# Deep Learning : Reconnaissance d'image 

On rappel que le but du projet est de permettre au Robot de se déplacer vers un objet de notre choix et d'éviter d'autres objets.
Ce dernier doit donc être capable d'identifier et de reconnaitre ces objets en temps réel. Pour cela on utilise un algorithme de reconnaissance d'image en script python.


## La librairie Tensorflow

L'algorithme de reconnaissance d'image utilise la libraire Tensorflow. C'est une librairie créée par Google qui propose une série de modèles pré-entraînés. Ces modèles constituent une base de données qui va permettre différencier et de classifier les différentes images extraites du flux vidéo de la caméra.

Pour trouver des exemples d'utilisation de la librairie Tensorflow, il suffit de cloner le dépôt Git suivant :

https://github.com/tensorflow/models

Pour trouver des modèles pré-entraînés :

https://github.com/tensorflow/models/blob/master/research/object_detection/g3doc/detection_model_zoo.md


## Le modèle MobileNetV2 + SSDLite

La reconnaissance d'image se fait en utilisant un modèle pré-entraîné MobileNet couplé avec SSD (Single-Shot multibox Detector), implémentés dans Tensorflow. 
Pour le projet nous avons utilisé le modèle :

```
ssdlite_mobilenet_v2_coco_2018_05_09
``` 

MobileNet est une classe de modèles. Les MobileNets sont basées sur une architecture qui utilise des réseaux de neurones convolutionnels. 
Ici nous avons pris un modèle SSDlite_MobilenetV2 car il est moins volumineux et mieux adapté pour les appareils portables, tel que la RaspberryPi. 

### Réseau de neurones convolutifs (CNN)
C'est un système composé de neurones, généralement répartis en plusieurs couches connectées entre elles :

![40%](https://1.bp.blogspot.com/-M8UvZJWNW4E/WsKk-tbzp8I/AAAAAAAAChw/OqxBVPbDygMIQWGug4ZnHNDvuyK5FBMcQCLcBGAs/s1600/image5.png)

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

#### Softmax
Une dernière étape, appelée softmax, consiste à normaliser les valeurs des sorties afin qu’elles correspondent à des probabilités (entre 0 et 1) et que leur somme soit de 1. La classe prédite correspondra alors au neurone de sortie indiquant la plus grande probabilité.

![](https://machinethink.net/images/mobilenet-v2/Classifier@2x.png)

Remarque : les features et les valeurs des poids ne sont pas pré-définies mais apprises par le réseau lors de la phase d'entraînement.

SSDLite  utilise des couches séparables en profondeur au lieu de convolutions régulières pour la partie de détection d'objet du réseau. Avec SSDLite, on peut facilement obtenir des résultats vraiment en temps réel.

## L'algorithme de reconnaissance d'image

Pour l'algorithme on a utilisé un script python existant sur internet et nous y avons apporté les modifications nécessaires.
Avec le modèle chargé, le robot est capable de détecter des objets appartenant à 90 classes différentes ainsi que la classe "aucun objet détecté". 
On réalise la détection avec en entrée une image (une frame) issue de la caméra et en sortie on récupère les boxes, les classes et les scores associés dans des tableaux.

Chaque boxe représente une partie de l'image où un objet à été détecté. Les classes renvoie la nature de l'objet et les scores représente le niveau de confiance de la classe associée à l'objet détecté.

Nous avons rajouter ce bout de code au script initial afin de retourner une liste de liste contenant, pour chaque objet détecté sur l'image : la classe, le score ainsi que ses coordonnées sur l'image (Ymax, Xmax, Ymin, Xmin)
On se limite ici au quatre premiers objets détectés sur l'image (c'est-à-dire, ceux avec le plus grand score).

```
  classes=np.squeeze(classes).astype(np.int32)
    scores=np.squeeze(scores).tolist()
    boxes=np.squeeze(boxes).tolist()
    objets=[[],[],[],[]]
    c=0
    for i in range (0,4):
        if scores[i]==0:
            break
        objets[i].append(category_index[classes[i]]['name'])
        objets[i].append(scores[i])
        objets[i].append(boxes[i][0])
        objets[i].append(boxes[i][1])
        objets[i].append(boxes[i][2])
        objets[i].append(boxes[i][3])
        c+=1
 
    camera.close()
    return (objets[0:c])
```
Le but de ce bout de code est de retourner les valeurs dans un certains ordre afin qu'elles puissent être récupérée pour le contrôle moteur.

## Axes d'amélioration

- Il est possible de créer son propre modèle et de l'entraîner mais cela demande beaucoup de ressources en image (au moins une centaines d'image pour un objet), de temps et c'est une démarche très fastidieuse.

- On peut utiliser la librairie Tensorflowlite, qui a été crée pour les télephone portables ou tout autre appareil portable. Les modèles sont beaucoup moins volumineux et plus rapides (on réduit la taille des poids synaptiques). 
Cependant, les modèles sont donc moins précis que les modèles classiques. De plus, le code de reconnaissance d'image pour cette libraire est différent de celui utilisé pour la libraire Tensorflow.

- Utiliser Intel® Neural Compute Stick : il s'agit d'un dispositif branché sur un port USB qui permet d'accélérer la détection d'image sur RaspberryPi. On peut ainsi chargé des modèles volumineux avec la RaspberryPi sans trop dégradé les performances.
Ce dispositif à malheureusement un coup assez élevé (environ 90e) et consomme beaucoup d'énergie (500mA).
