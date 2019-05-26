# Objectif

Le but de cette démarche est de controler le niveau de température des 2 batteries présententes dans le montage. 
Lorsque le niveau est trop important, une alerte devra être envoyée à l'aide du bus CAN. 

# Choix du capteur 

On a choisi un capteur LM35dz car il a une capture de température maximum de 100 degrés, ce qui est suffisant 
pour nos batteries. 

![Capteur-de-temperature-LM35-Dapres-la-fiche-technique png](https://user-images.githubusercontent.com/47904531/58384716-4dbd4a00-7fe5-11e9-96aa-5456dee0593f.jpg)

# Caractérisation du capteur de température

Pour caractériser ce capteur, il faut mettre une source de chaleur à proximité afin de voir l'évolution de 
la température. De plus, on observe la tension en sortie du capteur. Par ailleurs, il faut connaitre la
température exacte de la source de chaleura afin de tracer la caractéristique du capteur représentant la 
température en fonction de la tension.
 
(image)
 
# Montage permettant la caractérisation

On relie donc le capteur à une tension d'alimentation stable de 3,3V, ainsi qu'à l'oscilloscope pour avoir la 
tension de sortie. La source de chaleur est possible grâce à la diode de puissance. Elle même reliée aussi à 
une alimentation que l'on fera varier. En effet plus la tension d'alimentation augmente, plus la température 
de la diode augmente. On utilise en plus un thermomètre pour connaitre à chaque instant la température. 
On relie les 3 composants (capteur de température, thermomètre, diode de puissance)à l'aide de scotch, ce qui 
n'est pas très conventionnel, car cela peut influencer les mesures. On effectue les mesures plusieurs fois car
de nombreux paramètres influent sur le résultat, comme l'environnement, la salle, les personnes autour, le scotch
utilisé. Au final on obtient les courbes suivantes qui sont linéaires, c'est donc cohérent. 
 
(IMAGE)
