
import serial
import sys

	
#On essaie Mardi

#Configuration du port série :
S = serial.Serial("dev/ttyAM0",9600)			
	
#On essaye d'ouvir le port série, si on ne peut pas l'ouvrir on renvoie un message.
	
try:
	S.open()
except serial.SerialException as e:
	
	sys.stderr.write("Impossible d'ouvrir le port serie %r: %s\n" % (s.port, e))
 	sys.exit(1)

while True:
	receive=ser.read()
	data="Hello"
	ser.write(Hello)
	print(receive)
