/*
-----------------Choses à faire-------------
  - Faire un schema spice de l'arduino pour ce projet et les futurs
  - Faire un schema spice du circuit
*/

//---Definition des pins
#define PIN_ROUE_1 5
#define PIN_ROUE_2 6
#define PIN_FEEDBACK_ROUE_1 A0
#define PIN_FEEDBACK_ROUE_2 A3

//---Definition des variables

int DC1 = 0, DC2 = 0; //Rapports cycliques des roue en %
byte unsigned Consigne_PWM1 = 0, Consigne_PWM2 = 0; // Valeur des rapports cycliques sur 8 bits non-signés
byte unsigned Reel_PWM1 = 0, Reel_PWM2 = 0; // Valeurs des RC effectifs
float Consigne_V1 = 0, Consigne_V2 = 0, Reel_V1 = 0, Reel_V2 = 0;

void setup() {

  //---Configuration des pins
  pinMode(PIN_ROUE_1, OUTPUT);
  pinMode(PIN_ROUE_2, OUTPUT);
  pinMode(PIN_FEEDBACK_ROUE_1, INPUT);
  pinMode(PIN_FEEDBACK_ROUE_1, INPUT);

  //---Configuration Communication Série
  Serial.begin(baudrate);
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
    //On suppose les données envoyées comme suit:
    //Rapport_cyclique_roue_1 Rapport_cyclique_roue_2
    //Exemple : 50 35
    
    DC1 = Serial.parseInt(); //On lit la commande de la roue 1
    //Serial.parseInt(); //On vide le buffer (retour chariot)
    Consigne_PWM1 = map(DC1, 0, 100, 0, 255); //On rammène la commande en % à un 8 bit non-signé
    delay(10); //On laisse 10ms à l'ADC pour se remettre de la conversion
    
    DC2 = Serial.parseInt(); //On lit la commande de la roue 2
    Consigne_PWM2 = map(DC2, 0, 100, 0, 255);
    delay(10);

    Serial.parseInt();

    //On applique les consignes aux roues
    analogWrite(PIN_ROUE_1, Consigne_PWM1);
    analogWrite(PIN_ROUE_2, Consigne_PWM2);

    //On mesure les PWM effectifs
    Reel_PWM1 = PWM_mesure(PIN_FEEDBACK_ROUE_1, 50);
    Reel_PWM2 = PWM_mesure(PIN_FEEDBACK_ROUE_2, 50);

    //On convertit PWM en volts pou rle debug
    Consigne_V1 = (float) Consigne_PWM1/255.0 * 5.0;
    Consigne_V2 = (float) Consigne_PWM2/255.0 * 5.0;
    Reel_V1 = (float) Reel_PWM1/255.0 * 5.0;
    Reel_V2 = (float) Reel_PWM2/255.0 * 5.0;


    //On renvoie les consignes de DC, les PMW interprétées et les PWM effectifs
    Serial.print("DC1 = ");
    Serial.println(DC1);
    Serial.print("Consigne_PWM1 = ");
    Serial.println(Consigne_PWM1);
    Serial.print("Reel_PWM1 = ");
    Serial.println(Reel_PWM1);
    Serial.print("Consigne_V1 = ");
    Serial.println(Consigne_V1);
    Serial.print("Reel_V1 = ");
    Serial.println(Reel_V1);

    Serial.print("DC2 = ");
    Serial.println(DC2);
    Serial.print("Consigne_PWM2 = ");
    Serial.println(Consigne_PWM2);
    Serial.print("Reel_PWM2 = ");
    Serial.println(Reel_PWM2);
    Serial.print("Consigne_V2 = ");
    Serial.println(Consigne_V2);
    Serial.print("Reel_V2 = ");
    Serial.println(Reel_V2);
    
  }
  /*
  Reel_PWM1 = analogRead(PIN_FEEDBACK_ROUE_1) / 4;
  Serial.print(Consigne_PWM1);
  Serial.print("\t");
  Serial.println(Reel_PWM1);
  */

}

void verifierConnection() 
{
  while (Serial.available() <= 0) //tant qu'aucun caractère n'est disponible à la lecture
  { 
    Serial.println("Connexion stable");
    delay(300);
  }
}

int PWM_mesure(int pinMesure, int nombreMesure)
{
  int somme = 0;
  int moyenne = 0;
  for (int i = 0; i < nombreMesure; i++)
  {
    somme += analogRead(pinMesure)/4; //On ramene la mesure 10 bits à 8 bits
    delay(10);
  }
  moyenne = somme/nombreMesure;
  return moyenne;
}
