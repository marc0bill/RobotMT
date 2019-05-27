import serial
from time import sleep

BAUDRATE = 57600
NOMBRE_DE_PASSE = 3
vitesse = 200

#Configuration du port série :
print("Configuration du port serie...")
S = serial.Serial("/dev/ttyS0",baudrate)

while 1::
	data="VtsM %f %f" (vitesse, vitesse)
	print("Envoie de la commande : ", data)
	S.write(data.encode('ascii'))
	#receive=S.readline(len(data))
	#print(receive.decode("utf-8"))
	sleep(1)

S.close()
