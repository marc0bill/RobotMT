# FirmwareGestionAlim v0.2
**************************************************************************************************************************************
# Power Management System
# RobotMT/firmware/GestionBatterie_v0.2.X/
**************************************************************************************************************************************
* (C) COPYRIGHT 2019 POLYTECH.

  * file    : RobotMT/firmware/GestionBatterie_v0.2.X//readme.md
  * author  : Abdelfattah MASSOURI
  * version : V1.0.0
  * date    : 30-May-2019
  * brief   : Description of the project GestionBatterie_v0.2.X.

****************************************************************************************************************************************

### Project Description

This project allows to:
  - 1) Monitor the voltage of the 6 cells of the LiPo batteries
  - 2) Monitor the temperature of the two LiPo batteries
  - 3) Monitor power consumption for different power levels
  - 4) Communicate with the main calculator (Raspberry pi) through the CAN bus

______________________________________________________________________________

______________________________________________________________________________

### Directory contents

  - RobotMT/firmware/GestionBatterie_v0.2.X/main.c                        (Main program)
  - RobotMT/firmware/GestionBatterie_v0.2.X/ECAN1Drv.c                    (ECAN driver)
  - RobotMT/firmware/GestionBatterie_v0.2.X/ECAN1Drv.h                    (ECAN driver header file)
  - RobotMT/firmware/GestionBatterie_v0.2.X/adc.c                         (ADC configration)
  - RobotMT/firmware/GestionBatterie_v0.2.X/adc.h			  (ADC configration header file)
  - RobotMT/firmware/GestionBatterie_v0.2.X/init_pic.c 			  (pic initialization function)
  - RobotMT/firmware/GestionBatterie_v0.2.X/init_pic.h                    (pic initialization header file)
  - RobotMT/firmware/GestionBatterie_v0.2.X/node.h                        (CAN node configuration)
  - RobotMT/firmware/GestionBatterie_v0.2.X/uart.c			  (UART configration)
  - RobotMT/firmware/GestionBatterie_v0.2.X/uart.h                        (UART configration header file)
______________________________________________________________________________

### Hardware and Software environment 

  - This project has been used with a dsPIC33FJ128MC804.

  - dsPIC33FJ128MC804 Set-up
    - Use ADC input channel (AN0) to read batteries level.
	- Use RC6, RC7, RC8 to set mux input channel to select battery cell.
    - Use ADC input channel (AN1) to read battery 1 tempreture.
	- Use ADC input channel (AN2) to read battery 2 tempreture.
    - Use ADC input channel (AN3) to read the output voltage of the first hall effect sensor.
    - Use ADC input channel (AN4) to read the output voltage of the seconde hall effect sensor.
    - Use the eCAN module to communicate with other device such as calculator(raspberry pi)
    - Use RA7 pin to turn on/off the relay.
    
firmware dsPIC
==============

## Notice

In this project we use analog sensors. To acquire the data through these sensors, we use the ADC module of the dsPIC.
This is why we use the init_ADC function (int amask) to initialize the ADC and the readADC function (int channel) to read the data.
After reading the data, the data is processed and transmitted in the can bus to a raspberry pi card.
To use the CAN bus, functions are used for initialization, configuration of filters and functions for transmitting and receiving data.

We use the function Read_Batterie_Voltage (void) to read the levels of the different cells of the batteries and to send alerts and cut the power
where necessary.

We use the function Read_Batterie_Tempreture (void) to read battery temperature and to send alerts and cut power
where necessary.

The function Read_Current (void) is used to read the output of a hall effect sensor which controls the current consumption.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
