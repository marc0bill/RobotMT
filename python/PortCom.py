import numpy as np
import serial
import datetime
import time

import matplotlib.pyplot as plt
from IPython import display

def whatTime():
	dt = datetime.datetime.now()
	return dt.hour*3600+60*dt.minute+dt.second+dt.microsecond*1e-6
#
def findPort(port=None, baudrate = 9600, timeout = 0.1, Requet = "V1R?", portmax = 30,Com_Off=True):
	ser = serial.Serial()
	ser.baudrate = baudrate
	ser.setWriteTimeout(timeout)
	ser.setTimeout(timeout)
	ser.port = 0

	if port==None:
		while True:
			try:
				ser.open()
				String = readInfo(ser,Requet,SizeMax=10)
				if(String[0:3]==Requet[0:3]):
					print "Connected to %s with Good motor card answer" % ser.port
					break
			except:
				pass		    
			ser.close()    
			ser.port+=1
			if ser.port > portmax:
				print "No port found"
				break
	else:
		ser.port = port
		try:
			ser.open()
			print "Connected to %s with " % ser.port
		except:
			print "No port found"
			pass
		if Com_Off:
			ser.write("Com_Off\n")
	ser.flushInput()
	ser.flushOutput()
	return ser
#
def readInfo(ser,Requet,SizeMax=50):
	StrVal=""
	i=0
	String=Requet+" \n"
	ser.write(String)
	actualByte=""
	actualByte=ser.read()
	while actualByte != "\n" :
		StrVal = StrVal+actualByte
		i=i+1
		if(i>=SizeMax):
			print "erreur port com : fin de mot introuvable"
			break
		actualByte=ser.read()
	return StrVal
#	
def readFloat(ser,Requet,nbTest=5):
	for j in range(nbTest):
		String = readInfo(ser,Requet)
		if(String[0:3]==Requet[0:3]):
			return float(String[4:])
	return float('nan')
#

def plotXY(ser,tpsmax, dt=0.05, nbTest=5):
	x_c = list()
	y_c = list()
	x_r = list()
	y_r = list()
	for i in range(int(tpsmax/dt)):
		x_c.append(readFloat(ser,"XrC?",nbTest=nbTest))
		y_c.append(readFloat(ser,"YrC?",nbTest=nbTest))
		x_r.append(readFloat(ser,"XrR?",nbTest=nbTest))
		y_r.append(readFloat(ser,"YrR?",nbTest=nbTest))
		time.sleep(dt)
	return x_c,y_c,x_r,y_r
	
def plotInfoTime(ser,Requet, tpsmax, tps=list(), y_p=list(), dt=0.05, nbTest=5, TracePlot=True):
	tpsInit=whatTime()
	try :
		tpsBefore = tps[-1]
	except:
		tpsBefore = 0
	for i in range(int(tpsmax/dt)):
		y_p.append(readFloat(ser,Requet,nbTest=nbTest))
		tpsNow=whatTime()-tpsInit + tpsBefore
		tps.append(tpsNow)
		time.sleep(dt)
	if TracePlot:
		plt.scatter(tps,y_p)
		display.clear_output(wait=True)
		display.display(plt.gcf())
	return tps,y_p
	
	
def plotInfoTimeContinu(ser, tpsmax, tps=list(), y_p=list(), dt=0.05, nbTest=5, TracePlot=True):
	tpsInit=whatTime()
	try :
		tpsBefore = tps[-1]
	except:
		tpsBefore = 0
	for i in range(int(tpsmax/dt)):
		y_p.append(float(readInfo()))
		tpsNow=whatTime()-tpsInit + tpsBefore
		tps.append(tpsNow)
		time.sleep(dt)
	if TracePlot:
		plt.scatter(tps,y_p)
		display.clear_output(wait=True)
		display.display(plt.gcf())
	return tps,y_p