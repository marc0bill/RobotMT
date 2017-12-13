#Bouton pour limiter la vitesse du pointeur
LIMITER=7


# Association des bouton de la manette a une action
#
# binds= {bouton:(materiel, code), ...}
#   bouton: numero du bouton de la manette
#   materiel: 0=souris, 1=clavier
#   code: keycode de la touche pour un clavier,
#         numero du bouton pour une souris

binds={0:(0, 1),        # souris bouton de gauche
		1:(0, 3),       # souris bouton de droite
		2:(1, 36),      # clavier Echap
		3:(1,9),        # clavier Entrer
		4:(1, 117),     # clavier pg suivante
		5:(1,112),      # clavier pg precedente
		6:(1,37),       # clavier ctrl
		#~ 7:(1,50),        # clavier Shift
		#~ 9:(1,64),        # clavier Alt
		}