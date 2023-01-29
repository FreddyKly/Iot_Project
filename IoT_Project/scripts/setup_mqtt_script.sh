#!/bin/bash

iotlab_flash emcute_mqtts.elf
miniterm.py /dev/ttyA8_M3 500000
