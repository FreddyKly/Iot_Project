#!/bin/bash

while getopts l: flag
do
    case "${flag}" in
        l) login=${OPTARG};;
        n) node=${OPTARG};;
    esac
done

echo "Copying files from host to IoT-Lab using login: $login"
scp ./utils/gnrc_border_router.elf $login@grenoble.iot-lab.info:./A8
echo "Files were copied to IoT-Lab grenoble server ./A8"

ssh $login@grenoble.iot-lab.info /bin/bash << EOF
ssh root@node-a8-$node /bin/bash << EOF
echo "I'm at the A8 right now"
EOF
EOF
