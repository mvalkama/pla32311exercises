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

name = "Mika"

def random_colour():
    return (randint(0,255), randint(0,255), randint(0,255))

for i in range(len(name)):
    sense.show_letter(name[i], text_colour=random_colour())
    sleep(1)

sense.clear()
