#!/bin/bash
# Author: Frederik Kliemt (1465987)

while getopts 'i:': flag
do
    case "${flag}" in
        l) IP=${OPTARG};;
        *) error "Unexpected option ${flag}";;
    esac
done

if [ "$IP" = "" ]; then
    echo "you must specify the flags -i"
    exit 1
fi

mosquitto_sub -h $IP -p 1886 -t test
