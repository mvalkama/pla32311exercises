#!/usr/bin/python3

import serial
import signal
import sys
from influxdb_client import InfluxDBClient, Point
from influxdb_client.client.write_api import SYNCHRONOUS

keepReading = True

def signal_handler(sig, frame):
    global keepReading
    keepReading = False

def writeToInflux(value):
    bucket = "temperature"
    client = InfluxDBClient(url="INFLUXHOST", token="TOKEN", org="ORG")

    write_api = client.write_api(write_options=SYNCHRONOUS)

    p = Point("sensor").field("temperature", float(value))
    write_api.write(bucket=bucket, record=p)

def main():
    signal.signal(signal.SIGINT, signal_handler)
    serialport = serial.Serial('/dev/ttyACM0',9600)

    print("Reading values, stop by pressing ctrl-c")

    while keepReading:
        line = serialport.readline().decode('ascii').strip()

        print(line)
        
        if not line.startswith("D "):
            writeToInflux(line)
            
main()
