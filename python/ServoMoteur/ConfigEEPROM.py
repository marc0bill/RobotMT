import serial
import time
import RPi.GPIO as GPIO

Toque_Max = [0x03,0x0E,0xFF,0x03]
Mode_MultiTurn = [0x03,0x06,0xFF,0x0F,0xFF,0x0F]
Mode_Joint = [0x03,0x06,0x00,0x00,0xFF,0x0F]
Mode_Wheel = [0x03,0x06,0x00,0x00,0x00,0x00]
MultiTurnOffset = [0x03,0x14,0x00,0x00]

led_ON = [0x03,0x19,0x01]
led_OFF = [0x03,0x19,0x00]


def makeString(id,packet):
	P = [id,len(packet)+1] + packet
	checksum= ((~sum(P)) & 0xFF)
	return [0xFF,0xFF] + P + [checksum]


port = serial.Serial("/dev/ttyAMA0", baudrate=57600, bytesize=8, parity='N', timeout=3.0)
#Configuration des GPIO
GPIO.setmode(GPIO.BCM)
GPIO.setup(18, GPIO.OUT)
GPIO.output(18, GPIO.HIGH) # Write Mode

port.write("".join(map(chr,makeString(0x01,[0x03,0x06,27,0,6,6])))) # Fixe position max bras droit
time.sleep(0.01)
port.write("".join(map(chr,makeString(0x02,[0x03,0x06,202,7,242,12]))))# Fixe position max bras gauche
time.sleep(0.01)
port.write("".join(map(chr,makeString(0x03,Mode_Wheel))))
time.sleep(0.01)
#s = makeString(id,MultuTurnOffset)
#port.write("".join(map(chr,s)))
#time.sleep(1)
port.write("".join(map(chr,makeString(0x01,led_OFF))))
time.sleep(0.01)
port.write("".join(map(chr,makeString(0x02,led_OFF))))
time.sleep(0.01)
port.write("".join(map(chr,makeString(0x03,led_OFF))))
time.sleep(0.01)
#id = 0x02
#s = makeString(id,led_ON)
#s = makeString(id,MultuTurnMode)
#s = makeString(id,MultuTurnOffset)
#s = makeString(id,led_OFF)


#id = 0x03
#s = makeString(id,led_ON)
#s = makeString(id,MultuTurnMode)
#s = makeString(id,MultuTurnOffset)
#s = makeString(id,led_OFF)