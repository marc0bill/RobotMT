#include <p33fj128mc804.h>
#include "adc.h"
#include "init_pic.h"
#include "node.h"
#include "uart.h"
#include <stdio.h>
#include <stdlib.h> // stdlib.h is included for the rand() and srand() function call

//int tableADC[5];
//int idAn =0;
//char sizeU2Tx;
//char strU2Tx[UxTx_length];

void init_ADC( int amask)
{
    AD1PCFGL = amask;      // select analog input pins
    AD1CON1 = 0x04E0;     // data output format-integer, auto convert after end of sampling.12bit Operation mode. No need to include a delay loop to provide time for completion of sampling
    AD1CSSL = 0;          // no scanning required
    //AD1CON3 = 0x1FFF ;     // Use internal clock, max sample time avail is 31Tad, conversion time Tad = 128*Tcy = 128*(2/Fosc) = 256/8MHz = 32us which is > (required)75ns ); 31 Tad = 31*32us = 992us is the sample time. About 100samples/sec
    AD1CON3 = 0x8E01;       //Use external clock, max sample time is 14Tad, conversion time Tad = 4*Tosc;
	AD1CON2 = 0;          // use MUXA, AVss and AVdd are used as Vref+/-
    //IEC0bits.AD1IE=1;                   // enable "conversion Interrupt"                // Clear interrupt flag bit
    //IPC3bits.AD1IP=0b001;               // priority 1 
    AD1CON1bits.ADON = 1; // turn on the ADC
} //initADC


int readADC(int channel)
{
	AD1CHS0bits.CH0SA = channel;			// Select the channel to convert
	IFS0bits.AD1IF = 0; 					// Clear ADC interrupt flag
	AD1CON1bits.DONE=0;						// Clear Done Flag
	AD1CON1bits.SAMP=1; 					// Start sampling 

    while (!AD1CON1bits.DONE);  // wait to complete the conversion. DONE will be set as soon as conversion ends
	AD1CON1bits.ASAM = 0; 					// Then stop sample/convert...
	return(ADC1BUF0);
}



/*
void init_ADC( void )
{
    AD1CON1 = 0; // set everything to zero to start with.
    AD1CON1bits.ADON = 0; // turn ADC off.
    AD1CON1bits.ADSIDL = 0; // continue module operation in idle mode.
    AD1CON1bits.ADDMABM = 1; // DMA buffers are written in the order of conversion.
    AD1CON1bits.AD12B = 0; // set to 10bit mode.
  //AD1CON1bits.FORM = 3; // set data output to signed fractional.
    AD1CON1bits.FORM = 0; // set data output to integer.
    AD1CON1bits.SSRC = 0; // manual conversion. clearing sample bit manually.
    AD1CON1bits.SIMSAM = 1; // collect samples from channels 0, 1, 2, 3 simultaneously.
    AD1CON1bits.ASAM = 0; // manual sample. samples when SAMP bit is set.
    AD1CON1bits.SAMP = 0; // sample enable bit.
    AD1CON1bits.DONE = 0; // ADC conversion status bit.

    AD1CON2 = 0; // set everything to zero to start with.
    AD1CON2bits.VCFG = 0; // converter voltage ref. set to AVdd and AVss.
    AD1CON2bits.CSCNA = 0; // input scan select bit. set to do not scan.
  //AD1CON2bits.CHPS = 0; // channel select bits. set to just channel 0;
    AD1CON2bits.CHPS = 3; // channel select bits. set channel 0, channel 1, channel 2 and channel 3;
    AD1CON2bits.BUFS = 0; // buffer fill status (invalid as BUFM is 0);
    AD1CON2bits.SMPI = 0; // ADC interrupt is generated after every sample/conversion.
    AD1CON2bits.BUFM = 0; // buffer fill mode. set to always start filling from start address (0x0).
    AD1CON2bits.ALTS = 0; // Alternate input sample mode. set to always uses channel input from sample A.

    AD1CON3 = 0; // set everything to zero to start with.
    AD1CON3bits.ADRC = 0; // ADC conversion clock derived from system clock.
  //AD1CON3bits.SAMC = 0; // auto sample time bits, TAD, set to 0.
    AD1CON3bits.SAMC = 12; // auto sample time bits, TAD, set to 12.
    AD1CON3bits.ADCS = 0; // ADC conversion clock set to 0. 1 * TCY = TAD.

    AD1CON4 = 0; // set everything to zero to start with.
    AD1CON4bits.DMABL = 0; // allocates 1 word of buffer to each analogue input.

    AD1CHS123 = 0; // everything set to zero as not using channels 1, 2, or 3.

    AD1CHS0 = 0; // set everything to zero to start with.
    AD1CHS0bits.CH0NB = 0; // channel 0 negative input, set by CH0NA. sample B.
    AD1CHS0bits.CH0SB = 0; // channel 0 positive input, set by CH0SA. sample B.
    AD1CHS0bits.CH0NA = 0; // channel 0 negative input, for sample A. set to VREFL.
    AD1CHS0bits.CH0SA = 0; // channel 0 positive input is AN0.

    AD1CSSL = 0; // input scan register set to zero as not using it.

    AD1PCFGL = 0; // port configuration, set to analogue mode, ADC samples voltage.

    AD1CON1bits.ADON = 1; // turn on ADC
}
*/


/*     
void readADC(int ADCValue )
{                      
    AD1CON1bits.SAMP = 1; // Start sampling
    DELAY(1); // Wait for sampling time (1ms)
    AD1CON1bits.SAMP = 0; // Start the conversion
    while (!AD1CON1bits.DONE); // Wait for the conversion to complete
    ADCValue = ADC1BUF0; // Read the conversion result
}
*/


/*
void __attribute__((interrupt, no_auto_psv)) _T3Interrupt( void ){
    
    IFS0bits.T3IF=0;            //acquitement du flag
    AD1CHS0bits.CH0SA = idAn; // Select from AN0 through AN5 for CH0
    //AD1CON1bits.DONE=0;
    //PORTBbits.RB6=!LATBbits.LATB6;  // test
    
}
void __attribute__((interrupt, no_auto_psv)) _ADC1Interrupt(void){ 
    
    //result= ADC1BUF0;
    AD1CON1bits.DONE=0;
    tableADC[idAn] = ADC1BUF0;  // Get the conversion result
    IFS0bits.AD1IF = 0;           // clear ADC Interrupt Flag
    if(idAn<6)
    idAn ++;
    else idAn =0;
    sizeU2Tx=sprintf(strU2Tx, "AdcValue = %d \r\n",tableADC[idAn]);
    fctU1Tx_string(strU2Tx,sizeU2Tx);
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
    IFS0bits.T3IF=0;              /// Clear Timer1 Interrupt Flag // 
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
 */