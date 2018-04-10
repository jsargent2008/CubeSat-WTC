import time
import serial
import sys
from enum import Enum 

WRITE_DELAY = 0.001
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

		if("ok" in out):
			return 1
		else:
			return 0
	else:
		return 0

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
	if(swrite("ar ", 1) == 1):
		swrite(format("%02d ", channel), 0)

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
	

#EnduroSat commands
cmd1 		= "ES+W22003303"
cmd1R		= "Okay and .... 3303"
cmd2A 		= "ES+W22003363"
cmd2B 		= "a" * 12
cmd2C		= cmd1

# configure the serial connection
ser = serial.Serial(
	port='COM7',
	baudrate=115200,
	parity=serial.PARITY_NONE,
	stopbits=serial.STOPBITS_ONE,
	bytesize=serial.EIGHTBITS
)

ser.isOpen()

print('Enter your commands below.\r\nInsert "exit" to leave the application.')

cmd=1
retval = 0

while 1:

	# get keyboard input
	# cmd = input("Enter command or 'exit':")
	cmd = "dw d 11 1 " #raw_input(">> ")

	# Python 3 users
	# input = input(">> ")
	if cmd == 'exit':
		ser.close()
		exit()
	else:
		# send the character to the device
		# ar(32)
		# time.sleep(1)
		retval = dw('d', 11, 1)
		retval = dr('d', 11)
		time.sleep(1)
		retval = dw('d', 11, 0)
		retval = dr('d', 11)
		time.sleep(1)
		retval = dw('d', 11, 1)


		out = ''
		time.sleep(1)
		while ser.inWaiting() > 0:
			out += ser.read(1).decode('ascii')

		if out != '':
			print(out)
