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

sense.clear(random_colour())
sleep(1)

# light corners
maxc = 7
sense.clear()
sense.set_pixel(0, 0, white)
sense.set_pixel(0, maxc, white)
sense.set_pixel(maxc, 0, white)
sense.set_pixel(maxc, maxc, white)
sleep(1)

# draw smiley 
sense.clear()
sense.set_pixel(2, 2, (0, 0, 255))
sense.set_pixel(4, 2, (0, 0, 255))
sense.set_pixel(3, 4, (100, 0, 0))
sense.set_pixel(1, 5, (255, 0, 0))
sense.set_pixel(2, 6, (255, 0, 0))
sense.set_pixel(3, 6, (255, 0, 0))
sense.set_pixel(4, 6, (255, 0, 0))
sense.set_pixel(5, 5, (255, 0, 0))
sleep(1)

pixels = []
for i in range((maxc + 1)**2):
    pixels.append(random_colour())

sense.set_pixels(pixels)
sleep(1)

# Creeper
# Define some colours
g = green
b = black

# Set up where each colour will display
pixels = [
    g, g, g, g, g, g, g, g,
    g, g, g, g, g, g, g, g,
    g, b, b, g, g, b, b, g,
    g, b, b, g, g, b, b, g,
    g, g, g, b, b, g, g, g,
    g, g, b, b, b, b, g, g,
    g, g, b, b, b, b, g, g,
    g, g, b, g, g, b, g, g
]

# Display these colours on the LED matrix
sense.set_pixels(pixels)

