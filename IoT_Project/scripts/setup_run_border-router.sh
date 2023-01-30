#!/bin/bash
# Author: Frederik Kliemt (1465987)

while getopts 'l:n:': flag
do
    case "${flag}" in
        l) login=${OPTARG};;
        n) node=${OPTARG};;
        *) error "Unexpected option ${flag}";;
    esac
done

if [ "$login" = "" ] || [ "$node" = "" ]; then
    echo "you must specify the flags -l and -n"
    exit 1
fi

echo "Copying files from host to IoT-Lab using login: $login"
scp ./utils/gnrc_border_router.elf $login@grenoble.iot-lab.info:./A8
echo "Files were copied to IoT-Lab grenoble server ./A8"

ssh -t $login@grenoble.iot-lab.info ssh -t root@node-a8-$node /bin/bash << 'EOF'
cd A8;
iotlab_flash gnrc_border_router.elf;
cd ~/A8/riot/RIOT/dist/tools/uhcpd;
make clean all;
cd ../ethos; make clean all;
./start_network.sh /dev/ttyA8_M3 tap0 $INET6_PREFIX::/64 500000
EOF
