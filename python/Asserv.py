def fnct (Tableau):
	int distance, ratio
	char Vitesse == "VtsM"
	float Vit_droite = 50
	float Vit_gauche = 50
	float Size, deltaX, deltaY,Ksize,Kdist= 0
	float Middle
	for e in range Tableau.length:
		if Tableau[e][0] == "Cannette":
			deltaY = (Tableau[e][2]-Tableau[e][4])
			deltaX = (Tableau[e][3]-Tableau[e][5])
			Size = SQRT((deltaX**2) + (deltaY**2))
	Middle = (Tableau[e][3] + Tableau[e][5])/2.0
	distance = (Middle - 0.5)
	ratio = Size / SQRT(2)
	
	while ratio=!0.3 and 0.2<ratio<0.8
		Ksize = (ratio-0.5)/0.3
	Kdist = distance/0.5
		
		
	return Vit_droite*(Ksize+Kdist),Vit_gauche(Kdist-Ksize)
	
			
	
	
