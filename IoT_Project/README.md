Readme

# Run the bash scripts
Replace "<name_of_the_script>" with the name of the script you want to run. Make sure to change directory to _"/scripts"_ before executeing the following command:

```
sh ./<name_of_the_script> -<flag> <argument>
```

# Scripts
The functionality the scripts in _"/scripts"_ are executing:

## setup_run_border-router.sh: 
```
sh ./setup_run_border-router.sh -l <iot-lab_login> -n <node_number>
```
__<iot-lab_login>__: Your login for the IoT-Lab testbed
<br>
__<node_number>__: The number of the A8 node you reserved for the border-router (if you reserved node a8-102 you would need to provide "102" here)

This Script can be executed after you established [SSH Access](https://www.iot-lab.info/legacy/tutorials/ssh-access/index.html) to IoT-Lab, a A8-node was reserved on IoT-Lab and the RIOT repository was cloned to the A8 directory (explained [here](https://www.iot-lab.info/legacy/tutorials/riot-public-ipv6-a8-m3/index.html) in the steps 1 - 4). 

The script will copy the _"gnrc_border_router.elf"_ to the ./A8 directory. It then will ssh onto the specified A8 Board, build and run the border-router.
