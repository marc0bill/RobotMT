/*
Club Robot - Polytech Marseille

Fonctions liées à l'utilisation du module PWM1
initialise PWM1H1 et PWM1H2

Révision:     	$Rev: $
Auteur:       	$Author: $
Date révision: 	$Date:  $
projet:      	$URL: $


changements:
0.0.3: 14/08/2011
	- ajout fonction interruption PWM (postcaler à 15 -> inter de 0,4ms)
	- correction code initialisation (prediviseur 1, ajout conf periode!)
	- pmw fonctionnel à 40kHz : rapport cyclique max à 2*P1TPERVAL
0.0.2: 29/01/2011
	- ajout fonction interruption PWM (postcaler à 10 -> inter de 0,5ms)
	- correction code initialisation (prediviseur 4, ajout conf periode!, passage ne free running mode au lieau du up/down)
	- Ajout code manquant par rapport version du stagiare (normalement ok maintenant?)
0.0.1: 18/11/2010


Pour la commande PWM on a une plage de 0 à 499 soit 500 valeurs.
On peux envisager de supprimer la commande de sens des moteurs, et mettre DC(=TH/T)=0.5 : arret (~ 250), DC < 0.5: sens 1 et DC > 0.5 : sens 2? 
*/
#include "header.h"
#include "pwm.h"
#include "asserv.h"
#include "move.h"
/***************************************************************************************
Initialisation PWM

entrées : -
sortie : - 
*/
void init_PWM1()              // configure PWM1
{
	P1TPER= P1TPERVAL; 		// période du PWM -> (FCY/(FPWM*PTCKPS))-1 (cf fichier "header.h")
	PWM1CON1bits.PMOD1 = 1 ; // PWM I/O pin pair is in the Independent Output mode
	PWM1CON1bits.PMOD2 = 1 ; // PWM I/O pin pair is in the Independent Output mode
	PWM1CON1bits.PMOD3 = 1 ; // PWM I/O pin pair is in the Independent Output mode
	PWM1CON1bits.PEN1H = 0 ;
	PWM1CON1bits.PEN1L = 1 ; // pin is enabled for PWM2 output
	PWM1CON1bits.PEN2H = 0 ;
	PWM1CON1bits.PEN2L = 1 ; // pin is enabled for PWM2 output
	PWM1CON1bits.PEN3H = 0 ;
	PWM1CON1bits.PEN3L = 0 ;
	
	P1TCONbits.PTSIDL=0; //PWM time base runs in CPU Idle mode
	P1TCONbits.PTMOD=0; //free running mode
    P1TCONbits.PTCKPS=0;//PWM time base input clock period is 1 TCY (1:1 prescale) fréquence cycle/1
// PTCKPS<1:0>: PWM Time Base Input Clock Prescale Select bits
// 11 = PWM time base input clock period is 64 TCY (1:64 prescale)
// 10 = PWM time base input clock period is 16 TCY (1:16 prescale)
// 01 = PWM time base input clock period is 4 TCY (1:4 prescale)
// 00 = PWM time base input clock period is TCY (1:1 prescale)
// ATTENTION : Modifier P1TPERVAL dans pwm.h en consequence.
    P1TCONbits.PTOPS=15; // 1:16 postscale, interruption tous les 16*PeriodePWM=0,4 ms

	P1TMRbits.PTDIR=0;//PWM time base is counting up

	P1SECMPbits.SEVTDIR=0;//A Special Event Trigger occurs

	PWM1CON2bits.UDIS=0;//Updates from Duty Cycle and Period Buffer registers are enabled
    PWM1CON2bits.OSYNC=1;//Output overrides via the PxOVDCON register are synchronized to the PWM time base
 	PWM1CON2bits.IUE=0;//Updates to the active PxDC registers are synchronized to the PWM time base
 	PWM1CON2bits.SEVOPS=0;//1:1 postscale

	P1DTCON1bits.DTBPS=0b00;//Clock period for Dead-Time Unit B is TCY
	P1DTCON1bits.DTAPS=0b00;//Clock period for Dead-Time Unit B is TCY

	P1DTCON2bits.DTS2A=0;//dead time provide from unit A
	P1DTCON2bits.DTS1A=0;//dead time provide from unit A

	PDC1=0x0000;//duty cycle PWM1=0
	PDC2=0x0000;//duty cycle PWM2=0
	IFS3bits.PWM1IF=0;
	IPC14bits.PWM1IP = 7;	//PWM1 interrupt priority : High level !!
	IEC3bits.PWM1IE=1;

	P1TCONbits.PTEN = 1 ; //PWM time base is on

/*
	IPC15bits.FLTA1IP	= 4;	// PWM1 fault A
	IFS3bits.FLTA1IF	= 0;	// clear PWM1 fault A interrupt flag
	IEC3bits.FLTA1IE	= 0;	// PWM1 fault A interrupt enable
*/
 }



/********************************************************************************
interruption timer PWM1
*/
void __attribute__ ((interrupt, no_auto_psv)) _MPWM1Interrupt(void)
{	// passage tous les 0.4ms
	IFS3bits.PWM1IF=0;		// acquittement
	static int passage=0;
	static double alpha_M[2];

	if(passage==0)
	{
		aff_Consigne();
	}
	passage++;
	if(passage>nb_IT_PWM-1)
	{
		passage=0;
        
        Consigne.mode=3;
        FlagMove.Start=1;
        /*
        Consigne.Vts_M1=100.;
        Consigne.Vts_M2=200.0;
         */
		asservisement_roue(alpha_M);
	}
	
}
