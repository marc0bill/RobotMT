# Régulateurs de tension nécessaires

<p>Le robot possède de nombreuses cartes, microcontroleurs, capteurs, moteurs fonctionnants à des niveaux de tension/courant différents. Il est donc essentiel de créer différentes lignes de tension/courant à l'aide de régulateurs de tension.</p>

## En amont du relais de protection des batteries :

### Ligne1 : 5V-3A
<p>dsPIC33FJ128MC + bobine + espace libre</p>
<p>Consommation max du régulateur = 682mA</p>
<p>Composant = <b>LM2596T</b></p>
<p>Remarque : le dsPIC s'alimente en 3,3V ainsi nous avons utilisé un régulateur de tension supplémentaire 5V vers 3,3V. C'est un LP2985-33DBVR</p>

### Consommation max en amont du relais de protection des batteries
<p>Equivalent à la consommation max du régulateur 1 = 682mA</p>

## En aval du relais de protection des batteries :

### Ligne2 : 5V-3A 
<p>RaspberryPi model 3 (2.5A) + espace libre de 0.5A</p>
<p>Consommation max du régulateur = 682mA</p>
<p>Composant = <b>LM2596T</b></p>

### Ligne3 : 12V-5A 
<p>3 cerveaux moteurs MX28 (3*1.5A = 4.5A) + espace libre de 0.5A</p>
<p>Consommation max du régulateur = 2.73A</p>
<p>Composant = <b>LM2678</b></p>

### Ligne4 : tension ajustable (6.25 à 7.5V)-4.5A
<p>1 cerveau moteur + espace libre</p>
<p>Consommation max du régulateur = 1.53A</p>
<p>Composant = <b>LM2678_ADJ</b></p>

### Consommation max en aval du relais de protection des batteries
<p>Equivalent à la somme des consommations max des régulateur 2,3,4 
     + consommation de la propulsion (2 motoréducteurs amax32g alimentés en 22V-1A chacun) = 6.942A</p>


# Dimmensionnement des régulateurs de tension
