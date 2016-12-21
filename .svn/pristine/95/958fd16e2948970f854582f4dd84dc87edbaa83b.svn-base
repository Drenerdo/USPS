"""
    @file           DymoScale.py
    @author         BCA
    @version        1.0.0
    @date           12/5/16
    @brief          DymoScale USPS Blue Box API
    @copyright      Bay Computer Associates, Incorporated 2016
                    All rights reserved
                    This file contains CONFIDENTIAL material
    @remark         Matilda USPS Blue Box
    @Repository URL: $HeadURL: $
    Last changed by: $Author: $
    Last changed on: $Date: $
    Revision:        $Rev: $
"""

import os
import struct
import time
import signal
import Adafruit_BBIO.GPIO as GPIO
import threading

class DymoScale:
    """DymoScale is a USB scale"""

    # Private variables
    _device = None
    _switching_units = False
    _taking_reading = False
    _powerPin = None
    _unitsPin = None
    _t = None
    
    def __init__(self, device = "/dev/usb/hiddev0", powerPin = "P8_12", unitsPin = "P8_11"):
        """The constructor for the DymoScale will initialize the usb device and
        power on the device.
        Note that the scale will automatically zero on boot, so make sure
        nothing is on top of the scale when this function is called."""

        # Set up GPIO for the buttons
        self._powerPin = powerPin
        self._unitsPin = unitsPin
        GPIO.setup(self._powerPin, GPIO.OUT)
        GPIO.setup(self._unitsPin, GPIO.OUT)

        # Pins are active low, so set them high (inactive) for now
        GPIO.output(self._powerPin, GPIO.HIGH)
        GPIO.output(self._unitsPin, GPIO.HIGH)

        try:
            fd = os.open(device, os.O_RDONLY)
            os.close(fd)
        except OSError as e:
            print("Error opening Dymo USB Scale.")
            print("Make sure it is plugged in and run with sudo.")
            return

        self._device = device

        self.turnOn()
    
    def getWeightInGrams(self):
        """Get the weight on the scale in grams.

        @returns -1 on error, grams on success
        """
        grams = -1
        units = 0

        if (not self.isOn()):
            print("Scale not on. Remove items and call powerOn()")
            return grams
        
        # Wait till we are done switching units
        while (self._switching_units):
            time.sleep(0.05)
        
        self._taking_reading = True
        
        try:
            fd = os.open(self._device, os.O_RDONLY)
            # Read 4 integers from the scale
            fmt = "iiii"
            data = os.read(fd, struct.calcsize(fmt))
            usb_binary_read = struct.unpack(fmt, data)
            # detect if data is valid
            while (usb_binary_read[2] != 9240640):
                data = os.read(fd, struct.calcsize(fmt))
                usb_binary_read = struct.unpack(fmt, data)
                
            units = usb_binary_read[1]
            grams = usb_binary_read[3]
            os.close(fd)
        except OSError:
            print("Read fail.")
            return -1

        if (grams == 0):
            self._taking_reading = False
            return 0
        elif (units == 0):
            self._taking_reading = False
            return grams
        else:
            # Units are in oz, switch to grams
            self._pressSwitchUnits()
            # dummy read
            time.sleep(1);
            return self.getWeightInGrams()

    def getWeightInOunces(self):
        """Get the weight on the scale in ounces to the nearest 0.1oz.

        @returns -1 on error, ounces on success
        """
        grams = self.getWeightInGrams()
        if (grams == -1):
            return grams
        else:
            return round(grams * 0.03527396195, 1)

    def turnOn(self):
        """Turns on the scale if it is off. Only needed if an error is detected.
        Note that the scale will automatically zero on boot, so make sure
        nothing is on top of the scale when this function is called."""
        if (not self.isOn()):
            self._pressPower()
            time.sleep(1) # Give the scale some time to boot
            # Start a separate thread to prevent the scale from shutting down
            if (self._t == None):
                self._preventAutoShutdown()

    def turnOff(self):
        """Turns off the scale if it is on.
        Note that the weight functions will return errors if they are called
        after this."""
        if (self.isOn()):
            self._pressPower()
            time.sleep(0.5) # Give the scale some time to shut down
        self._cleanUpThread()

    def isOn(self):
        """Check if the scale is on.
        @returns True if the scale is on, False otherwise."""

        if (self._device == None):
            return False
        
        # Change the behavior of SIGALRM to call the timeout handler
        # after 1 second.
        signal.signal(signal.SIGALRM, self._ReadTimeoutHandler)
        signal.alarm(1)
        
        # open the device and try to read from it to see if the scale is awake.
        try:
            fd = os.open(self._device, os.O_RDONLY)
            # Read 4 integers from the scale
            fmt = "iiii"
            data = os.read(fd, struct.calcsize(fmt))
            usb_binary_read = struct.unpack(fmt, data)
            os.close(fd)
            signal.alarm(0)
        except self._ReadTimeoutException:
            return False
        except OSError:
            signal.alarm(0)
            return False
        return True
    
    ###############################
    # Private Classes and Functions
    ###############################
    class _ReadTimeoutException(Exception):
        """A dummy exception used internally for a read timeout."""
        pass
    
    def _ReadTimeoutHandler(self, signum, frame):
        """A handler for when a read times out."""
        raise self._ReadTimeoutException
    
    def _preventAutoShutdown(self):
        """Prevent the scale from shutting down by toggling the units
           every once in a while. """
        
         # Wait till we are done reading before switching units
        while (self._taking_reading):
            time.sleep(0.05)
        
        self._switching_units = True

        self._pressSwitchUnits()
        time.sleep(0.5) # needed between presses for the scale to register a press
        self._pressSwitchUnits()
        self._switching_units = False

        # Periodically prevent the device from shutting off.
        self._t = threading.Timer(60.0, self._preventAutoShutdown)
        self._t.daemon = True
        self._t.start()
        
    def _pressPower(self):
        """Press and release the power button."""
        GPIO.output(self._powerPin, GPIO.LOW)
        time.sleep(0.5)
        GPIO.output(self._powerPin, GPIO.HIGH)

    def _pressSwitchUnits(self):
        """Press and release the switch units button."""
        GPIO.output(self._unitsPin, GPIO.LOW)
        time.sleep(0.2)
        GPIO.output(self._unitsPin, GPIO.HIGH)
        
    def _cleanUpThread(self):
        self._taking_reading = False
        if (self._t):
            self._t.cancel()
            self._t.join(0.1)
            self._t = None
    
    def __del__(self):
        self._cleanUpThread()
