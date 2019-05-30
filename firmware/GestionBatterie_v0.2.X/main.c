/**********************************************************************
* © 2008 Microchip Technology Inc.
*
* FileName:        main.c
* Dependencies:    Header (.h) files if applicable, see below
* Processor:       dsPIC33Fxxxx
* Compiler:        MPLAB® C30 v3.00 or higher
*
* SOFTWARE LICENSE AGREEMENT:
* Microchip Technology Incorporated ("Microchip") retains all ownership and 
* intellectual property rights in the code accompanying this message and in all 
* derivatives hereto.  You may use this code, and any derivatives created by 
* any person or entity by or on your behalf, exclusively with Microchip's
* proprietary products.  Your acceptance and/or use of this code constitutes 
* agreement to the terms and conditions of this notice.
*
* CODE ACCOMPANYING THIS MESSAGE IS SUPPLIED BY MICROCHIP "AS IS".  NO 
* WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED 
* TO, IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY AND FITNESS FOR A 
* PARTICULAR PURPOSE APPLY TO THIS CODE, ITS INTERACTION WITH MICROCHIP'S 
* PRODUCTS, COMBINATION WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
*
* YOU ACKNOWLEDGE AND AGREE THAT, IN NO EVENT, SHALL MICROCHIP BE LIABLE, WHETHER 
* IN CONTRACT, WARRANTY, TORT (INCLUDING NEGLIGENCE OR BREACH OF STATUTORY DUTY), 
* STRICT LIABILITY, INDEMNITY, CONTRIBUTION, OR OTHERWISE, FOR ANY INDIRECT, SPECIAL, 
* PUNITIVE, EXEMPLARY, INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, FOR COST OR EXPENSE OF 
* ANY KIND WHATSOEVER RELATED TO THE CODE, HOWSOEVER CAUSED, EVEN IF MICROCHIP HAS BEEN 
* ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT 
* ALLOWABLE BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY RELATED TO 
* THIS CODE, SHALL NOT EXCEED THE PRICE YOU PAID DIRECTLY TO MICROCHIP SPECIFICALLY TO 
* HAVE THIS CODE DEVELOPED.
*
* You agree that you are solely responsible for testing the code and 
* determining its suitability.  Microchip has no obligation to modify, test, 
* certify, or support the code.
************************************************************************/

/* The code example uses LEDs to indicate status
 * LED1 - Message Transmitted
 * LED2 - Message Received
 * LED3 - CAN BUS Error
 * LED4 - Data Payload CRC check error */
 
#include <stdio.h>
#include <stdlib.h> // stdlib.h is included for the rand() and srand() function call
#ifdef __dsPIC33FJ128MC804__
#include <p33fj128mc804.h>
#endif

#include "ECAN1Drv.h"
//#include "crc16.h"
#include "init_pic.h"
#include "node.h"
#include "adc.h"
#include "uart.h"

_FOSCSEL(FNOSC_PRIPLL); // Primary Oscillator (XT, HS, EC) w/ PLL
_FOSC(FCKSM_CSECMD & OSCIOFNC_OFF  & POSCMD_XT);
    //FCKSM_CSECMD  Clock switching is enabled, Fail-Safe Clock Monitor is disabled
    //OSCIOFNC_OFF  OSC2 pin has clock out function
    //POSCMD_XT     XT Oscillator Mode
_FWDT(FWDTEN_OFF);
    // FWDTEN_OFF   Watchdog timer enabled/disabled by user software
//Configuration pin I2C
_FPOR(ALTI2C_ON);

void Read_Batterie_Voltage(void);
void Read_Batterie_Tempreture(void);
void Read_Current(void);
void mux_Select(int sel);
/* Define the number of ECAN RX buffers. Only one TX buffer is used. This is 
 * explained in the readme file along with this code example. */
#define NUM_OF_RX_BUFFERS 8

/* Create the message arrays. Note the size of the TX Message. It is 7 (not 8)*/
int ecanTxMsgBuffer[7] __attribute__((space(dma)));
int ecanRxMsgBuffer[NUM_OF_RX_BUFFERS][8] __attribute__((space(dma)));

/* The received flag is checked in the main loop to compute CRC on the received
 * message and flags errors. The transmitNext flag  transmits the next packet.
 * The sentPacket  variable tracks the number of packets sent.*/
volatile int received = 0;
volatile int transmitNext = 1;
int sentPacket = 0;
char sizeU1Tx;
char sizeU2Tx;
int data[8];
//	int crcval;
char strU1Tx[UxTx_length];
char strU2Tx[UxTx_length];
int AdcValue;
int sel = 0;
int channel_current = 1;
int channel_temp = 3;


/* In Register Indirect mode, the ECAN/DMA cannot differentiate between buffers.
 * The application must keep track of where the received message was stored */
volatile int rxBufferIndex = -1;
int rxIndex;
int txBufferIndex = 0;


void RandomWait(void){
	/* This function will wait for a randon period
	 * of time before exiting. The rand() and srand() functions
	 * used for generating the random numbers */
	
	unsigned long wait;
	wait = rand();
	srand(wait);
    wait *=16;
	while(wait > 0){
		wait--;
	}
}

int main(void){
    
    int readBatterieVoltage_Temp=0;
    int readCurrent = 0;
    
    
    /******* Activation du relay *******/
    TRISAbits.TRISA7 =0;
    LATAbits.LATA7 = 1; 

    
    
	/* Configure the dsPIC */
	init_pic();
    init_ADC(0);
    initUART1(57600);//9600, 19200, 57600 // CONCERNE UART
    
	ECAN1DMAConfig(__builtin_dmaoffset(ecanTxMsgBuffer),
					__builtin_dmaoffset(ecanRxMsgBuffer), 
					NUM_OF_RX_BUFFERS);
    
	ECAN1ClockConfig(); //Configuration de la clock
	ECAN1InterruptConfig();
	ECAN1RxFiltersConfig();
	ECAN1TxRxBuffersConfig();
	ECAN1SetOPMode();

	while(1){
       //PORTBbits.RB13 != PORTBbits.RB13;
        //Read multi-channel
        /* 
        while(channel <7){
        AdcValue=readADC(channel);
        DELAY(10);
        data[channel]=AdcValue;
        sizeU2Tx=sprintf(strU2Tx, "AdcValue = %d \r\n",AdcValue);
        fctU1Tx_string(strU2Tx,sizeU2Tx);
        //if (channel < 9)
            channel++;
        //else channel =0;
        DELAY(10);
        }
        channel =0;
        */
        
        /**************NIVEAU BATTERIE*****************/
        if(!readBatterieVoltage_Temp){
            Read_Batterie_Voltage();
            Read_Batterie_Tempreture();
            readBatterieVoltage_Temp=40;
        }
        else
            readBatterieVoltage_Temp--;
        if(!readCurrent){
            Read_Current();
            readCurrent=20;
        }
        else 
            readCurrent--;
		/*		
		if(received == 1){
			received = 0;
			rxIndex = rxBufferIndex;
            sizeU1Tx=sprintf(strU1Tx, "%d\t%d\t%d\t%d\t%d%d%d%d\n", rxIndex,
                    ecanRxMsgBuffer[rxIndex][0],ecanRxMsgBuffer[rxIndex][1],
                    ecanRxMsgBuffer[rxIndex][2],ecanRxMsgBuffer[rxIndex][3],
                    ecanRxMsgBuffer[rxIndex][4],ecanRxMsgBuffer[rxIndex][5],ecanRxMsgBuffer[rxIndex][6]);
            fctU1Tx_string(strU1Tx,sizeU1Tx);
		}
        */
	}
}

void __attribute__((__interrupt__,no_auto_psv)) _C1Interrupt(void){
	/* Only the Transmit Message, Receive Message Events and Error flags are 
     * processed. You can check for the other events as well.*/
	
	_C1IF = 0;
	
	if(C1INTFbits.TBIF == 1){
		/* Transmit done. Set the flag so that the main application loop knows
         * that the message was transmitted */
		C1INTFbits.TBIF = 0;
		transmitNext = 1;
		LED1 != LED1;
		T1CONbits.TON = 1;	
	}
	
	if(C1INTFbits.RBIF == 1){
		/* Received a packet. Check if the rxBufferIndex is at the boundary
		 * and reset to initial condition if needed. 
		 * You can check the RXFUL flags if needed. */
		if(rxBufferIndex == (NUM_OF_RX_BUFFERS - 1))
			rxBufferIndex = -1;	
		
		C1INTFbits.RBIF = 0;
		C1RXFUL1 = 0;
		received = 1;
		rxBufferIndex ++;
		LED2 != LED2;
		T1CONbits.TON = 1;	
	}
		
	LED3 = LED_OFF;
	if(C1INTFbits.ERRIF == 1){
		C1INTFbits.ERRIF = 0;
		LED3 = LED_ON;
	}
}	

void DELAY(unsigned ms) {
    unsigned j;
    unsigned i;
    for (j = 0; j < ms; j++) {
        for (i = 0; i < 0x1F40; i++);
    }
}
void Read_Batterie_Voltage(void){
     mux_Select(sel);
     AdcValue=readADC(AN0);
        DELAY(10);
         /* ADC_output has 12 bits resolution
         * To send this data using the can bus, we need to put the higth 8 bits in data[1] and the low 4 bits in data[2]
         * data[0] is the id of the data. if battery level is less then 15V then id = 0xAA else id =[0xFF,...,0xFA]
         */
        data[1]=AdcValue>>4;
        data[2]=AdcValue && 0x00F;
        if((((data[1]<<4 + data[2])/4095)*3300*9.28)<=1500){
            data[0]=0xAA;
        }
        else
            data[0]=0xff - sel;
        sizeU2Tx=sprintf(strU2Tx, "AdcValue = %d \r\n",AdcValue); //Send data through the serial port for debugging
        fctU1Tx_string(strU2Tx,sizeU2Tx);
        // Increment the input channel
        if (sel < 5)
            sel++;
        else sel =0;
        DELAY(10);
        //channel =0;
        
        if(transmitNext == 1){
			/* Send a new packet. Create the packet using
             * data structure and the SID and EID.*/ 
			data[7] = 0; // don't needed
			data[6] = 0; // don't needed
			data[5] = 0; // don't needed
			data[4] = 0; // don't needed
			ECANCreateEIDPacket(data,TXSID1,TXEID1,ecanTxMsgBuffer); // Create CAN packet
			transmitNext = 0;
		}
        
		/* Wait for a random period of time and then send the message. This code
         * example does not check if the message was aborted but that could be 
         * checked here. Note that if the message was aborted the TBIF flag will
         * not be set and you will not get the associated event interrupt. */
		ECAN1SendPacket(); // send can packet
	    if(data[0]==0xaa){
            DELAY(6000);
            LATAbits.LATA7 = 0;
        }
      
}

void Read_Batterie_Tempreture(void){
    //Read data from adc channel "channel_temp"
    AdcValue=readADC(channel_temp);    
        DELAY(10);
        /* ADC_output has 12 bits resolution
         * To send this data using the can bus, we need to put the higth 8 bits in data[1] and the low 4 bits in data[2]
         * data[0] is the id of the data. if tempreture is more then 50°C then id = 0xAA else id =[0xDF, 0xDE]
         */
        data[1]=AdcValue>>4;    
        data[2]=AdcValue && 0x00F;
        if(((AdcValue/4095)*3300)>50)
            data[0]=0xAA;
        else
            data[0]=0xdf - (channel_temp-1);
        sizeU2Tx=sprintf(strU2Tx, "AdcValue = %d \r\n",AdcValue);
        fctU1Tx_string(strU2Tx,sizeU2Tx);
        
        //increment adc input channel
        if (channel_temp < 2)
            channel_temp++;
        else channel_temp =1;
        DELAY(10);
        //channel =0;
        
        if(transmitNext == 1){
			/* Send a new packet. Create the packet using
             * data structure and the SID and EID.*/ 
			data[7] = 0; // don't needed
			data[6] = 0; // don't needed
			data[5] = 0; // don't needed
			data[4] = 0; // don't needed
			ECANCreateEIDPacket(data,TXSID1,TXEID1,ecanTxMsgBuffer); // Create CAN packet
			transmitNext = 0;
		}
        
		/* Wait for a random period of time and then send the message. This code
         * example does not check if the message was aborted but that could be 
         * checked here. Note that if the message was aborted the TBIF flag will
         * not be set and you will not get the associated event interrupt. */
	
		ECAN1SendPacket();
	    if(data[0]==0xaa){
            DELAY(6000);
            LATAbits.LATA7 = 0;
        }
}
void Read_Current(void){
        AdcValue=readADC(channel_current);
        DELAY(10);
        
        /* ADC_output has 12 bits resolution
         * To send this data using the can bus, we need to put the higth 8 bits in data[1] and the low 4 bits in data[2]
         * data[0] is the id of the data. id =[0xEF, 0xEE]
         */
        data[1]=AdcValue>>4;
        data[2]=AdcValue && 0x00F;
        data[0]=0xef - (channel_current-3);
        sizeU2Tx=sprintf(strU2Tx, "AdcValue = %d \r\n",AdcValue);
        fctU1Tx_string(strU2Tx,sizeU2Tx);
        if (channel_current < 4)
            channel_current++;
        else channel_current =3;
        DELAY(10);
        //channel =0;
        
        if(transmitNext == 1){
			/* Send a new packet. Create the packet using
             * data structure and the SID and EID.*/ 
			data[7] = 0; // don't needed
			data[6] = 0; // don't needed
			data[5] = 0; // don't needed
			data[4] = 0; // don't needed
			ECANCreateEIDPacket(data,TXSID1,TXEID1,ecanTxMsgBuffer); // Create CAN packet
			transmitNext = 0;
		}
        
		/* Wait for a random period of time and then send the message. This code
         * example does not check if the message was aborted but that could be 
         * checked here. Note that if the message was aborted the TBIF flag will
         * not be set and you will not get the associated event interrupt. */
	
		ECAN1SendPacket();
				
}


/**********mux select function ************/
/* @int sel: in select channel from 0 to 8 as we have mux 8 to 1
 * LATCbits.muxSEL1 = sel(0)
 * LATCbits.muxSEL2 = sel(1)
 * LATCbits.muxSEL3 = sel(2)
*/
void mux_Select(int sel){
   
    LATCbits.muxSEL1= sel && 001;  
    LATCbits.muxSEL2=(sel && 010)>>1;
    LATCbits.muxSEL3=(sel && 100)>>2;

     }