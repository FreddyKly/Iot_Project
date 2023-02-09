#!/bin/bash
# Author: Frederik Kliemt (1465987)

while getopts 'l:': flag
do
    case "${flag}" in
        l) login=${OPTARG};;
        *) error "Unexpected option ${flag}";;
    esac
done

if [ "$login" = "" ]; then
    echo "you must specify the flags -l"
    exit 1
fi

echo "Copying files from host to IoT-Lab using login: $login"
scp ./utils/gnrc_border_router.elf $login@grenoble.iot-lab.info:./A8
scp ./utils/MQTT_sender.elf $login@grenoble.iot-lab.info:./A8
scp ./setup_border_router_from_A8.sh $login@grenoble.iot-lab.info:./A8
scp ./setup_mqtt_script.sh $login@grenoble.iot-lab.info:./A8
scp -r ./mqtt_bridge $login@grenoble.iot-lab.info:./A8
scp ./utils/config_IoT.conf $login@grenoble.iot-lab.info:./A8
echo "Files were copied to IoT-Lab grenoble server ./A8"
