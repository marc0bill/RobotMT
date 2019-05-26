L'objectif était de comprendre comment les moteurs actionnant les roues étaient commandés.

C'est le dsPIC33F qui est chargé de transmettre les instructions aux moteurs.



###Au départ :

La majeure partie des programmes codés en langage C contrôlant le robot nous était fourni.



###Ce que nous avons fait :

Notre travail consistait à comprendre comment le code fonctionnait pour pouvoir ensuite l'exploiter.

Les moteurs sont contrôler avec un système de pwm ("Pulse width modulation", autrement dit, modulation de largeures d'impulsions). On applique un signal carré dont on peut modifier le rapport cyclique. On prends ensuite la valeur moyenne sur une période ce qui nous donne une tension variant entre 0V et la tension d'alimentation. Cela permet d'appliquer la tension souhaitée en fonction de la vitesse que l'on veut appliquer aux roues.

Cela est couplé avec un pont en H qui est un système qui va permettre de changer le sens du courant traversant le moteur et donc de changer son sens de rotation. Ceal permettra de pouvoir passer d'une consigne "avancer" à une consigne "reculer" ou inversement. 

En se plongeant dans le code, nous avons pu nous rendre compte que l'on pouvait donner des consignes de vitesses évidemment mais aussi de positions et d'angles. Il y avait déja différents modes implantés : avance en x et y, recule en x et y, ajustement de l'angle... Il y a la possibilité de définir une vitesse de déplacement simple ou une vitesse angulaire. Il y a des fonctions qui permettent de limiter la vitesse ainsi que l'accélération, d'autres qui calculent les erreurs de positions, vitesses ou angles.

### Compréhension du code

Comme il a été dit ce code permet de convertir une entrée UART issue de la raspberry en PWM. Pour cela le code va interprété l'UART charactère par charactère, en effet il y a dans "uart.c" une interruption qui permet de parcourir charactère par charactère les données envoyé via UART, ensuite ces charactère vont être regroupés en chaîne de charactère grâce aux espaces. Ces chaînes vont ensuite être traité par le code de "uartassig.c", celui ci va permettre de différiencer les ordres que nous envoyons.


###Problèmes rencontrés

Aux premiers abords, le code permettant de piloter les moteurs est extremement dense et il nous a donc fallu beaucoup de temps pour le comprendre et l'utiliser.



###Ce qu'il reste à faire

Comme dit précédemment, le code est vraiment dense et il pourrait être nettement amélioré. Malheureusement, nous n'avons pas eu le temps de nous plonger dans cette tâche.

