#!/usr/bin/env python

from sense_emu import SenseHat
sense = SenseHat()

blue = (0, 0, 255)
yellow = (255, 255, 0)

while True:
    sense.show_message("PLA32311", text_colour=yellow, back_colour=blue, scroll_speed=0.05)
