#!/usr/bin/env python

from random import randint
from time import sleep
from sense_emu import SenseHat
sense = SenseHat()

def red():
    sense.clear(255, 0, 0)

def green():
    sense.clear(0, 255, 0)

def blue():
    sense.clear(0, 0, 255)

def yellow():
    sense.clear(255, 255, 0)

sense.stick.direction_up = red
sense.stick.direction_down = green
sense.stick.direction_left = blue
sense.stick.direction_right = yellow
sense.stick.direction_middle = sense.clear

while True:
    pass

