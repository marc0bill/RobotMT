
#Exemple


import serial



def write(portSerie, data):
	print("Envoie de ", data)
	portSerie.write(data.encode('ascii'))

def read(portSerie):
	receive = portSerie.readline(20)
	return receive.decode("utf-8")


