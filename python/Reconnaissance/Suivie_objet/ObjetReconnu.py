import constantes

class ObjetReconnu:

	def __init__(self, nom, proba, ymin, xmin, ymax, xmax):
		self.nom = nom
		self.proba = proba
		# Les x et y sont données en valeurs normalisées (de 0 à 1)
		# Le points en haut à gauche est (0,0) et en bas à doite (1,1)
		# Le centre de l'ecran est donc en (0.5, 0.5)
		self.ymin = ymin - 0.5
		self.xmin = xmin - 0.5
		self.ymax = ymax - 0.5
		self.xmax = xmax - 0.5
		self.milieu_X = (self.xmax+self.xmin)/2.0
		self.taille_X = abs(self.xmax-self.xmin)
		self.taille_Y = abs(self.ymax-self.ymin)
		self.diagonale = SRQT(self.taille_X**2 + self.taille_Y**2)
		self.ratio = self.diagonale/DIAGONALE_ECRAN
