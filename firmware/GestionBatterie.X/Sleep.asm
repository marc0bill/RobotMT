;******************************************************************************
; TITLE: 
; AUTHOR:
; DESCRIPTION:   CLRWDT To prevent a WDT Time-out Reset
		/* If  the WDT times out during Sleep or Idle modes, the device will wake-up and continue code execution
		from where the PWRSAV instruction was executed.*/ 
;******************************************************************************
#include <stdio.h>
#include <stdlib.h> // stdlib.h is included for the rand() and srand() function call
#ifdef __dsPIC33FJ128MC804__
#include <p33fj128mc804.h>
#endif
;******************************************************************************
;  DEFINITION DE SYMBOLES ET MACRO
;******************************************************************************

;******************************************************************************
; PROGRAMME
;******************************************************************************

.ifdef __dsPIC33F
.include "p33fj128mc804.inc"
.endif

	.global _ASleep

_ASleep:
	bclr	AD1CON1,#1
	pwrsav 	#0
	nop
	nop
	nop
	nop
	return
