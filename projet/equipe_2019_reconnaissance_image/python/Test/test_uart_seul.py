import serial
from time import sleep

BAUDRATE = 57600
NOMBRE_DE_PASSE = 3
vitesse = 200

#Configuration du port série :
print("Configuration du port serie...")
S = serial.Serial("/dev/ttyS0",BAUDRATE)


for i in range(5):
	data="VtsM 200 200\n"
	print("Envoie de la commande : ", data)
	S.write(data.encode('ascii'))
	#sleep(1)
	#receive=S.readline(len(data))
	#print("Reception : ", receive.decode("utf-8"))
	sleep(1)
data="VtsM 0 0"


for k in range(NOMBRE_DE_PASSE):
	data="VtsM %f %f" (vitesse, vitesse)
	print("Envoie de la commande : ", data)
	S.write(data.encode('ascii'))
	#receive=S.readline(len(data))
	#print(receive.decode("utf-8"))
	sleep(1)
data="VtsM 0 0"
print("Envoie de la commande : ", data)
S.write(data.encode('ascii'))
#receive=S.readline(len(data))
#print(receive.decode("utf-8"))

S.close()
