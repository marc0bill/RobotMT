/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef _ADC_H
#define	_ADC_H


//void ADC1_Init(void);
//void T3_init(void);
//void __attribute__((interrupt, no_auto_psv)) _T3Interrupt( void );
//void __attribute__((interrupt, no_auto_psv)) _ADC1Interrupt(void);

//void init_ADC( void );
void init_ADC( int amask);
int readADC(int channel);

// Select the channel to convert
#define BAT2_14V 0   //muxSEL=000 => Y0 in AN0 
#define BAT2_18V 1   //muxSEL=001 => Y0 in AN0 
#define BAT23_22V 2   //muxSEL=010 => Y0 in AN0 
#define BAT12_11V 3   //muxSEL=011 => Y0 in AN0 
#define BAT1_7V 4   //muxSEL=100 => Y0 in AN0 
#define BAT1_3V 5   //muxSEL=101 => Y0 in AN0 

#define AN0 0   //Channel 0 on
#define AN1 1   //Channel 1 on
#define AN2 2   //Channel 2 on 
#define AN3 3   //Channel 3 on 
#define AN4 4   //Channel 4 on
#define AN5 5   //Channel 5 on

#endif	/* XC_HEADER_TEMPLATE_H */
