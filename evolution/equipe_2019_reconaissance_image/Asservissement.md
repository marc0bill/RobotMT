L'objectif est de faire en sorte que les roues s'actionnent de manière cohérente par rapport aux objets détectés. Pour cela, nous avons défini un type d'objet (les sacs par exemple) vers lequel il doit se rapprocher et un autre duquel il doit s'éloigner.

Nous avons donc écrit un programme en python pour contrôler ces roues. Nous avons commencé par un mode de positionnement basique : lorsque le robot détecte un objet duquel il doit se rapprocher ou s'éloigner, il va d'abord se positionner face à cet objet. Pour cela, il va le centrer sur l'axe horisontal. Cela est possible car l'algorithme de reconnaissance d'images définit des "carrés" dans lesquels sont inclus les objets qu'il détecte. Il nous renvoit ensuite les coordonnés de deux points correspondants à deux sommets du "carré" (celui en haut à gauche et celui en bas à droite) ce qui nous permet de définir un point qui correspond au centre de l'objet. On peut ainsi déterminer la distance entre ce dernier et le centre de l'image. Suivant le signe de cette distance, on sait alors si on doit tourner à gauche ou à droite. On applique alors une cerrtaine vitesse à une des deux roues et son opposé à l'autre (pour tourner sur place). On ajoute également une tolérance sur l'alignement du robot avec l'objet pour éviter qu'il ne se corrige sans cesse en esayant de s'aligner sur une position très précise sans jamais réussir.

Nous avons également défin une distance à laquelle il doit se positionner pour l'objet duquel il doit s'approcher et une autre distance pour l'objet duquel il doit s'éloigner. Sachant que l'algorithme renvoit les coordonnés de deux points du "carré", on peut obtenir la diagonale et on connait également la diagonale totale de l'écran. On peut alors faire un rapport des deux pour obtenir la place que prend l'objet sur l'image. Il suffit ensuite de paramétrer une certaine taille que doit prendre l'objet sur l'image ce qui équivaut à une distance à laquelle le robot doit se trouver par rapport à l'objet.

Une fois aligné, le robot doit avancer ou reculer pour atteindre la distance à laquelle il doit se trouver de l'objet. On applique donc la même vitesse aux deux roues.

Pour optimiser un peu plus le mouvement du robot, nous avons également ajouter un correcteur proportionnel sur la vitesse des roues. Ainsi, au plus il faut tourner pour s'aligner avec l'objet (distance entre le centre de l'objet et le centre de l'image grande), au plus les roues tourneront vite pour s'aligner plus rapidement. Il en est de même lorsqu'il faut s'approcher ou s'éloigner : au plus on est loin de la distance à laquelle le robot doit se positionner par rapport à l'objet, au plus les roues tourneront vite.

Nous avons également conçu un second mode de déplacement un peu plus complexe et optimisé où lorsque le robot s'aligne avec l'objet tout en commencant à avancer. Cela évite de décomposer le mouvement un deux étapes disinctes. Dans ce cas-là, on va additionner les vitesses de positionnement (avancer/reculer) et de d'alignement (tourner à droite/gauche).



###Problèmes rencontrés :

La traduction de l'asservissement des roues en langage python n'a pas vraiment posé problème. Nous n'avons pas eu de difficultés particulières pour cette partie.




###Possibilités d'améliorations que nous n'avons pas eu le temps d'implémenter :

Dans notre code, nous avons utiliser un correcteur proportionnel pour l'asservissement des roues ce qui correspond au cas le plus basique (simple modification du gain statique initial du système). Nous aurions pu utiliser un correcteur intégrale ou à action dérivée pour améliorer la précision ou la rapidité respectivement ou encore d'autres types de correcteurs pour optimiser l'asservissement.

Le code pourrait également bénéficier de quelques optimisations.





