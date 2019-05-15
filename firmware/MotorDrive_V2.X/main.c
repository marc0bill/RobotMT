/*
 * File:   main.c
 * Author: g15016154
 *
 * Created on 15 mai 2019, 10:53
 */


#include "xc.h"

/***********************************************************************
				CONFIGURATION DU PIC - Repris de la V1
*/
_FOSCSEL(FNOSC_PRIPLL); // Primary Oscillator (XT, HS, EC) w/ PLL
_FOSC(FCKSM_CSECMD & OSCIOFNC_OFF  & POSCMD_XT);
    //FCKSM_CSECMD  Clock switching is enabled, Fail-Safe Clock Monitor is disabled
    //OSCIOFNC_OFF  OSC2 pin has clock out function
    //POSCMD_XT     XT Oscillator Mode
_FWDT(FWDTEN_OFF);
    // FWDTEN_OFF   Watchdog timer enabled/disabled by user software
//Configuration pin I2C
_FPOR(ALTI2C_ON)

#include "main.h"
#include "pwm.h"

int main(void) {
    
    init_PWM1();
    
    
    return 0;
}
