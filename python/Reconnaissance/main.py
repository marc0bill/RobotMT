import Reconnaissance
import serial
import sys

	
def main():

	#Configuration du port série :
	S = serial.Serial()			
	S.baudrate = 9600
	S.timeout = 0
	S.port = "/dev/ttyAMA0"

	try:
		#On essaye d'ouvir le port série :
		S.open()
	except serial.SerialException as e:
		# Le port serie ne s'ouvre pas
 		sys.stderr.write("Impossible d'ouvrir le port serie %r: %s\n" % (s.port, e))
 		sys.exit(1)

 	# On lance l'algorithme de reconnaissance d'image
 	Reconnaissance(1)
 	