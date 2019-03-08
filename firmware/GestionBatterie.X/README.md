# Gestion Batterie

		Readme File for Code :
              RobotMT - ADC Conversion 
             ----------------------------------------

This file contains the following sections:
1. Code Description
3. Suggested imporovements



## Code Description:
In this example, ADC is set up to convert AN0 through AN5 using CH0 S/H and ADC is operating in 12-Bits mode.
A trigger source can be chosen from the PWM outputs, Analog Comparators, timers, external fault pins, PWM fault and
current limit inputs, or through software. This code sets up the Adc conversion to be triggered
by Timer 3 (16 Bits). The input clock to the Timer module is Tcy = 65536 / Fcy = 0.83s.
Fcy = Fosc/2= 20 MHz 


void Adc_init(void);
ADC CH0 is set-up to covert AN0 through AN5 in 12-bit mode. ADC is configured to next sample data immediately after the conversion.

void T3_init(void);
Timer3 period match to trigger ADC so it will trigger ADC at every 0.83Sec ( a Watchdog Timer can be enabled to push it to 7Sec by setting the values of WDTPOST and WDTPRE bits)

void _T3Interrupt();
We select from AN0 through AN5 for CH0 by incrementing the value of idAN which designs the selected Analog input

void _ADC1Interrupt();
After that ADC conversion cycle is completed we get the conversion result and clear ADC Interrupt Flag.


## Suggested imporovements:
-------------------------
### ADC Conversion in Sleep mode: 
Start of conversion is issued in the background loop and device enters sleep mode immediately after that. 

When the ADC conversion is completed in sleep mode, it wakes up the device and enters ADC ISR.

Device enters the ADC ISR after waking up from sleep mode. ADC result is read in the ISR.
