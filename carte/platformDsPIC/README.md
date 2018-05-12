# Carte platforme dsPIC (eCAN <=> UART)

## Présentation

La carte proposée ici, permet de réaliser une passerelle eCAN <=> UART.


<p align="center">
  <img width="598" height="403" src="https://github.com/marc0bill/RobotMT/blob/master/ressourceWikiReadme/IMG_3110.jpg">
</p>

## Détail
On utlise cette carte comme platforme de monitoring et commande de l'ensemble des nodes connectés sur le bus CAN. Elle écoute les messages transmis sur le bus CAN et les envoient par le bus UART à un PC par exemple pour afficher les résultat sur un terminal(Termite, CoolTerm, etc).



### firmware

Le firmware associé a cette carte est :

```
firmware/dsPICeCAN.X
```


## Authors

* **Marc Bocquet** - *Initial work* - [marc0bill](https://github.com/marc0bill)
