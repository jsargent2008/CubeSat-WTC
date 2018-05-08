#! /usr/bin/env python
import serial
import time
import re
# Configure the port
ser = serial.Serial('/dev/ttyUSB0', 115200, timeout=1)
# Request the status control word 
ser.write(b'\rES+R2200\r')
s  = ser.read(256)
print s
# Write the status control word to set 19200 RF mode
ser.write(b'\rES+W22003603\r')
s  = ser.read(256)
print s
ser.write(b'\rES+R2200\r') # Status control
s  = ser.read(256)
print s
# Read the current center frequency
ser.write(b'\rES+R2201\r')
s  = ser.read(256)
print s
# Set the frequency to 437.275 MHz
ser.write(b'\rES+W2201422F0A42\r')
s  = ser.read(256)
print s
ser.write(b'\rES+R2201\r') # Current freq.
s  = ser.read(256)
print s
# Set the current status to RF Mode 9600, Echo on, Pipe On
# (Means you can now send/rcv. stuff)
ser.write(b'\rES+W220033A3\r')
s  = ser.read(256)
print s
while True:
 #   s  = ser.read(256)
    s = ser.readline() # Read some data.
    print s
    # Look for our test command.  If we find it, reply via RF/TX.
    if (re.search('Send file',s)):
        ser.write(b'Got the command')
    time.sleep(0.25)
ser.close()
