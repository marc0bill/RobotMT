## Présentation
La carte proposé ici, permet l'interface entre le bus eCAN et d'autre periphérique (cles modules ultrason en I2C et capteur de distance SHARP analogique)


## dsPICeCAN
Firmware des cartes d'interface dsPIC_I2C (carte\interfaceI2C_eCAN\dsPIC_I2C.brd)


## Description

Réalise l'interface entre :
* [US - srf10] Capteurs Ultrason (I2C) 
* [GP2Y2Y0A02] Capteurs IR SHARP (sortie analogique) 20cm->150cm
* [Le bus eCAN]
* [Une sortie UART] @ 57600 baud

## Details

Details de chaque module existant dans la programmation du dsPIC_I2C pour creer l'interface du bus eCAN avec d'autres peripheriques et de l'UART

# Module ECAN1Drv.h

* Dans ce module, on declare les fonctions de Ecan1Drv.c
* Choix de la frequence de fonctionnement de l'eCAN
* Choix debit binaire de l'eCAN

# Module ECAN1Drv.c

* Fonction ECANFilterSID: Cette fonction definit le filtre Standard ID utilisé lors de la tranmission eCAN
* Fonction ECANFilterEID: Cette fonction definit le filtre Extended ID utilisé lors de la tranmission eCAN
* Fonction ECAN1DMAConfig: Configuration de tout les Direct Memory Access Channel. 2 DMA sont configurés 
* Fonction ECAN1ClockConfig: Configuration de la Clock de l'eCAN
* Fonction ECAN1InterruptConfig: Fonction qui Reset de tout les flags avant le Run. Il configure egalement tout les interruptions de l'eCAN
???* Fonction ECAN1TxRxBuffersConfig: Fonction qui configure un TX Buffer et active 4 DMA buffers
* Fonction ECAN1RxFiltersConfig: Configuration des Filtres et des des Masques

## ToDo
* Définir les adresses eCAN des messages envoyés
* Etudier la mise en place de filtrage sur les données des capteurs
* Mettre en place une compilation conditionnelle en fonction des nodes (Node uniquemen pour US, Node US + SHARP, etc.)

## Note importante
La carte dsPIC_I2C.brd utilise le I/O standart pour I2C.
