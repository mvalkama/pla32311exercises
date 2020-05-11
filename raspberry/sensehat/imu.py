#!/usr/bin/env python

from time import sleep
from sense_emu import SenseHat
sense = SenseHat()
sense.clear()

while True:
    o = sense.get_orientation()
    pitch = round(o["pitch"], 2)
    roll = round(o["roll"], 2)
    yaw = round(o["yaw"], 2)

    print("pitch: {} roll: {} yaw: {}".format(pitch, roll, yaw))
