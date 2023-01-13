#!/bin/bash

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
all_ipv6=$(ip addr show dev eth0 | sed -e's/^.*inet6 \([^ ]*\)\/.*$/\1/;t;d');
ip_adress=$(echo $all_ipv6| cut -d' ' -f 1);
echo $ip_adress;
cd A8;
iotlab_flash gnrc_border_router.elf;
cd ~/A8/riot/RIOT/dist/tools/uhcpd;
make clean all;
cd ../ethos; make clean all;
./start_network.sh /dev/ttyA8_M3 tap0 2001:660:3207:401::/64 500000
EOF
