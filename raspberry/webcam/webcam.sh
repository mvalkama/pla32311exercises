#!/bin/bash
DATE=$(date +"%Y-%m-%d_%H%M")
fswebcam -r 1280x720 --rotate 180 --title "RPi4 Camera" --jpeg 60 /tmp/webcam/$DATE.jpg
