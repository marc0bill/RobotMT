//---Definition des pins
#define PIN_ROUE_1 5
#define PIN_ROUE_2 6
#define PIN_FEEDBACK_ROUE_1 A0
#define PIN_FEEDBACK_ROUE_2 A3

//---Caractéristiques du robot
#define RAYON_ROUE 75 //A MESURER, CECI EST UNIQUEMENT UNE VALEUR DE TEST !!!!!!! //Rayon des roues en mm
#define VITESSE_ANGULAIRE_MAX 5000 //A DETERMINER, CECI EST UNIQUEMENT UNE VALEUR DE TEST !!!!!! //Vitesse engulaire max des moteurs des roues en tour/min
#define CONSTANTE_VITESSE_MOTEUR 0.0382 //A DETERMINER, CECI EST UNIQUEMENT UNE VALEUR DE TEST !!!!!! //Nm/A ou Vs/rad
#define TENSION_ALIM_MOTEUR 22 //V

//---Definition des variables
#define BAUDRATE 9600
int DC1 = 0, DC2 = 0; //Rapports cycliques des roue en %
byte unsigned Consigne_PWM1 = 0, Consigne_PWM2 = 0; // Valeur des rapports cycliques sur 8 bits non-signés
byte unsigned Reel_PWM1 = 0, Reel_PWM2 = 0; // Valeurs des RC effectifs
float Consigne_V1 = 0, Consigne_V2 = 0, Reel_V1 = 0, Reel_V2 = 0;
String action = "";
int nombreMesurePWM = 50; //nombre de valeurs moyennée pour effectuer les mesures des signaux PWM. 50 est un bon compromis entre précision et rapidité
long distance = 0; //Distance a parcourir en cm
long temps_deplacement = 0; //temps nécessaire au deplacement en ms


void setup() {

  //---Configuration des I/O
  pinMode(PIN_ROUE_1, OUTPUT);
  pinMode(PIN_ROUE_2, OUTPUT);
  pinMode(PIN_FEEDBACK_ROUE_1, INPUT);
  pinMode(PIN_FEEDBACK_ROUE_1, INPUT);

  //---Configuration Communication Série
  Serial.begin(BAUDRATE);
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Port Serie Disponible");
}

void loop() {

  //verifierConnection();

  if (Serial.available() > 0) //Si on reçois une donnée
  {
    Serial.println("-----Donnees recues-----");
    action = Serial.readStringUntil(' '); //lit la chaine de caractères difinissant la commande
    Serial.print("Action : ");
    Serial.println(action);

    if(action.startsWith("stop")) 
      stop_moteur();
    else if(action.startsWith("vtsm")) 
    {
      Serial.println("-----MOTEUR ON : LIGNE DROITE-----");
      DC1 = Serial.parseInt(); //On lit la commande de la roue 1
      //DC2 = Serial.parseInt(); //On lit la commande de la roue 2
      DC2 = DC1; //On avance en ligne droite
      distance = Serial.parseInt();
      Serial.print("Distance : ");
      Serial.print(distance);
      Serial.println(" cm");
      
      
      temps_deplacement = calculer_temps_deplacement(distance);
      
      avancer(DC1, DC2);
      mesurer_vitesses_roues();
      afficher_vitesses_roues();
      delay(temps_deplacement); //inconvenient : on ne peut pas arreter les roues une fois le mouvement engagé

      stop_moteur();
    }
    else
      Serial.println("Erreur : commande invalide");

    mesurer_vitesses_roues();
    afficher_vitesses_roues();
    while (Serial.available()) Serial.read(); //On vide le buffer d'entrée
  } 
}

void verifierConnection() 
{
  while (Serial.available() <= 0) //tant qu'aucun caractère n'est disponible à la lecture
  { 
    Serial.println("Connexion stable");
  }
}

int PWM_mesure(int pinMesure, int nombreMesure)
{
  int somme = 0;
  int moyenne = 0;
  for (int i = 0; i < nombreMesure; i++)
  {
    somme += analogRead(pinMesure)/4; //On ramene la mesure 10 bits à 8 bits
    delay(10); //on laisse l'ADC recupérer de la conversion
  }
  moyenne = somme/nombreMesure;
  return moyenne;
}

void stop_moteur()
{
  Serial.println("-----MOTEUR STOP-----");
  DC1 = 0;
  DC2 = 0;
  Consigne_PWM1 = 0; 
  Consigne_PWM2 = 0;
  analogWrite(PIN_ROUE_1, 0);
  analogWrite(PIN_ROUE_2, 0);
}

void avancer(byte DC1, byte DC2)
{  
  //On rammène les commandes en % à un 8 bit non-signé
  Consigne_PWM1 = map(DC1, 0, 100, 0, 255); 
  Consigne_PWM2 = map(DC2, 0, 100, 0, 255);
  
  //On applique les consignes aux roues
  analogWrite(PIN_ROUE_1, Consigne_PWM1);
  analogWrite(PIN_ROUE_2, Consigne_PWM2);
}

void mesurer_vitesses_roues()
{
  //On mesure les PWM effectifs
  Reel_PWM1 = PWM_mesure(PIN_FEEDBACK_ROUE_1, nombreMesurePWM);
  Reel_PWM2 = PWM_mesure(PIN_FEEDBACK_ROUE_2, nombreMesurePWM);
  
  //On convertit PWM en volts pour le debug
  Consigne_V1 = (float) Consigne_PWM1/255.0 * 5.0;
  Consigne_V2 = (float) Consigne_PWM2/255.0 * 5.0;
  Reel_V1 = (float) Reel_PWM1/255.0 * 5.0;
  Reel_V2 = (float) Reel_PWM2/255.0 * 5.0;
}

void  afficher_vitesses_roues()
{
  //On renvoie les consignes de DC, les PMW interprétées et les PWM effectifs
  /*
  Serial.print("DC1 = ");
  Serial.println(DC1);
  Serial.print("Consigne_PWM1 = ");
  Serial.println(Consigne_PWM1);
  Serial.print("Reel_PWM1 = ");
  Serial.print(Reel_PWM1);
  Serial.println(" V");
  Serial.print("Consigne_V1 = ");
  Serial.println(Consigne_V1);
  Serial.print("Reel_V1 = ");
  Serial.print(Reel_V1);
  Serial.println(" V");
  
  Serial.print("DC2 = ");
  Serial.println(DC2);
  Serial.print("Consigne_PWM2 = ");
  Serial.println(Consigne_PWM2);
  Serial.print("Reel_PWM2 = ");
  Serial.print(Reel_PWM2);
  Serial.println(" V");
  Serial.print("Consigne_V2 = ");
  Serial.println(Consigne_V2);
  Serial.print("Reel_V2 = ");
  Serial.print(Reel_V2);
  Serial.println(" V");
  */

  Serial.print("Roue 1 : ");
  Serial.print(DC1);
  Serial.println(" %");
  
  Serial.print("Roue 2 : ");
  Serial.print(DC2);
  Serial.println(" %");
}

long calculer_temps_deplacement(int distance)
{
//  int vitesse_angulaire = VITESSE_ANGULAIRE_MAX * 2*PI/60 / 1000 * DC1; //Il faut convertir la vitesse angulaire de tr/min à rad/ms
  long vitesse_angulaire = TENSION_ALIM_MOTEUR * DC1 / CONSTANTE_VITESSE_MOTEUR /100;
  Serial.print("Vitesse angulaire : ");
  Serial.print(vitesse_angulaire);
  Serial.println(" rad/s");
  
  temps_deplacement = (long) distance*1000 /(vitesse_angulaire*RAYON_ROUE/10);
  Serial.print("Temps deplacement : ");
  Serial.print(temps_deplacement);
  Serial.println(" ms");

  //Simple protection en cas d'erreur du à la capacité de calcul
  if (temps_deplacement < 0)
  {
    Serial.println("Erreur : temps negatif");
    return 0;
  }
  
  return temps_deplacement;
}
