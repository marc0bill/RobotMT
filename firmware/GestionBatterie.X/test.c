/******************************************************************************
TITLE: Convesion A/D dsPic33F
AUTHOR: 
DESCRIPTION: 
******************************************************************************/
#include <stdio.h>
#include <stdlib.h> // stdlib.h is included for the rand() and srand() function call
#ifdef __dsPIC33FJ128MC804__
#include <p33fj128mc804.h>
#endif
//-- PIC Configuration --------------------------------------------------------
_FOSCSEL(FNOSC_PRIPLL); // Primary Oscillator (XT, HS, EC) w/ PLL
_FOSC(FCKSM_CSECMD & OSCIOFNC_OFF  & POSCMD_XT);
    //FCKSM_CSECMD  Clock switching is enabled, Fail-Safe Clock Monitor is disabled
    //OSCIOFNC_OFF  OSC2 pin has clock out function
    //POSCMD_XT     XT Oscillator Mode
_FWDT(FWDTEN_OFF);
    // FWDTEN_OFF   Watchdog timer enabled/disabled by user software
//Configuration pin I2C
_FPOR(ALTI2C_ON);
//----------
int idAn =0;
int tableADC[5];
// int result;
//Functions and Variables :
int main (void);
void ADC1_Init(void);
void T3_init(void);
void __attribute__((interrupt, no_auto_psv)) _T3Interrupt( void );
void __attribute__((interrupt, no_auto_psv)) _ADC1Interrupt(void);
//-----------Pic Interruption
void __attribute__((interrupt, no_auto_psv)) _T3Interrupt( void ){
    
    IFS0bits.T3IF=0;            //acquitement du flag
    AD1CHS0bits.CH0SA = idAn; // Select from AN0 through AN5 for CH0
    AD1CON1bits.DONE=1;
    PORTBbits.RB6=!LATBbits.LATB6;  // test
    
}
void __attribute__((interrupt, no_auto_psv)) _ADC1Interrupt(void){ 
    
    //result= ADC1BUF0;
    tableADC[idAn] = ADC1BUF0;  // Get the conversion result
    IFS0bits.AD1IF = 0;           // clear ADC Interrupt Flag
    idAn ++;
    
  }

// Timer config
void T3_init(void){
    T2CONbits.T32=0;              //désactiver T2 et T4
    T4CONbits.T32=0;
    T3CONbits.TCKPS=11;           //prescale max
    PR3=0xFFFF;                   //maximum period
    T3CONbits.TCS=0;              //Internal clock
    T3CONbits.TGATE=0;            //Pas d'accumalation.....Gated time accumulation disabled
    //T3CONbits.TSIDL=0;          //Continue timer operation même en mode Idle
    T3CONbits.TON=1;              // T3 ON
    IPC2bits.T3IP=5;              //Interrupt is priority 5 (highest priority interrupt)
    IFS0bits.T3IF=0;              /* Clear Timer1 Interrupt Flag */ 
    IEC0bits.T3IE=1;              // Interrupt request enabled  
     //End Timer3
    
}
 //ADC module config
void ADC1_Init(void){
 
    AD1PCFGL=0b11000000;                   // AN0--> AN5                  -------changed
    //AD1PCFGL=0xFFFF;                     // Default all ADC Pins Digital
    //AD1PCFGLbits.PCFG0 = 0;             // AN0 as Analog Input
    //ADC1BUF0 = 0;                       // clear the ADC memory positions ... just in case
    AD1CON2bits.VCFG=0b000;             //Vref
    AD1CON3bits.ADCS=0b00000000;        //Conversion Clock  TAD=Tcy
    AD1CON2bits.CHPS=0b00;             //convert CH0 
     // Set up A/D conversion clock to ADC Internal RC so that it will work in SLEEP mode      
	    //	AD1CON3bits.ADRC=1;			// ADC Clock is derived from ADC Internal RC
    //AD1CON3bits.ADRC = 0;    // Clock derived from system clock----- à revoir
    //AD1CON2bits.SMPI   =0;		// SMPI must be 0   ---- changed 23/05
    AD1CON1bits.AD12B=0b1;                // 12-bits ADC operation 
    AD1CON1bits.FORM=0b00;              // Data-output form signed       
    AD1CON1bits.ASAM=0b1;               //ADC Sample Auto-Start bit: Sampling begins immediately after conversion     
    AD1CON3bits.SAMC=0b01110;           //14*Tad au max
    AD1CON1bits.SSRC=0b010;             //Timer3 for ADC1   
    //AD1CON1bits.ADSIDL=0;               //continue la conv en mode idle
    IFS0bits.AD1IF = 0;                 // Clear interrupt flag bit
    IEC0bits.AD1IE=1;                   // enable "conversion Interrupt"
    IPC3bits.AD1IP=0b001;               // priority 1 
    AD1CON1bits.DONE = 0;               //Making sure that there is any conversion in progress
    AD1CON1bits.ADON=1;                 // turn on the ADC
       //End ADC1
    }
//-- Programme Principal ------------------------------------------------------
int mainTest(void){
    //I/O
    TRISBbits.TRISB6=0;     // led  RB6
    LATBbits.LATB6=0;
    TRISAbits.TRISA0=1;     // AN0 is input
    T3_init();             //Initialize Timer3
    ADC1_Init();            //Initialize the A/D converter
    //AD1CON1bits.SAMP=1;                 //--for sleep mode--ADC S&H amplifiers are sampling
    while(1){
        /* A_Sleep(); // Generate Start of Conversion and enter sleep mode
                    * Start of conversion is issued in the background loop 
                    and device enters sleep mode immediately after that.
                    When the ADC conversion is completed in sleep mode, it wakes up the device and enters ADC Interrupt*/
	}
}
