  # Carte alimentation version V2
La carte d’alimentation a été conçue par les étudiants 4A de l’année dernière. C’est une carte qui permet de gérer les niveaux des batteries du Robot Mt


![image2](https://user-images.githubusercontent.com/49748739/58384919-5748b100-7fe9-11e9-82bb-5cb81351e33e.jpg)


   # Description
  
![image](https://user-images.githubusercontent.com/49748739/58385085-1e114080-7feb-11e9-8e41-40b7d4889960.png)  
   
L'étage 1 composé du régulateur LM2596T est alimente en permanence vue qu'il est responsable d'alimenter le DsPIC33F.
Cet étage est alimente par 22V à travers les connecteurs. En sortie de cet étage on trouve 5 V qui sera par la suite injecter dans 
LP2985-33DBVR qui lui fournit en sortie 3.3 V qui correspond à la tension d'alimentation de notre DsPIC33F.
Le relais permet d'alimenter en 22 V les trois etages2, 3 et 4 une fois le DsPIC33F lui envoyé la commande.
L'étage 2 composé du régulateurs LM2678 permet de fournir une tension de 12 V qui sera utilisée par la suite pour alimenter les 3  servomoteurs à travers la sortie2.
L'étage 3 composé du régulateurs LM2678_Ajustable permet de fournir une tension variable entre 6.37 V et 7.4 V qui permet d'alimenter un servomoteur à travers la sortie3.
Finalement l'étage 4 composé du régulateur LM2596T permet d'alimenter la Rasberry-PI par 5 V qu'on récupère sur les sorties 4.

    # Solution en V2
    
         #  Solution 1

Au niveau de l'étage 1&4, la solution adopter dans V0 ne permet pas de générer les 5 volts demandées, pour résoudre ce problème on a remplacé le Feedback direct par un pont diviseur comme illustrer ci-dessous. 
Problèmes des condensateurs 330 uF :
Tension de claquage faible 6.3 V alors que tension appliquée et 22 V.
P.S : Dans notre cas on n’utilise pas CFF tension de sortie inférieure à 10V

![image](https://user-images.githubusercontent.com/49748739/58745596-13273780-8453-11e9-9e0b-9c60dfe6e839.png)

         # Solution 2
         
Au niveau de l'étage 2 on n’a pas eu les 12 V en sortie car il y avait pas de Feedback, ce qui expliquer les 20 volts en sortie.

![image](https://user-images.githubusercontent.com/49748739/58745606-2934f800-8453-11e9-8dfc-44c20900dcfc.png)

         # Solution 3

Relier la résistance R7  à 22 V alors qu’il doit être à la masse.

![image](https://user-images.githubusercontent.com/49748739/58745618-44a00300-8453-11e9-8b9f-cb606312fc72.png)

         # Solution 4
Modification du PCB sous Eagle.


A l'issue de ces modifications le schéma de la carte d'alimentation avec son PCB ont été modifier (voir PCBAlimv2).

