int baudrate = 9600;
int DC1 = 0, DC2 = 0; //Rapports cycliques des roue en %
byte unsigned Consigne_PWM1 = 0, Consigne_PWM2 = 0; // Valeur des rapports cycliques sur 8 bits non-signés
byte unsigned Reel_PWM1 = 0, Reel_PWM2 = 0; // Valeurs des RC effectifs
float Consigne_V1 = 0, Consigne_V2 = 0, Reel_V1 = 0, Reel_V2 = 0;

unsigned long duration = 0; //longueur de largeur d'impulsion en µs
unsigned long frequence_pwm = 62500;//frequence de base en Hz du pwm des broches 5 et 6
unsigned long periode_pwm = 1000000 / frequence_pwm; //periode pwn en µs
unsigned long duty_cycle = 0;
