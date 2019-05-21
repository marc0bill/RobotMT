
import serial
import sys

	
#On essaie Mardi

#Configuration du port série :
S = serial.Serial("/dev/ttyS0",9600)			
	
#On essaye d'ouvir le port série, si on ne peut pas l'ouvrir on renvoie un message.
	
#try:
#	S.open()
#except serial.SerialException as e:
	
#	sys.stderr.write("Impossible d'ouvrir le port serie %r: %s\n" % (s.port, e))
# 	sys.exit(1)

data='Hello'
S.write(data.encode('ascii'))
receive=S.readline(len(data))
print(receive.decode("utf-8"))
S.close()
