
#!/usr/bin/python3
#
# simple_rx_test.py
# 
# This is CAN receive python program.
# For use with CAN SPI CLICK boards on the Raspberry Pi
#
# Make sure Python-CAN is installed first
#
# 03-05-19 MASSOURI Abdelfattah
#
#
#

import can
import time
import os

BATT_22V=0xFF;
BATT_18V=0xFE;
BATT_14V=0xFD;
BATT_11V=0xFC;
BATT_7V=0xFB;
BATT_3V=0xFA;
CURRENT_12V=0xEE;
CURRENT_5V=0xEE;
TEMP_BATT1=0xDF;
TEMP_BATT2=0xDE;
ALERT=0xAA;



print('\n\rCAN Rx test')
print('Bring up CAN0....')
os.system("sudo /sbin/ip link set can0 up type can bitrate 500000")
time.sleep(0.1)	

try:
	bus = can.interface.Bus(channel='can0', bustype='socketcan_native')
except OSError:
	print('Cannot find PiCAN board.')
	exit()
	
print('Ready')

try:
	while True:
		message = bus.recv()	# Wait until a message is received.
		
		c = '{0:f} {1:x} {2:x} '.format(message.timestamp, message.arbitration_id, message.dlc)
		s=''
#		for i in range(message.dlc ):
#			s +=  '{0:x} '.format(message.data[2])	#i
			
#		print(' {}'.format(c+s))
		id = (message.data[0])
		d = (((message.data[2] <<4) + message.data[3])/4095)*3300
#		s +=  '{0:x} '.format(message.data[2]) 
#		print('{0:x} '.format(id) +'	'+ '{%.3f}'.format(d) + 'mv')


		if id == BATT_22V:
			print('La tension de la cellule 6 est' +'    '+ '{0:3f}'.format(d*0.007) + 'V')
		elif id == BATT_18V:
			print('La tension de la cellule 5 est' +'    '+ '{0:3f}'.format(d*0.007) + 'V')
		elif id == BATT_14V:
			print('La tension de la cellule 4 est' +'    '+ '{0:3f}'.format(d*0.007) + 'V')
		elif id == BATT_11V:
			print('La tension de la cellule 3 est' +'    '+ '{0:3f}'.format(d*0.007) + 'V')
		elif id == BATT_7V:
			print('La tension de la cellule 2 est' +'    '+ '{0:3f}'.format(d*0.007) +  'V')
		elif id == BATT_3V:
			print('La tension de la cellule 1 est' +'    '+ '{0:3f}'.format(d*0.007) + 'V')
		elif id == CURRENT_12V:
			print('La consommation en courant pour la tension 12V est' +'    '+ '{0:3f}'.format(d*1.51) + 'mA')
		elif id == CURRENT_5V:
			print('La consommation en courant pour la tension 5V est' +'    '+ '{0:3f}'.format(d*1.51) + 'mA')
		elif id == TEMP_BATT1:
			print('La température de la batterie 1 est' +'    '+ '{0:2f}'.format(d/10) + ' °C')
		elif id == TEMP_BATT2:
			print('La température de la batterie 2 est' +'    '+ '{0:2f}'.format(d/10) + ' °C')
		elif id == ALERT:
			print('Niveau des batteries critique')
			print('systeme shutdown now')
			time.sleep(1)
			os.system("sudo shutdown -h now")
		else:
			print(' ')

except KeyboardInterrupt:
	#Catch keyboard interrupt
	os.system("sudo /sbin/ip link set can0 down")
	print('\n\rKeyboard interrtupt')	

