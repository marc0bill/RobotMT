# FirmwareGestionAlim v0.2
# Presentation

The software proposed here allows to:
* Monitor the voltage of the 6 cells of the LiPo batteries
* Monitor the temperature of the two LiPo batteries
* Monitor power consumption for different power levels
* Communicate with the main calculator (Raspberry pi) through the CAN bus

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
