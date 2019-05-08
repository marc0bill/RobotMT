DAY 1 : Seance 1-2
    Introduction au projet
    Formation des groupes
DAY 2 : Seance 3-6
    Fait:
        Redaction du gant v1
        Mise à jour de la raspberry
        Test de la commande robot -> inconcluant, voir avec Mr. Bocquet
        Prise en main TenseurFlow
        Prise en main UART : https://electrosome.com/uart-raspberry-pi-python/  et  https://doc.ubuntu-fr.org/minicom
        Prise en main camera : https://www.instructables.com/id/Raspberry-Pi-remote-webcam/
    A faire:
        Revoir le gant
        Completer le tuto UART
        Completer le tuto camera
DAY 3 : Seance 7
    Fait:
        Configuration de l'UART (testé et approuvé en direct et avec un scipt python)
        Compréhension de l'algorithme tensorflow
DAY 4 : Seance 8
    Fait :
        Tests simplistes de la camera. Celle ci fonctionne mais la video récupérée est accéléré x2
        Installation des logiciels et librairies nécessaire à la reconnaissance d'image sur la raspi
            - Exceptions relevée lors de la commande "sudo apt-get install python-tk", revenir la dessus en cas de problèmes 
            - Bloqué à l'installation de openCV 
                - Il faut mettre à jour la version de python (ver 3.7) : https://github.com/lhelontra/tensorflow-on-arm
                - En refaisant la commende make, python 3.4 est toujours présent. A voir si cela influe sur la suite (on devrais être en 3.5 minimum)
        Prise en main de l'algorithme tensorflow
        Etude du code C du microcontrolleur afin de comprendre l'actionnement des roues
        Reflexion sur toute la chaine de fonctionnement et les modification à apprter au code C afin de simplifier le processus de communication entre la raspi et le µC
DAY 5 : Seance 9




Discussions libres

Processus de fonctionnement
    - Video temps réel récupérée de la camera
    - Traitement d'image par algorithme tensorflow sur la raspi
    - Communication UART de la raspi au µC en cas de reconnaissance d'objet : envoie de commmande d'action des roues
A dévelloper:
    - Comment évaluer clairement la distance à parcourir ?
        -> Comprendre comment fonctionne et exploiter le module infrarouge 
        -> 

    