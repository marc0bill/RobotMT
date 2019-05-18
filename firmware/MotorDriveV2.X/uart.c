#include "uart.h"
#include "main.h"
#include "pwm.h"
#include <ctype.h>
#include <stdio.h>            /* for printf */ 
#include <string.h>


void initUART1() {
	// Configuration of UART 
	U1BRG = ((FCY / 9600) / 16) - 1;	// Initialization of baud rate, baudrate = 9600
	//UxMODE: UARTx Mode Register
	U1MODEbits.UARTEN = 1; // UARTx is enabled, UARTx pins are controlled by UARTx as defined by 
						   // the UEN <1:0> and UTXEN control bits
	U1MODEbits.USIDL = 1; // Stop in Idle Mode bit : 1 =  Discontinue operation when the device enters Idle mode
						  //						 0 = Continue operation in Idle mode
	U1MODEbits.IREN = 0; // 0 = IrDA encoder and decoder are disabled, 1 = IrDA encoder and decoder are enabled
	U1MODEbits.RTSMD = 1; // Mode Selection for UxRTS Pin bit , 1 = UxRTS is in Simplex mode
						 // 0 = UxRTS is in Flow Control mode
						// NON SUR!!!! A changer si erreur
	U1MODEbits.UEN = 00; // UxTX and UxRX pins are enabled and used; UxCTS, UxRTS and BCLKx pins are controlled by
	                     // port latches. TX,RX enabled, CTS,RTS not
	U1MODEbits.WAKE = 0;	// No Wake up (since we don't sleep here)
	U1MODEbits.LPBACK = 0;	// No Loop Back		//cleared by hardware upon completion
	U1MODEbits.ABAUD = 0;	// Auto-Baud Enable bit : 1 = Enable baud rate measurement on the next character. Requires reception of a Sync field (55h);
							// cleared in hardware upon completion.
	U1MODEbits.URXINV = 0; // Receive Polarity Inversion bit,1 = UxRX Idle state is ‘0’, 0 = UxRX Idle state is ‘1’,
							// Aucune idée du pourquoi
	U1MODEbits.BRGH = 0;	//High Baud Rate Select bit, 1 = High speed
							// 0 = Low speed, Nous avons 16 clocks per bit period
	U1MODEbits.PDSEL = 0;	// Parity and Data Selection bits
							// 11 = 9 - bit data, no parity
							//	10 = 8 - bit data, odd parity
							//	01 = 8 - bit data, even parity
							//	00 = 8 - bit data, no parity
	U1MODEbits.STSEL = 0;  //Stop Selection bit
							//  1 = 2 Stop bits
							// 	0 = 1 Stop bit

	// configure U1STA
	U1STAbits.UTXISEL= 10;	// Interrupt Transmission mode :
							// Interrupt generated when a character is transferred to the Transmit Shift register and the
							// transmit buffer becomes empty
	U1STAbits.UTXINV = 0;	// Transmit Polarity Inversion bit
							// 0 = UxTX Idle state is ‘0’
	U1STAbits.UTXBRK = 0;	// Sync Break transmission is disabled or completed
	U1STAbits.UTXEN = 1;	// UARTx transmitter enabled; UxTX pin is controlled by UARTx (if UARTEN = 1)

	// UTXBF: Transmit Buffer Full Status bit (read-only), DOIT ON LE MODIFIER ??
	U1STAbits.URXISEL = 00;	// Interrupt Reception mode : Interrupt flag bit is set when a character is received


	IFS0bits.U1TXIF = 0; 	// Clear the Transmission Interrupt Flag
	
	U1STAbits.ADDEN = 0;	// Address Detect Disabled



	// Interrupts : Reception
	IPC2bits.U1RXIP = 1;	// interrupt priority 3
	IEC0bits.U1RXIE = 1; 	// Enable Recieve Interrupts 1
	IFS0bits.U1RXIF = 0; 	// Clear the Recieve Interrupt Flag
	// Interrupts : Transmission
	IPC3bits.U1TXIP = 1;	// interrupt priority 2

	FlagUart.U1Tx=0;
	IEC0bits.U1TXIE	= 1;	// // Enable Transmisssion Interrupts 1
}

// routine d'interruption sur reception UART1
void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void) {
	static char UxRx_string[UxRx_length];
	char UxRx_char;
	int i = 0;
	static int k = 0;

	IFS0bits.U1RXIF = 0;	// On dit qu'on accepte de prendre des données en interruption
	UxRx_char = U1RXREG;    // On prend un charactère de 8 bits issue de l'uart

	switch (isspace(UxRx_char))
	{
	case 0:  // Pas d'espace
		UxRx_string[i] = UxRx_char;  // On ajoute un à un les charactères pour former un "mot" qui peut être une valeur
		i++;
		break;
	default:  // un espace
		assign(UxRx_string);  // Fin d'une suite de charactère donc on peut l'envoyer afin d'appliquer l'instruction
		for (k = 0; k<UxRx_length; k++) UxRx_string[k] = 0; // nettoyage de la chaine de caractére
		i = 0;
		break;
	}
}





//routine d'interruption transmission UART1 
void __attribute__((interrupt, no_auto_psv)) _U1TXInterrupt(void)
{


	IFS0bits.U1TXIF = 0;	// acquittement
	U1TXREG = U1Tx_string[i]; // Transmit one character
	U1Tx_chaine(U1TXREG);



}






void U1Tx_chaine(char string[UxTx_length]) //Envoie une chaine de caractère en UART (taille max = UxTx_length = 20 )
{
	FlagUart.U1Tx = 1;
	if (FlagUart.U1Tx == 1) {
		IEC0bits.U1TXIE = 1;
		U1Tx_size = sprintf(U1Tx_string, string) + 1;
		FlagUart.U1Tx = 0;
	}

}
