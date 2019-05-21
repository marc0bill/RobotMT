
#Exemple


import serial

# #Configuration du port série :


# S = serial.Serial("/dev/ttyS0",9600)
# data='VtsM 50 50'
# S.write(data.encode('ascii'))
# receive=S.readline(len(data))
# print(receive.decode("utf-8"))
# sleep(1)
# data='Stop'
# S.write(data.encode('ascii'))
# receive=S.readline(len(data))
# print(receive.decode("utf-8"))


# S.close()

def write(serial, data):
	S.write(date.encode('ascii'))

def read(serial):
	receive = S.readline(20)
	return receive.decode("utf-8")


