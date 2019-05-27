import serial

#Configuration du port série:
S=serial.Serial("/dev/ttyS0")

data='Hello'
print("Données envoyées",data)
S.write(data.encode('ascii'))
receive=S.readline(len(data))
print("Données reçues:",reveive.decode("utf-8"))
S.close()
