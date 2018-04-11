# Présentation

La carte proposé ici, permet l'interface entre le bus eCAN et d'autre periphérique (cles modules ultrason en I2C et capteur de distance SHARP analogique)


## dsPICeCAN

Firmware des cartes d'interface dsPIC_I2C (carte\interfaceI2C_eCAN\dsPIC_I2C.brd)


# Description

Réalise l'interface entre :
* [US - srf10] Capteurs Ultrason (I2C) 
* [GP2Y2Y0A02] Capteurs IR SHARP (sortie analogique) 20cm->150cm
* [Le bus eCAN]
* [Une sortie UART] @ 57600 baud

# Details

Details de chaque module existant dans la programmation du dsPIC_I2C pour creer l'interface du bus eCAN avec d'autres peripheriques et de l'UART

## Module init_pic.h

* Definition de toutes les entrees/sorties et frequence de fonctionnement general

## Module node.h

* Choix de la node 1 (Reception) ,2 (reception et transmission) ou US (pour capteur) avec attribution des adresses

## Module I2c.h
A DEFINIR

## Module moduleI2c.h

* Declaration des variables
* Initiation Ultrason

## Module ECAN1Drv.h

Dans ce module, on déclare principalement les fonctions de Ecan1Drv.c
* Choix de la fréquence de fonctionnement de l'eCAN
* Choix débit binaire de l'eCAN

# Module init_pic.c

* Initialisation de la clock
* Assignation des PIN
* Initialisation des Ports I/O

## Module ECAN1Drv.c

* Fonction ECANFilterSID: Cette fonction definit le filtre Standard ID utilisé lors de la tranmission eCAN
* Fonction ECANFilterEID: Cette fonction definit le filtre Extended ID utilisé lors de la tranmission eCAN
* Fonction ECAN1DMAConfig: Configuration de tout les Direct Memory Access Channel. 2 DMA sont configurés (0 pour reception,1 pour transmission)
* Fonction ECAN1ClockConfig: Configuration de la Clock de l'eCAN
* Fonction ECAN1InterruptConfig: Fonction qui Reset de tout les flags avant le Run. Il configure egalement tout les interruptions de l'eCAN
* (Fonction ECAN1TxRxBuffersConfig: Fonction qui configure un TX Buffer et active 4 DMA buffers)
* Fonction ECAN1RxFiltersConfig: Configuration des Filtres et des des Masques
* Fonction ECAN1SendPacket: L'eCAN envoie une requete au DMA pour transmettre le message et le DMA envoie le TxBuffer a transmettre
* Fonction ECAN1SetOPMode:Choix du mode utilisee (Normal Operation Mode pour recevoir et ecouter en eCAN)
* Fonction ECANCreateSIDPacket: Creation du Packet SID a envoyer (8bits)
* Fonction ECANCreateEIDPacket: Creation du Packet EID a envoyer (8bits)


# ToDo
* Définir les adresses eCAN des messages envoyés
* Etudier la mise en place de filtrage sur les données des capteurs
* Mettre en place une compilation conditionnelle en fonction des nodes (Node uniquemen pour US, Node US + SHARP, etc.)

# Note importante
La carte dsPIC_I2C.brd utilise le I/O standart pour I2C.
