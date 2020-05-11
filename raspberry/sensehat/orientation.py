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

def random_colour():
    return (randint(0,255), randint(0,255), randint(0,255))

# Arrow
# Define some colours
g = green
b = black
w = white

# Set up where each colour will display
pixels = [
    b, b, b, w, w, b, b, b,
    b, b, b, w, w, b, b, b,
    b, b, b, w, w, b, b, b,
    b, b, b, w, w, b, b, b,
    b, b, b, w, w, b, b, b,
    b, w, w, w, w, w, w, b,
    b, b, w, w, w, w, b, b,
    b, b, b, w, w, b, b, b
]

# Display these colours on the LED matrix
sense.set_pixels(pixels)

rotations = [0, 90, 180, 270]
r = 1
while True:
    sense.set_rotation(rotations[r])
    sleep(1)
    r = r + 1
    if r >= len(rotations):
        r = 0
