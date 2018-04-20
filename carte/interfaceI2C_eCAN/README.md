# Carte interface eCAN/I2C/UART/entrée Analog

## Présentation

La carte proposé ici, permet l'interface entre le bus eCAN et d'autre périférique (comme par exemple les modules ultrason en I2C ou capteur de distance SHARP analogique)

## Détail

Deux versions de cartes sont proposées : 
<p align="center">
  <img width="460" height="400" src="https://github.com/marc0bill/RobotMT/blob/master/ressourceWiki/interfaceI2C_eCAN_photo.png/460/300">
</p>


### dsPIC_I2C

Il s'agit de celle actuellement utilisé et fonctionnelle

### dsPIC_I2CMini

Il s'agit d'une version plus compact à finaliser si nécessaire.
Un travail sur les connecteurs pourrait aussi être effectuer pour amélioré la robustesse d'assemblage et la taille de la carte.


### firmware

Le firmware associé a cette carte est :

```
firmware/dsPICeCAN.X
```

## Authors

* **Marc Bocquet** - *Initial work* - [marc0bill](https://github.com/marc0bill)
