#!/bin/bash
# Author: Frederik Kliemt (1465987)

iotlab_flash emcute_mqttsn.elf
miniterm.py /dev/ttyA8_M3 500000
