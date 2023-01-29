#!/bin/bash

iotlab_flash gnrc_border_router.elf;
cd ~/A8/riot/RIOT/dist/tools/uhcpd;
make clean all;
cd ../ethos; make clean all;
./start_network.sh /dev/ttyA8_M3 tap0 $INET6_PREFIX::/64 500000
