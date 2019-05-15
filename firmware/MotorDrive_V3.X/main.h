

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded.  


#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

#ifdef __dsPIC33FJ128MC802__
#include <p33fj128mc802.h>
#endif
#ifdef __dsPIC33FJ128MC804__
#include <p33fj128mc804.h>
#endif

#include <libpic30.h>

#define FQUARTZ     4000000	// 4 MHz
#define FOSC        (FQUARTZ/(2*2))*80	//(FQUARTZ/(N1*N2))*M
#define FCY         FOSC/2

