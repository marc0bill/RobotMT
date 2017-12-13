import serial
import time


def makeString(id,packet):
	P = [id,len(packet)+1] + packet
	checksum= ((~sum(P)) & 0xFF)
	return [0xFF,0xFF] + P + [checksum]


port = serial.Serial("/dev/ttyAMA0", baudrate=57600, bytesize=8, parity='N', timeout=3.0)

id = 0x03

closeL = [0x03,0x1E,0x00,0x00,0x00,0x07]

led_ON = [0x03,0x19,0x01]
led_OFF = [0x03,0x19,0x00]

turn_UP = [0x03,0x20,0xFF,0x03]
turn_DOWN = [0x03,0x20,0xFF,0x07]
turn_STOP = [0x03,0x20,0x00,0x00]

s = makeString(id,led_ON)
port.write("".join(map(chr,s)))


time.sleep(1)

s = makeString(id,turn_UP)
print s
port.write("".join(map(chr,s)))
time.sleep(1)

s = makeString(id,turn_STOP)
print s
port.write("".join(map(chr,s)))
time.sleep(1)

s = makeString(id,turn_DOWN)
print s
port.write("".join(map(chr,s)))
time.sleep(1)
s = makeString(id,turn_STOP)
print s
port.write("".join(map(chr,s)))

s = makeString(id,led_OFF)
port.write("".join(map(chr,s)))
