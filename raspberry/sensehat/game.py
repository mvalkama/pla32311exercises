#!/usr/bin/env python

from random import choice
from time import sleep
from sense_emu import SenseHat
sense = SenseHat()

green = (0, 255, 0)
white = (255, 255, 255)
red = (255, 0, 0)
black = (0, 0, 0)

sense.clear()
sleep(1)

rotations = [0, 90, 180, 270]

def generate_arrow(fgcolour, bgcolour):
    # Set up where each colour will display
    pixels = [
        0, 0, 0, 1, 1, 0, 0, 0,
        0, 0, 0, 1, 1, 0, 0, 0,
        0, 0, 0, 1, 1, 0, 0, 0,
        0, 0, 0, 1, 1, 0, 0, 0,
        0, 0, 0, 1, 1, 0, 0, 0,
        0, 1, 1, 1, 1, 1, 1, 0,
        0, 0, 1, 1, 1, 1, 0, 0,
        0, 0, 0, 1, 1, 0, 0, 0
    ]

    for i in range(len(pixels)):
        if pixels[i] == 1:
            pixels[i] = fgcolour
        else:
            pixels[i] = bgcolour

    return pixels

def check_orientation():
    acceleration = sense.get_accelerometer_raw()
    x = round(acceleration['x'], 0)
    y = round(acceleration['y'], 0)
    z = round(acceleration['z'], 0)
    if x == -1:
        return 180
    elif y == 1:
        return 90
    elif y == -1:
        return 270
    else:
        return 0

white_arrow = generate_arrow(white, black)
green_arrow = generate_arrow(green, black)
red_arrow = generate_arrow(red, black)

pause = 3
score = 0
angle = 0
play = True

while play == True:
    angle = choice(rotations)
    sense.set_rotation(angle)
    sense.set_pixels(white_arrow)
    sleep(pause)
    if check_orientation == angle:
        score = score + 1
        sense.set_pixels(green_arrow)
    else:
        sense.set_pixels(red_arrow)
        play = False


    pause = pause * 0.97
    
    sleep(1)

gameover = "Game over, score {}".format(score)

sense.show_message(gameover, text_colour=white)
