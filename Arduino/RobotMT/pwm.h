//---Definition des pins
#define PIN_ROUE_1 5
#define PIN_ROUE_2 6
#define PIN_FEEDBACK_ROUE_1 A0
#define PIN_FEEDBACK_ROUE_2 A3


//---Definition des variables
int DC1 = 0, DC2 = 0; //Rapports cycliques des roue en %
byte unsigned Consigne_PWM1 = 0, Consigne_PWM2 = 0; // Valeur des rapports cycliques sur 8 bits non-signés
byte unsigned Reel_PWM1 = 0, Reel_PWM2 = 0; // Valeurs des RC effectifs
float Consigne_V1 = 0, Consigne_V2 = 0; //Tension de consigne
float Reel_V1 = 0, Reel_V2 = 0; //Tension relle

//---Prototypes des fonctions
