#!/usr/bin/python3

import serial
import signal
import sys

keepReading = True

def signal_handler(sig, frame):
    global keepReading
    keepReading = False

signal.signal(signal.SIGINT, signal_handler)
serialport = serial.Serial('/dev/ttyACM0',9600)

min_vals = [0,0,0,0,0,0]
max_vals = [0,0,0,0,0,0]

print("Reading values, stop by pressing ctrl-c")

while keepReading:
    read_serial = serialport.readline().decode('ascii').strip()
    vals = read_serial.split("\t")

    for i in range(len(vals)):
        if float(vals[i]) < min_vals[i]:
            min_vals[i] = float(vals[i])
        if float(vals[i]) > max_vals[i]:
            max_vals[i] = float(vals[i])
            
print()
print("Minimum gyroscope values: {}, {}, {}".format(min_vals[0], min_vals[1], min_vals[2]))
print("Maximum gyroscope values: {}, {}, {}".format(max_vals[0], max_vals[1], max_vals[2]))
print("Minimum acceleration values: {}, {}, {}".format(min_vals[3], min_vals[4], min_vals[5]))
print("Maxmium acceleration values: {}, {}, {}".format(max_vals[3], max_vals[4], max_vals[5]))
