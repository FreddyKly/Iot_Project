#!/bin/bash
# Author: Frederik Kliemt (1465987)

iotlab_flash MQTT_sender.elf
miniterm.py /dev/ttyA8_M3 500000
