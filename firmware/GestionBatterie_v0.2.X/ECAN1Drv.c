/**********************************************************************
* © 2008 Microchip Technology Inc.
*
* FileName:        ECAN1Drv.c
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


#include "ECAN1Drv.h"
#include "node.h"

unsigned int ECANFilterSID(int sid, unsigned long eid, int exide){
	/* This function returns the value to be stored in CxFnSID register. 
	 * SID - The Standard ID
	 * EID - The Extended ID. For Standard messages EID should be zero.
	 * EXIDE - 0 for Standard messages. 1 otherwise
	 */
	unsigned int returnVal;
	
	returnVal = sid << 5;
	if(exide == 1)
		returnVal |= 0x8;
	else
		returnVal &= 0xFFFE;
	returnVal |= (int)(eid >> 16);
	return (returnVal);
}	

unsigned int ECANFilterEID( unsigned long eid){
	/* This function will return value to be stored on CxFnEID register.
	 * EID - this is the extended ID */
	unsigned int returnVal;
	
	returnVal = (int)(eid & 0xFFFF);
	
	return(returnVal);
}	

void ECAN1DMAConfig(int txBufferOffset, int rxBufferOffset, int numOfRxBuffers){
	/* Set up DMA Channel 0 to copy data from DMA RAM to ECAN module 1. The DMA 
     * mode is Register Indirect with Post Increment. The length of each ECAN
     * message is 7 words. Additionally the Continuous mode with ping pong 
     * disabled is used. For ease of error* handling while using register 
     * indirect mode, only one TX buffer is used. */ 
	DMA0CON = 0x2000;		//direct memory acess
	DMA0PAD = (int)(&C1TXD);//transmit data Word
 	DMA0CNT = 6;			//Set Number of DMA Transfer per ECAN message to 8 words
	DMA0REQ = 0x0046;		//Assign ECAN1 Transmit event for DMA Channel
	DMA0STA = txBufferOffset; //Start Address Offset for ECAN1 Message Buffer 0x0000
   	_DMA0IE	= 0;	//Channel Interrupt Enable: Enable DMA Channel 0 Interrupt
   	_DMA0IF = 0;//DMA Channel 0 Data Transfer Complete Interrupt Flag Status bit
   	DMA0CONbits.CHEN = 1;		//Channel Enable: Enable DMA Channel
	
	/* Set up DMA Channel 1 to copy data from ECAN module 1 to DMA RAM. The 
     * Receive memory is treated like a FIFO. The ECAN module cannot 
     * differentiate between buffers when the DMA is in register indirect mode.
	 * Note the size of each recevied message is eight words. Continuous with 
     * pin pong disabled is used.*/
	DMA1CON = 0x0000;		
	DMA1PAD = (int)(&C1RXD);	
 	DMA1CNT = (numOfRxBuffers * 8) - 1;				
	DMA1REQ = 0x0022;	
	DMA1STA = rxBufferOffset; 
    _DMA1IE	= 0;	
   	_DMA1IF = 0;
   	DMA1CONbits.CHEN = 1;		
}    	



void ECAN1ClockConfig(void){
	/* ECAN_FCY and ECAN_BITRATE are defined in ECAN1Drv.h. The total time time
     * quanta per bit is 8. Refer to ECAN FRM section for more details on 
     * setting the CAN bit rate */
	C1CTRL1bits.CANCKS = 1; // Select the CAN Master Clock
	C1CFG1 = ((ECAN_FCY/16)/ECAN_BITRATE)-1;  
 	C1CFG2 = 0x0290; 	
} 
 

void ECAN1InterruptConfig(void){
	/* Only the C1 Event Interrupt is used in this code example. All the status 
	 * flags are cleared before the module is enabled */
	C1INTF = 0; // Reset all the CAN Interrupt
	_C1IF = 0;// Reset the Interrupt Flag Status register
	_C1TXIF = 0;//Ecan1 Transmit Data Request Interrupt Flag Status bit, 0=> interrupt request has not occured
	_C1RXIF = 0;//Ecan1 Receive Data Ready interrupt Flag Status bit, 0=> interrupt request has not occured 
	_C1IE = 1;//Enable the CAN1 Interrupt
	_C1TXIE = 0;//Ecan1 transmit data Request Interrupt enable bit,0=> Interrupt requestion not occured
	_C1RXIE = 0;//ECAN1 Receive Data Ready Interrupt Enable bit,0 = Interrupt request not enabled
	C1INTE = 0x00FF;// Enable all CAN interrupt sources
	C1RXFUL1 = 0;//Receive Buffer n full Bits, 0=> buffer empty
	C1RXFUL2 = 0;//Receive Buffer n Full bits, 0=> buffer empty
	C1RXOVF1 = 0;// Receive buffer n Overflow bits, 0=> no overflow condition
	C1RXOVF2 = 0;// Receive buffer  n Overflow bits, 0=>no overflow condition
}


void ECAN1TxRxBuffersConfig(void){
	/* Configure only one TX buffer and enable four DMA buffers. No need to 
     * configure  RX buffers. */
	C1CTRL1bits.WIN = 0;//don't Enable window to Access Acceptance Filter Registers
	C1TR01CONbits.TXEN0 = 1; //Configure Message buffer 0 for transmission
}


void ECAN1RxFiltersConfig(void ){
	/* Enable 2 filters. The ID are defined in node.h Note that using Register 
     * Indirect mode does not  affect the filter and masking capability. You may 
	 * not want to set up the CxBUFPNTn bits to point to FIFO. This way you can 
     * avoid the FIFO interrupts. Just point to an arbitrary RX buffer */
	
	/* In this case filters 0 and 4 are used */
	 C1CTRL1bits.WIN = 1;// Enable window to Access Acceptance Filter Registers
	 C1FEN1 = 0x11;//Filter  enabled for Identifier match with incoming message
	
	 C1RXF0SID = ECANFilterSID(SID1,EID1,1);//Configure Acceptance Filter 0 to match standard identifier		
	 C1RXF0EID = ECANFilterEID(EID1);//Configure Acceptance Filter 0 to match standard identifier		
	 	 
	 C1RXF4SID = ECANFilterSID(SID2,EID2,1);//Configure Acceptance Filter 4 to match standard identifier				
	 C1RXF4EID =ECANFilterEID(EID2);//Configure Acceptance Filter 4 to match standard identifier		
	 	 
	 C1RXM0SID = 0xFFEB;		/* Configure MASK 0 - All bits used in comparison*/
	 C1RXM0EID = 0xFFFF; /* Configure MASK 0 - All bits used in comparison*/
	 
	 C1FMSKSEL1bits.F0MSK = 0x0;	/* User MASK 0 for all filters */
	 C1FMSKSEL1bits.F4MSK = 0x0;	/* User MASK 4 for all filters, A VERIFIER */
	 
	 C1BUFPNT1bits.F0BP = 0x1;		/* Set the destination buffers to be any thing but */
	 C1BUFPNT2bits.F4BP = 0x1;		/* configured transmit buffers */
}

	

int ECAN1SendPacket(void){
	/* The TXREQ bit is set. This will make the ECAN module generate request to 
     * the DMA. Note that in Register Indirect Mode the ECAN module is not aware
     * of buffers. So setting the TXREQ bit will cause data be transferred from 
     * the location pointed by the DMA */
	 
	/* The DMA Pointer will have to be reset in case arbitration is lost. This 
     * can be done by checking the TXLARB bit in the CxTRmnCON register. The DMA
	 * Pointer is reset by disabling and enabling the DMA channel.*/
	 
	/* If the message transmission is aborted the function will return a zero.*/
	 
	C1TR01CONbits.TXREQ0 = 1;// Request Message Buffer 0 Transmission , message send request bit 1=> = Requests that a message be sent. The bit automatically clears when the message is successfully sent
	while(C1TR01CONbits.TXREQ0 == 1){
		if(C1TR01CONbits.TXLARB0 == 1){ // Message Lost Arbitration bit , 1=> message lost arbitration while being sent, 0=> message did not lose arbritration while the message was being sent 
			/* Arbitration lost. Abort the message and reset the transmit buffer
             * DMA */
	
			C1TR01CONbits.TXREQ0 = 0;// Clear when message is abort
			DMA0CONbits.CHEN = 0;// Channel Enable bit disabled
			DMA0CONbits.CHEN = 1;// Channel Enable bit enabled
			C1TR01CONbits.TXREQ0 = 1;// request message buffer 0 Transmission
		}
	}
	
	if(C1TR01CONbits.TXABT0 == 1){ //TXABT0 Message Aborted bit, 1=> message was aborted , 0 => message completed transmission successfully
		return(0);
	}
	
	return(1);			
}	


void ECAN1SetOPMode(void){
	/* Request the normal operational mode and wait  till it is set */
	C1CTRL1bits.REQOP = 0;// Rquest Operation Mode bits, 000=> Set Normal Operation Mode, utile pour savoir si on est transmission/reception/les 2
	while(C1CTRL1bits.OPMODE != 0);// Operation Mode bits is 000=> Normal Operation Mode
}


void ECANCreateSIDPacket(int * data, int sid,int * output){
	/* This function will create a standard ID packet DLC is set to 8. 
	 * data - points to the data payload
	 * SID - Standard ID value to be used. 
	 * output - points to where the packet should be stored which typically is 
     * an ECAN TX buffer */
	 
	 //output[0] = (sid << 2) & 0x1FFC;		/* SID, SRR = 0 and IDE = 0 */
	 //output[1] = 0x8;
	 //output[2] = data[0];
	 //output[3] = data[1];
	 //output[4] = data[2];
	 //output[5] = data[3];
	 //output[6] = 0;
     
     output[0] = (sid << 2) & 0x1FFC;		/* SID, SRR = 0 and IDE = 0 */
     output[1] = 0x0;//(int)(eid >> 6) & 0x0FFF;
	 output[2] = 0x8;
	 output[3] = data[0];
	 output[4] = data[1];
	 output[5] = data[2];
	 output[6] = data[3];
	 output[7] = data[4];
	 output[8] = data[5];
	 output[9] = data[6];
	 output[10] = data[7];
}  

void ECANCreateEIDPacket(int * data,int sid,long eid,int * output){
	/* This function will create a extended ID packet DLC is set to 8. 
	 * data - points to the data payload
	 * sid - standard id
	 * eid - extended id
	 * output - points to where the packet should be stored which typically is 
     * an ECAN TX buffer */
	 
	 output[0] = (sid << 2) | 0x3;		
	 output[1] = (int)(eid >> 6) & 0x0FFF;
	 output[2] = ((int)(eid & 0x3F) << 10) | 0x8;
	 output[3] = data[0];
	 output[4] = data[1];
	 output[5] = data[2];
	 output[6] = data[3];
	 output[7] = data[4];
	 output[8] = data[5];
	 output[9] = data[6];
	 output[10] = data[7];
}
                         
