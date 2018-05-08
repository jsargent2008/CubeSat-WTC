#! /usr/bin/env python
import serial
import time
# See the read version; we do most of the stuff there.
# Ideally we would want to service all reads with an interrupt.
ser = serial.Serial('/dev/ttyUSB0', 115200, timeout=1)
ser.write(b'\rES+R2200\r')
s  = ser.read(256)
print s
ser.write(b'\rES+W22003603\r')
s  = ser.read(256)
print s
ser.write(b'\rES+R2200\r')
s  = ser.read(256)
print s
ser.write(b'\rES+R2201\r')
s  = ser.read(256)
print s
ser.write(b'\rES+W2201422F0A42\r')
s  = ser.read(256)
print s
ser.write(b'\rES+R2201\r')
s  = ser.read(256)
print s
ser.write(b'\rES+W220033A3\r')
s  = ser.read(256)
print s
# This is our test loop.  We send some stuff, then send something for which we wish a response.
while True:
    s = ser.readline()
    print s
    ser.write(b'This is a test\r\n')
    # ser.write(jBytes)
    time.sleep(0.25)
    s = ser.readline()
    print s
    ser.write(b'This is a test\r\n')
    # ser.write(jBytes)
    time.sleep(0.25)
    s = ser.readline()
    print s
    ser.write(b'Please Send file  \r\n')
    # ser.write(jBytes)
    time.sleep(0.25)
ser.close()
