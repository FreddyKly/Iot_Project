Readme
Author: Frederik Kliemt (1465987)

For a lookup of Nodenames see architecture.jpg
# Steps to replicate:
0. Reserve 3 A8 nodes in grenoble Iot-Lab
1. Open four terminals
2. Run `sh ./transfer_files_to_IoT-Lab.sh -l <iot-lab_login>` in __one__ terminal
3. SSH into IoT-Lab and navigate to the A8 directory of an A8 node and run `iotlab_reset`
4. Run `sh ./setup_border_router_from_A8.sh` to run a border-router (__A8-m3_1__)
5. In a __second__ terminal SSH into IoT-Lab and navigate to the A8 directory of an A8 node and run `iotlab_reset`
6. Run `ip -6 -o addr show eth0` to get the ip address of the A8 node
7. Run `broker_mqtts config.conf` (__A8-m3_2__)
8. In a __third__ terminal SSH into IoT-Lab and navigate to the A8 directory of an A8 node and run `iotlab_reset`
9. Run `sh ./setup_mqtt_script.sh` (__A8-m3_3__)
10. Type and the run `con {ip address from A8-m3_2} 1885`
11. After successfully connecting run `start`
12. In a __forth__ terminal SSH to the grenoble server
13. Run `nano mqtt_bridge/pybash_bridge.py` and change the IP-Addresses. (sub-process IP: IP of A8 node
that runs in the __second__ terminal. pub-process IP: IP of the EC2 instance)
14. Run `python3 mqtt_bridge/pybash_bridge.py`
15. Start two EC2 instances like described here: [Setup the AWS EC2 Instance](#setup-the-aws-ec2-instance)
16. On one of them create a file named "config.conf" and copy the contents of ./scripts/utils/config.conf into it.
17. Then run `mosquitto -c config.conf` set up a MQTT broker (__AWS EC2 Instance_1__)
18. On the other one run `mosquitto_sub -h <Public IP of AWS EC2 Instance_1> -p 1886 -t data`

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

## transfer_files_to_IoT-Lab.sh:
```
sh ./transfer_files_to_IoT-Lab.sh -l <iot-lab_login>
```

Transfers all files that are needed onto the A8 directory on IoT-Lab

## setup_mqtt_script.sh:
```
sh ./setup_mqtt_script.sh
```

## setup_border_router_from_A8.sh: 
```
sh ./setup_border_router_from_A8.sh
```
__<iot-lab_login>__: Your login for the IoT-Lab testbed
<br>

This script sets up a border router. This script can only be run when you already ssh'ed onto an A8 node and your current
directory is the A8 directory. To have script 
on the A8 folder the __transfer_files_to_IoT-Lab.sh__ was already run from your host mashine.

# Setup the AWS EC2 Instance 
0. From the AWS Learners Lab click on the "AWS" button to connect to "AWS Console"
1. When on the EC2 subpage on AWS (looking something like this: https://us-east-1.console.aws.amazon.com/ec2/home?region=us-east-1#Home:)
, press on __launch Instances__
2. Name the Instance
3. Select Ubuntu as OS Image
4. Set instance type to t2.micro
5. For Key-Pair set __"Proceed without a key pair"__
6. For Network setting click on "Edit"
7. Set "Auto-assign public ip" to "Enable"
8. For Inbound security group rules add a new group with "Type" = "All traffic" and "Source Type" = "anywhere"
9. Click "Launch Instance"
10. Wait until the instance is up and running and the click "Connect" and enter
the EC2 terminal
11. Continue with [Execution of commands on EC2](#execution-of-commands-on-ec2)


## Execution of commands on EC2
On EC2 Instance run the following commands:
```
#Update the list of repositories with one containing the latest version of #Mosquitto and update the package lists
sudo apt-add-repository ppa:mosquitto-dev/mosquitto-ppa
sudo apt-get update

#Install the Mosquitto broker, Mosquitto clients and the aws cli
sudo apt-get install mosquitto
sudo apt-get install mosquitto-clients
sudo apt install awscli
```
