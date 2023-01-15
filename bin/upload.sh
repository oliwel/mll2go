#!/bin/bash

2>&1
arduino --board arduino:avr:nano:cpu=atmega328old  --upload --port /dev/ttyUSB0  --verbose-build  $(realpath $1) > upload.log

