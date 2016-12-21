#!/bin/bash

if [ $(id -u) != "0" ]; then
    echo "You must be root to run this script"
    echo "Switch to root or run with sudo"
    exit 1
fi

echo "Enabling SPI0 and SPI1 at boot. Note: HDMI will no longer be functional."

sed -i '/CAPE/c\CAPE=ADAFRUIT-SPI0,ADAFRUIT-SPI1' /etc/default/capemgr

echo "Installing Dymo USB scale udev rules"

cp 51-dymo-scale.rules /etc/udev/rules.d/51-dymo-scale.rules

echo "Installing alsa sound libraries."

apt-get install libasound2-dev

echo "Please reboot for changes to take effect."
