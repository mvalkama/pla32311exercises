#!/usr/bin/env python

from time import sleep
from sense_emu import SenseHat
sense = SenseHat()
sense.clear()

while True:
    acceleration = sense.get_accelerometer_raw()

    x = acceleration['x']
    y = acceleration['y']
    z = acceleration['z']

    if abs(x) > 1 or abs(y) > 1 or abs(z) > 1:
        sense.show_letter("!", (255, 0, 0))
    else:
        sense.show_letter("M", (255, 255, 255))

        print("x: {:.1f} y: {:.1f} z: {:.1f}".format(x, y, z))
        x = round(acceleration['x'], 0)
        y = round(acceleration['y'], 0)
        z = round(acceleration['z'], 0)
        if x == -1:
            sense.set_rotation(180)
        elif y == 1:
            sense.set_rotation(90)
        elif y == -1:
            sense.set_rotation(270)
        else:
            sense.set_rotation(0)
