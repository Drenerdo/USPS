"""
    @file           DymoScaleTest.py
    @author         BCA
    @version        1.0.0
    @date           12/5/16
    @brief          DymoScale Tests
    @copyright      Bay Computer Associates, Incorporated 2016
                    All rights reserved
                    This file contains CONFIDENTIAL material
    @remark         Matilda USPS Blue Box
    @Repository URL: $HeadURL: $
    Last changed by: $Author: $
    Last changed on: $Date: $
    Revision:        $Rev: $
"""
from DymoScale import DymoScale
import signal
import time

# Catch Ctrl+C and gracefully exit
def signal_handler(signal, frame):
    if (scale):
        scale.turnOff()
        exit()

signal.signal(signal.SIGINT, signal_handler)

# Initialize and power on the scale.
scale = DymoScale()

if (scale.isOn() == False):
    # If the scale is not on after the constructor, then something went
    # wrong. There should be an error printed out.
    exit();

units = "grams"

while 1:
    if (units == "grams"):
        value = scale.getWeightInGrams()
    else:
        value = scale.getWeightInOunces()

    if (value == -1):
        # Error case, try and restart the scale
        print("Turning on scale")
        scale.turnOff()
        scale.turnOn()
        if (not scale.isOn()):
            print("Tried to turn on the scale, but couldn't. Must have gotten unplugged.")
            exit()
    else:
        print(units + ": " + str(value))

    time.sleep(1)
    
    if (units == "grams"):
        units = "ounces"
    else:
        units = "grams"

scale.turnOff()
