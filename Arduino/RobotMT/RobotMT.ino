
//#include "pwm.h"
//#include "uart.h"


//---Definition des pins
#define PIN_ROUE_1 5
#define PIN_ROUE_2 6
#define PIN_FEEDBACK_ROUE_1 A0
#define PIN_FEEDBACK_ROUE_2 A3

//---Definition des variables
#define BAUDRATE 9600
int DC1 = 0, DC2 = 0; //Rapports cycliques des roue en %
byte unsigned Consigne_PWM1 = 0, Consigne_PWM2 = 0; // Valeur des rapports cycliques sur 8 bits non-signés
byte unsigned Reel_PWM1 = 0, Reel_PWM2 = 0; // Valeurs des RC effectifs
float Consigne_V1 = 0, Consigne_V2 = 0, Reel_V1 = 0, Reel_V2 = 0;
String action = "";
int id_action = 0;


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

  if (Serial.available() > 0 and Serial.peek() != ' ') //Si on reçois une donnée
  {
    Serial.println("-----Donnees recues-----");
    action = Serial.readStringUntil(' '); //lit la chaine de caractères difinissant la commande
    
    Serial.print("Action : ");
    Serial.println(action);
   
    if (action == "stop")
    {
      DC1 = 0;
      DC2 = 0;
    } else if (action == "vtsm")
    {
      //On suppose les données envoyées comme suit:
      //Rapport_cyclique_roue_1 Rapport_cyclique_roue_2
      //Exemple : vtsm 50 35
      
      DC1 = Serial.parseInt(); //On lit la commande de la roue 1
      Consigne_PWM1 = map(DC1, 0, 100, 0, 255); //On rammène la commande en % à un 8 bit non-signé
      
      DC2 = Serial.parseInt(); //On lit la commande de la roue 2
      Consigne_PWM2 = map(DC2, 0, 100, 0, 255);
      
      Serial.parseInt(); //On vide le buffer d'entrée
    } else 
    {
      Serial.println("Erreur : commande inconnue");
    }
    
    //On rammène les commandes en % à un 8 bit non-signé
    Consigne_PWM1 = map(DC1, 0, 100, 0, 255); 
    Consigne_PWM2 = map(DC2, 0, 100, 0, 255);

    //On applique les consignes aux roues
    analogWrite(PIN_ROUE_1, Consigne_PWM1);
    analogWrite(PIN_ROUE_2, Consigne_PWM2);

    //On mesure les PWM effectifs
    Reel_PWM1 = PWM_mesure(PIN_FEEDBACK_ROUE_1, 50);
    Reel_PWM2 = PWM_mesure(PIN_FEEDBACK_ROUE_2, 50);

    //On convertit PWM en volts pour le debug
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
    
  }
  /*
  Reel_PWM1 = analogRead(PIN_FEEDBACK_ROUE_1) / 4;
  Serial.print(Consigne_PWM1);
  Serial.print("\t");
  Serial.println(Reel_PWM1);
  */

  //Serial.readString(); //on vide le buffer;
  delay(1000);
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
