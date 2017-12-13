import serial
import time
import RPi.GPIO as GPIO
# The types of packets.
PING       = [0x01]
READ_DATA  = [0x02]
WRITE_DATA = [0x03]
REG_WRITE  = [0x04]
ACTION     = [0x05]
RESET      = [0x06]
SYNC_WRITE = [0x83]

led_ON = WRITE_DATA + [0x19,0x01]
led_OFF = WRITE_DATA + [0x19,0x00]

id_ServoR = 0x01
closeR = WRITE_DATA + [0x1E,0xA0,0x00,0xFF,0x00,0xFF,0x00]
openR =  WRITE_DATA + [0x1E,0x78,0x05,0xFF,0x03,0xFF,0x03]

id_ServoL = 0x02
closeL = WRITE_DATA + [0x1E,0x94,0x0C,0xFF,0x00,0xFF,0x00]
openL =  WRITE_DATA + [0x1E,0x48,0x08,0xFF,0x03,0xFF,0x03]

UP = WRITE_DATA + [0x1E,0x00,0x00,0xFF,0x03]
DOWN =  WRITE_DATA + [0x1E,0x00,0x00,0xFF,0x07]
STOP =  WRITE_DATA + [0x1E,0x00,0x00,0x00,0x00]





_ServoAdd={'Model':0, 'id':0x03, 'GlobalPos':0x1E, 'PosCur':0x24}




def _Checksum(s):
	"""Calculate the Dynamixel checksum (~(ID + length + ...)) & 0xFF."""
	return (~sum(s)) & 0xFF

def makeString(id_Servo,packet):
	P = [id_Servo,len(packet)+1] + packet
	checksum= _Checksum(P)
	return [0xFF,0xFF] + P + [checksum]

def ServoRead(id_Servo, RegAdd, nbReg):
	GPIO.output(18, GPIO.HIGH) # Write Mode
	packet = READ_DATA + [RegAdd] + [nbReg]
	s = makeString(id_Servo,packet)
	port.write("".join(map(chr,s)))
	port.flushOutput()
	time.sleep(0.0012)
	GPIO.output(18, GPIO.LOW) # Read Mode
	# Handle the read.
	res = [map(ord, port.read())[0]]
	while port.inWaiting() > 0:
		res.append(map(ord, port.read())[0])
	GPIO.output(18, GPIO.HIGH) # Write Mode
	
	if len(res) == 0 or res[0] != 0xFF or res[1] != 0xFF:
	  raise ValueError, "Bad Header! ('%s')" % str(res)
	
	if _Checksum(res[2:-1]) != res[-1]:
	  raise ValueError, "Checksum %s should be %s" % (_Checksum(res[2:-1]),res[-1])
	  
	id_Servo_read, length = res[2:4]
	if id_Servo_read != id_Servo:
	  raise ValueError, "Bad id_Servo! ('%s')" % str(res)
	parameters = res[5:-1]
	return parameters

#def ServoWrite(id_Servo, RegAdd, nbReg,packet)




port = serial.Serial("/dev/ttyAMA0", baudrate=57600, bytesize=8, parity='N', timeout=3.0)
#Configuration des GPIO
GPIO.setmode(GPIO.BCM)
GPIO.setup(18, GPIO.OUT)



#print ServoRead(id_Servo, 0x11, 1)
#print ServoRead(id_Servo, _ServoAdd['id'], 1)
#print ServoRead(id_Servo, 0x11, 1)

#closeL = [0x03,0x1E,0x00,0x00,0xFF,0x07]




# OPEN
GPIO.output(18, GPIO.HIGH) # Write Mode
port.write("".join(map(chr,makeString(id_ServoR,openR))))
time.sleep(0.01)
port.write("".join(map(chr,makeString(id_ServoL,openL))))
time.sleep(0.01)

time.sleep(1)

# CLOSE
GPIO.output(18, GPIO.HIGH) # Write Mode
port.write("".join(map(chr,makeString(id_ServoR,closeR))))
time.sleep(0.01)
port.write("".join(map(chr,makeString(id_ServoL,closeL))))
time.sleep(0.01)

time.sleep(1.5)


#print ServoRead(id_ServoR, 0x11, 1)
#time.sleep(0.01)
#print ServoRead(id_ServoL, 0x11, 1)


#UP
port.write("".join(map(chr,makeString(0x03,UP))))
time.sleep(2)
port.write("".join(map(chr,makeString(0x03,DOWN))))
time.sleep(2)
port.write("".join(map(chr,makeString(0x03,STOP))))
time.sleep(0.01)
#parameters=ServoRead(id_Servo, _ServoAdd['PosCur'], 2)
#print ServoRead(id_Servo, 0x11, 1)

port.write("".join(map(chr,makeString(id_ServoR,led_OFF))))
time.sleep(0.01)
port.write("".join(map(chr,makeString(id_ServoL,led_OFF))))
time.sleep(0.01)