#!/bin/bash

# print date and time along with a list of users to a file 
# in temporary directory. This will be overwritten on each
# execution.

echo $(date) > /tmp/skripti.out
awk -F: '{ print $1}' /etc/passwd >> /tmp/skripti.out
