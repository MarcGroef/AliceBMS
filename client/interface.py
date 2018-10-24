import serial
import time
import io
import os
import re

ser = serial.Serial('/dev/ttyUSB0', baudrate = 9600, timeout = 1)
sio = io.TextIOWrapper(io.BufferedRWPair(ser, ser))
time.sleep(1)
print "used port:", ser.name
ser.write('start')


def shutdown():
	print 'shutdown!'
	#os.system('sudo shutdown -fP 0')


while True:
	
		x = sio.readline().strip('\n').strip('\n').strip('\r') #
		if x != '':
			v1, v2, sig = re.findall(r"[-+]?\d*\.\d+|\d+", x)
			print v1, v2, sig
			if int(sig) == 1:
				shutdown()
			#val = int(x)
			#print val
			#if val == 1:
				#shutdown()
		
