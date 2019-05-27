#include <p33fj128mc804.h>
#include "adc.h"
#include "init_pic.h"
#include "node.h"
#include "uart.h"
#include <stdio.h>
#include <stdlib.h> // stdlib.h is included for the rand() and srand() function call


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
