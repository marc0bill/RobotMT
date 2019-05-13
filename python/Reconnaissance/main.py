import Reconnaissance
import serial

	
def main():

	#Configuration du port série :
	S = serial.Serial()			
	S.baudrate = 9600
	S.timeout = 0
	S.port = "/dev/ttyAMA0"

	#On essaye d'ouvir le port série :
	
