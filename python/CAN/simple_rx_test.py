
#!/usr/bin/python3
#
# simple_rx_test.py
# 
# This is simple CAN receive python program. All messages received are printed out on screen.
# For use with PiCAN boards on the Raspberry Pi
# http://skpang.co.uk/catalog/pican2-canbus-board-for-raspberry-pi-2-p-1475.html
#
# Make sure Python-CAN is installed first http://skpang.co.uk/blog/archives/1220
#
# 01-02-16 SK Pang
#
#
#

import can
import time
import os

#define	AN0	FF
#define	AN1	FE
#define	AN2	FD
#define	AN3	FC
#define	AN4	FB
#define	AN5	FA
#define	AN6	F9
#define	AN7	F8

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
		print('{0:x} '.format(id) +'	'+ '{}'.format(d) + 'mv')
	
except KeyboardInterrupt:
	#Catch keyboard interrupt
	os.system("sudo /sbin/ip link set can0 down")
	print('\n\rKeyboard interrtupt')	
