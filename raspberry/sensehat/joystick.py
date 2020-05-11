#!/usr/bin/env python

from random import randint
from time import sleep
from sense_emu import SenseHat
sense = SenseHat()

blue = (0, 0, 255)
green = (0, 255, 0)
yellow = (255, 255, 0)
white = (255, 255, 255)
red = (255, 0, 0)
black = (0, 0, 0)

while True:
    for event in sense.stick.get_events():
        print(event.direction, event.action)
        if event.action == "pressed":
            if event.direction == "up":
                sense.show_letter("U")
            elif event.direction == "down":
                sense.show_letter("D")
            elif event.direction == "left":
                sense.show_letter("L")
            elif event.direction == "right":
                sense.show_letter("R")
            elif event.direction == "middle":
                sense.show_letter("M")

            sleep(0.5)
            sense.clear()

