import time
import serial
import sys
import math
from enum import Enum 

WRITE_DELAY = 0.005
READ_DELAY = 0.005
RETURN_LEN = 5

class CommandError(Enum):
	def __str__(self):
		return str(self.value)

	ERROR_INVALID_PORT 		= 1
	ERROR_INVALID_PIN 		= 2
	ERROR_INVALID_STATE 	= 3
	ERROR_SKIP				= 4

# https://www.safaribooksonline.com/library/view/python-cookbook-2nd/0596007973/ch04s21.html
def printf(format, *args):
	sys.stdout.write(format % args)

def format(format, *args):
	return (format % args)


def primePipe():
	out = ''
	ser.write("-".encode("ascii"))
	time.sleep(READ_DELAY)
	while ser.inWaiting() > 0:
		out += ser.read(1).decode('ascii')
	printf("i go `%s`\n", out)
	if("f" in out):
		printf("primed\n")
		return
	else:
		ser.reset_input_buffer()
		primePipe()

def swrite(str, check: 1):
	out = ''
	time.sleep(WRITE_DELAY)
	ser.write(str.encode("ascii"))
	if(check == 1):
		time.sleep(READ_DELAY)
		while ser.inWaiting() > 0:
			out += ser.read(1).decode('ascii')
		# printf("after write `%s` \n", out)
		if(str.replace(" ", "") in out):
			return 1
		else:
			return 0
	else:
		return 1

def ks(pin):
	out = ''
	if(swrite("ks ", 1) == 1):
		swrite(format("%d ", pin), 0)
		time.sleep(READ_DELAY)
		# gets the output confirmation
		out = ser.read(4).decode('ascii')
		# gets the output result and \r\n
		out = ser.readline().decode("ascii").strip()
		printf("the ret val was `%s`", out);
		
		if("bye" in out):
			return 1
		else:
			return 0
	else:
		return 0			

def dw(port, pin, state):
	# `p 00 x `
	# p  is port, lowercase char
	# 00 is pin, single int
	# x  is value, 0 or 1
	# length is 7, validation is 4
	out = ''
	if(swrite("dw ", 1) == 1):
		swrite(format("%c ", port), 0)
		swrite(format("%02d ", pin), 0)
		swrite(format("%d ", state), 0)

		time.sleep(READ_DELAY)
		# gets the output confirmation
		out = ser.read(4).decode('ascii')
		# gets the output result and \r\n
		out = ser.readline().decode("ascii").strip()
		printf("the ret val was `%s`", out);


def dr(port, pin):
	# `p 00 `
	# p  is port, lowercase char
	# 00 is pin, single int
	# length is 5, validation is 3
	out = ''
	if(swrite("dr ", 1) == 1):
		swrite(format("%c ", port), 0)
		swrite(format("%02d ", pin), 0)

		time.sleep(READ_DELAY)
		# gets the output confirmation
		out = ser.read(3).decode('ascii')
		# gets the output result and \r\n
		out = ser.readline().decode("ascii").strip()
		printf("the ret val was `%s`", out);

		if("ok" in out):
			return 1
		else:
			return 0
	else:
		return 0
	
def ar(channel):
	# `00 `
	# 00 is channel, single int
	# length is 3, validation is 2
	out = ''
	time.sleep(WRITE_DELAY)
	if(swrite("ar ", 1) == 1):
		swrite(format("%02d ", channel), 0)

		time.sleep(READ_DELAY)
		# gets the output confirmation
		out = ser.read(2).decode('ascii')
		# gets the output result and \r\n
		out = ser.readline().decode("ascii").strip()
		# printf("the ret val was `%s`", out);
		fval  =  float(out.split("-")[-1]);
		# printf("\nval `%.3f`\n", fval);

		return fval
	else:
		return 0

#def enDeployment():
	# # deployment power enable
	# dw('b',9,1)
	# time.sleep(READ_DELAY)
	
	# dw('e',11,1)
	# time.sleep(500)
	# dw('e',11,0)
	# #if deployment 1 not sensed then try deployment #2
	# 	#dw('e',12,1)
	# 	#time.sleep(500)
	# 	#dw('e',12,0)
	# 	#if deployment 2not sensed return 0
	# 		# return 0
	# dw('b',9,0)
	# return 1

def enPiPwr(pi):
	# check if 5V power is on
	if check5V() < 3:
		# turn on 5V
		if turnOn5V() == 0:
			return 0

	# enable Pi 'pi' pin
	if pi==1 :
		dw('d',11,1)
	else:
		dw('d',12,1)
	return 1

def check5V():
	time.sleep(1000)
	factor = 1/11
	# WTC ADC Channel 3  = 5V rail
	val = ar('03')/factor
	return val

def turnOn5V():
	#try turning on rail 1
	time.sleep(READ_DELAY)
	dw('a','12',1)

	if check5V() > 3:
		return 1;
	else:
		dw('a','12',0)
		dw('h','2',1)
		if check5V() > 3:
			return 1;
		else:
			dw('a','1',0)
			return 0;

def checkWTC_3V():
	succeed = True
	target = 3.3
	tolerance = 0.20

	printf("\n3.3 Rail and Regulator Voltage Test Begin\n")

	# 	Name		:	ADC Name	:	ADC	:	Factor
	#	3_3V_Rail 	:	5X_Out_1	:	12	:	5
	#	3.3Raw-1	:	5X_Out_2	:	11	:	5
	#	3.3Raw-1	:	5X_Out_3	:	10	:	5

	rail = ar(12) * 5
	ps1 = ar(11) * 5
	ps2 = ar(10) * 5

	# printf("3_3V_Rail is %4.3f\n", rail)
	if(math.isclose(rail, target, rel_tol=target*tolerance)):
		printf("\tPASS:\t")
		succeed = succeed & True;
	else:
		printf("\tFAIL:\t")
		succeed = False;
	printf("3_3V_Rail is %4.3f\n", rail)

	if(math.isclose(ps1, target, rel_tol=target*tolerance)):
		printf("\tPASS:\t")
		succeed = succeed & True;
	else:
		printf("\tFAIL:\t")
		succeed = False;
	printf("3.3Raw-1 is %4.3f\n", ps1)

	if(math.isclose(ps2, target, rel_tol=target*tolerance)):
		printf("\tPASS:\t")
		succeed = succeed & True;
	else:
		printf("\tFAIL:\t")
		succeed = False;
	printf("3.3Raw-1 is %4.3f\n", ps2)

	printf("3.3 Rail and Regulator Voltage Test End:\t %s\n\n", succeed)

	return succeed


def checkWTC_3I():
	printf("\n3.3 Rail and Regulator Current Test Begin\n")

	# 	Name		:	ADC Name	:	ADC	:	Factor
	#	Imon_3.3-2 	:	Imon_3.3-2	:	8	:	1
	#	Imon_3.3-1	:	Imon_3.3-1	:	9	:	1

	gain = 20
	r = .1

	reg1 = ar(9) * gain * r
	reg2 = ar(8) * gain * r

	printf("\tImon_3.3-1 is %4.3f\n", reg1)
	printf("\tImon_3.3-2 is %4.3f\n", reg2)

	printf("\t\tI_Total is ~%4.3f\n", reg1+reg2)

	printf("3.3 Rail and Regulator Current Test End\n\n")
	
	return True

## for surfsat
#EnduroSat commands
cmd1 		= "ES+W22003303"
cmd1R		= "Okay and .... 3303" #fix command
cmd2A 		= "ES+W22003363"
cmd2B 		= "a" * 12
cmd2C		= cmd1


## for surfsat
def tt(channel):

	out = ''
	if(swrite("tt ", 1) == 1):
		swrite(cmd1, 0)

		time.sleep(READ_DELAY)
		# gets the output confirmation
		out = ser.read(2).decode('ascii')
		# gets the output result and \r\n
		out = ser.readline().decode("ascii").strip()
		printf("the ret val was `%s`", out);

		if("ok" in out):
			return 1
		else:
			return 0
	else:
		return 0

# configure the serial connection
ser = serial.Serial(
	port='COM4',
	baudrate=115200,
	parity=serial.PARITY_NONE,
	stopbits=serial.STOPBITS_ONE,
	bytesize=serial.EIGHTBITS
)

ser.isOpen()

print('Enter your commands below.\r\nInsert "exit" to leave the application.')

retval = 0

# main loop
while 1:
	status = checkWTC_3V()
	status = checkWTC_3I()


	exit()

	# get keyboard input
	# cmd = input("Enter command or 'exit':")
	#cmd = "dw d 11 1 " #raw_input(">> ")
	commandline = sys.stdin.readline()

	# remove trailing/leading spaces
	#commandline = commandline.strip()
	commandline = commandline.replace(" ", "")

	# dw, dr, aw, ar, tt
	cmd = commandline[0:2]
	
	#dw	
	if cmd == 'dw':
		# port a, b, c, d
		port = commandline[2:3]
		# pin 0<=x<=15
		pin = commandline[3:5]
		# state 0 or 1
		state = commandline[5:6]
		dw(port, int(pin), int(state))
	#dr	
	if cmd == 'dr':
		# port a, b, c, d
		port = commandline[2:3]
		# pin 0<=x<=15
		pin = commandline[3:5]
		dr(port, int(pin))
	# #aw	
	# if cmd == 'aw':
	# 	# channel  00 <= XX <= 31
	# 	channel = commandline[2:4]
	# 	aw(channel)
	#ar	
	if cmd == 'ar':
		# channel 00 <= XX <= 31
		channel = commandline[2:4]
		ar(int(channel))

	if cmd == 'ks':
		# channel 00 <= XX <= 31
		pin = commandline[2:3]
		ks(int(pin))

	# Python 3 users
	# input = input(">> ")
	if cmd == 'exit':
		ser.close()
		exit()
	else:
		# send the character to the device
		# ar(32)
		# time.sleep(1)
		# retval = dw('d', 11, 1)
		# retval = dr('d', 11)
		# time.sleep(1)
		# retval = dw('d', 11, 0)
		# retval = dr('d', 11)
		# time.sleep(1)
		# retval = dw('d', 11, 1)

		out = ''
		time.sleep(1)
		while ser.inWaiting() > 0:
			out += ser.read(1).decode('ascii')

		if out != '':
			print(out)
