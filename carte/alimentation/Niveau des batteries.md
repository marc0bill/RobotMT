# Objectif

Le montage est composé de 2 batteries de chacune 11,2V. Chaque batterie est elle même composée de 3 cellules. L'objectif est 
d'amener la tension de sortie de chaque cellule à une tension de 3,3V maximum. 
 
# Solution 1 

Dans un premier temps l'idée est de mettre en place un pont diviseur de tension afin de réduire cette tension venant des 
batteries. 

![Image2](https://user-images.githubusercontent.com/47904531/58384981-287f0a80-7fea-11e9-94a5-a3acdc768c4a.png)
 
Plus la tension d'entrée est grande plus il faut prendre des résistances grandes pour diminuer cette tension à la sortie. 
On a donc un montage qui fonctionne. Cependant, nous n'avons pas pris en compte la résistance présente sur la carte STM32. 
En effet, la résistance équivalente est très faible et sera donc prise en compte lors du calcul de la résistance 
équivalente. Cette résistance en plus, va perturber le diviseur de tension, la tension de sortie sera donc différente. 

# Solution 2 

Il faut donc repenser le montage pour avoir une tension de sortie maximum de 3,3V. On a donc supprimé une résistance 
comme le montre le montage ci-dessous. 


