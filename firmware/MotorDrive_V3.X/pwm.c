/*
 * File:   pwm.c
 * Author: g15016154
 *
 * Created on 15 mai 2019, 11:24
 */


#include "xc.h"
#include "pwm.h"
#include "main.h"
#include "uart.h"

void init_PWM1()
{
    PWM1CON2bits.UDIS=0;    //Autorisation d'écrire dans les registres de duty cycle et les registres de periodes
    P1TCONbits.PTEN=1 ;     //PWM time base is on
    P1TCONbits.PTSIDL=0;    //PWM time base runs in CPU Idle mode //Pourquoi? Le PWM devrait être en arret lors de l'IDLE
    P1TCONbits.PTOPS=15;    // 1:16 postscale, interruption tous les 16*PeriodePWM=0,4 ms
    P1TCONbits.PTCKPS=0;    //PWM time base input clock period is 1 TCY (1:1 prescale) fréquence cycle/1
    P1TCONbits.PTMOD=0b00;  //free running mode
    P1TMRbits.PTDIR=0;      //PWM time base is counting up
    P1TPER= P1TPERVAL;      // période du PWM -> (FCY/(FPWM*PTCKPS))-1
    PTMR = 0 ;               //Initialisation du compteur-période à 0 (compteur permettant d'identifier la fin de la periode)
    
    //--Gestion des special event -- inutilisés pour l'instant donc aucune importance
    P1SECMPbits.SEVTDIR=0;  //A special event trigger will occur when the PWM time base is counting up 
    P1SECMPbits.SEVTCMP=0;  //Valeur de trigger du special event
    PWM1CON2bits.SEVOPS=0b0000;  //postcale du STE à 1
    
    //---Configuration des Pins
    PWM1CON1bits.PMOD1 = 1 ;    // PWM1 I/O pin pair 1 is in the Independent Output mode
	PWM1CON1bits.PMOD2 = 1 ;    // PWM1 I/O pin pair 2 is in the Independent Output mode
	PWM1CON1bits.PMOD3 = 1 ;    // PWM1 I/O pin pair 3 is in the Independent Output mode
                                // La I/O pin par 4 fait partie du module PWM2
    PWM1CON1bits.PEN1H = 0 ;    // PWM1H1 pin disabled; I/O pin becomes GPIO
	PWM1CON1bits.PEN1L = 1 ;    // PWM1L1 pin is enabled for PWM1 output //Une roue doit être reliée à cette pin
    PWM1CON1bits.PEN2H = 0 ;    // PWM1H2 pin disabled; I/O pin becomes GPIO
	PWM1CON1bits.PEN2L = 1 ;    // PWM1L2 pin is enabled for PWM1 output //Une roue doit être reliée à cette pin
	PWM1CON1bits.PEN3H = 0 ;    // PWM1H3 pin disabled; I/O pin becomes GPIO
	PWM1CON1bits.PEN3L = 0 ;    // PWM1L3 pin disabled; I/O pin becomes GPIO

    
    PWM1CON2bits.IUE = 0;       // Mise à jour des registres de rapport cycliques synchronisé avec la bse de temps PWM
    
    //---Output Override Control --inutilisé pour l'instant
    PWM1CON2bits.OSYNC = 1;     // Synchronisé sur base de temps PWM
    
    //----Dead time------------------
    
    P1DTCON1bits.DTBPS=0b00;//Clock period for Dead-Time Unit B is TCY
	P1DTCON1bits.DTAPS=0b00;//Clock period for Dead-Time Unit B is TCY

	P1DTCON2bits.DTS2A=0;//dead time provide from unit A
	P1DTCON2bits.DTS1A=0;//dead time provide from unit A
    
    
    //Registres de duty cycle
    P1DC1 = P1TPERVAL/2;    //Rapport cyclique 1 initialisé à 50%
    P1DC2 = P1TPERVAL/2;    //Rapport cyclique 2 initialisé à 50%
    
    
}