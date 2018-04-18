import time
import serial
import sys
import re
from enum import Enum 

def printf(format, *args):
	sys.stdout.write(format % args)


commandline = sys.stdin.readline()

# remove trailing/leading spaces
#commandline.lstrip()
#commandline.rstrip()
commandline = commandline.strip()
commandline = commandline.replace(' ', '')

# if dw, dr, aw, ar, tt
subcmd0 = commandline[0:2]

#dw
# if a, b, c, d
subcmd1 = commandline[2:3]
# if 0<x<15
subcmd2 = commandline[3:5]
# if 0 or 1
subcmd3 = commandline[5:6]

printf(commandline)
printf(subcmd0 + '\n')
printf(subcmd1 + '\n')
printf(subcmd2 + '\n')
printf(subcmd3 + '\n')

#dr
# subcmd1 = commandline[2:2]

# subcmd2 = command[3:4]
# subcmd3 = command[5:5]
