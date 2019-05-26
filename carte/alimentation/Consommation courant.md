# Objectif

La carte d'alimentation comporte 3 cellules de sortie  respectivement de 3,3V, 5V et 12V. Ces sorties sont reliées à 
la carte STM32. L'objectif est de pouvoir contrôler le courant de manière instantanée. Il faut pouvoir en cas de problème
pouvoir couper l'alimentation. Le problème peut-être de type dépassement de la limite de courant demandée par la STM32. Si 
on met en place un montage par cellule, le problème sera plus rapidement trouvé et résolu. 
 
![schema](https://user-images.githubusercontent.com/47904531/58384878-b0fcab80-7fe8-11e9-9f08-bc525399ca31.png)


# Solution 1 

Un amplificateur différentiel permettra d'amplifier la différence de potentiel entre les entrée de de l'amplificateur 
afin de déterminer grace à la formule V=RI le courant allant dans la ST32. Il faut donc choisir le composant adequat. 
L'amplificateur différentiel AD8237 ARMZ-R7 a été choisi pour ces différents paramètres comme la tension d'offset d'entrée, 
la bande passante. On a pu établir un schéma grace à la datasheet permettant d'avoir une mesure précise du courant. 
 
![Image3](https://user-images.githubusercontent.com/47904531/58384887-e86b5800-7fe8-11e9-9d78-9ab33145108c.png)

Cette solution est très interresante pour controler avec précision le courant, mais elle engendre des complications car 
le montage doit être répété 3 fois et cela à un coût. 
 
# Solution 2

Pour limiter cet encombrement, on peut utiliser un capteur à effet Hall. En effet, un conducteur parcouru par un courant 
électrique, selon une direction, soumis à un champ magnétique, dirigé dans une seconde direction, présente une différence de 
potentiel selon la troisième direction. Ce phénomène est connu sous le nom d'effet Hall. Ce capteur qui est donc inductif et
permet de mesurer la variation de champ magnétique. Il permet donc aussi de mesurer le courant allant dans la carte STM32.

![hall2](https://user-images.githubusercontent.com/47904531/58384909-38e2b580-7fe9-11e9-8e1b-12b042acf95f.gif)
