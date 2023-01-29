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

## tramsfer_files_to_IoT-Lab.sh:
```
sh ./tramsfer_files_to_IoT-Lab.sh
```

Transfers all files that are needed onto the A8 directory on IoT-Lab

## setup_border_router_from_A8.sh: 
```
sh ./setup_border_router_from_A8.sh -l <iot-lab_login>
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

Run Script to transfer config.conf file from Repository to EC2 instance root directory and then run:

```
mosquitto -c config.conf
```

This will start a Mosquitto broker that listens for MQTT messages on port 1883

To publish to this broker you could run a command like this:

```
mosquitto_pub -h <Public IP Adress of the EC2 instance› -p 1884 -t test/riot -m "iotlab"
```
