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
	time.sleep(0.001)
	GPIO.output(18, GPIO.LOW) # Read Mode
	# Handle the read.
	res = [map(ord, port.read())[0]]
	while port.inWaiting() > 0:
		res.append(map(ord, port.read())[0])

	if len(res) == 0 or res[0] != 0xFF or res[1] != 0xFF:
	  raise ValueError, "Bad Header! ('%s')" % str(res)
	
	if _Checksum(res[2:-1]) != res[-1]:
	  raise ValueError, "Checksum %s should be %s" % (_Checksum(res[2:-1]),res[-1])
	  
	id_Servo_read, length = res[2:4]
	if id_Servo_read != id_Servo:
	  raise ValueError, "Bad id_Servo! ('%s')" % str(res)
	parameters = res[5:-1]
	return parameters

port = serial.Serial("/dev/ttyAMA0", baudrate=57600, bytesize=8, parity='N', timeout=3.0)

#Configuration des GPIO
GPIO.setmode(GPIO.BCM)
GPIO.setup(18, GPIO.OUT)

id_Servo = 0x01
parameters=ServoRead(id_Servo, 0x24, 2)# Read Present Position
print "id:",id_Servo, parameters[0],parameters[1]


#return Response(map(ord, res)).Verify()
