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

* Configuration I2CCON
* SFRs pour I2C1 module
* Configuration maitre-esclave

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

## Module i2c.c

* Fonction I2C_Init: Cette fonction initialise le bus I2c
* Fonction config_I2C:Configuration de l'i2 (vitesse de fonctionnement,activation i2c)
* Fonction write_i2c:On ecrit et quand c'est remplit on arrete
* Fonction write_reg_i2c: Envoie/ecriture adresse/registre/data
* Fonction Lecture_reg_i2c: Ecriture adresse lecture, lecture de la donnee
* Fonction write_i2c_EEPROM: Ecriture i2c dans EEPROM (NON UTILISEE)
* Fonction lecture_I2C_EEPROM: test de lecture (NON UTILISEE)
* Fonction save_double: lecture d'un double en memoire EEPROM (NON UTILISEE)
* Fonction load_double: lecture d'un double en memoire EEPROM (NON UTILISEE)
* Fonction save_int: lecture d'un int en memoire EEPROM (NON UTILISEE)
* Fonction load_int: lecture d'un int en memoire EEPROM (NON UTILISEE)

## Module moduleI2C.c
Ce module s'occupe de la gestion des capteurs ultra son

* Fonction mesure_boussole: Configuration de la boussole
* Fonction init_ultrason: Initiation de l'ultrason
* Fonction mesure_ultrason_1: mesure de l'ultrason. On a une machine d'etat (cas 1 a 4) 1= debut mesure , 2= fin mesure, 3=mesure en LSB, 4= mesure en MSB. A la fin de chaque case, il y'a une verification d'erreur.

## Module uart.c

* Fonction initUART1: 
Initialise l'UART:
- Calcul du baud rate. 
- Configure Uxmode: Registre de mode.  
- Configure UxSTA : Registre status et controle.
- Configuration des priorites interrupts en transmission et reception. 
* Fonction _U1RXInterrupt: Routine d'interruption sur reception UART1
* Fonction _U1TXInterrupt: Routine d'interruption transmission UART1 (buffer vide)
* Fonction fctU1Tx_int: Fonction d'envoie en UART
* Fonction fctU1Tx_string: Fonction d'envoie en UART

## Module main.c


# ToDo
* Définir les adresses eCAN des messages envoyés
* Etudier la mise en place de filtrage sur les données des capteurs
* Mettre en place une compilation conditionnelle en fonction des nodes (Node uniquemen pour US, Node US + SHARP, etc.)

# Note importante
La carte dsPIC_I2C.brd utilise le I/O standart pour I2C.
