#!/usr/bin/env python

from sense_emu import SenseHat
sense = SenseHat()

green = (0, 255, 0)
red = (255, 0, 0)

while True:
    temperature = round(sense.get_temperature(), 1)
    humidity = round(sense.get_humidity(), 1)
    pressure = round(sense.get_pressure(), 1)

    status = "{}C {}% {}mbar".format(temperature, humidity, pressure)

    status_colour = green
    if temperature < 18.3 or temperature > 26.7:
        status_colour = red
    if pressure < 979 or pressure > 1027:
        status_colour = red
    if humidity < 55 or humidity > 65:
        status_colour = red
    
    print(status)
    sense.show_message(status, text_colour=(255,255,255), back_colour=status_colour, scroll_speed=0.05)
