#!/bin/bash

iotlab_flash emcute_mqttsn.elf
miniterm.py /dev/ttyA8_M3 500000
