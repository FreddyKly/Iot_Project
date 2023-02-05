# Author: Frederik Kliemt (1465987)
import subprocess
import sys

#Subscribe to the A8-m3_2 Broker
sub_process = subprocess.Popen("mosquitto_sub -h " + sys.argv[1] + " -p 1886 -t test", stdout=subprocess.PIPE, shell=True)
while True:
        # Safe the message that was received in local storage
        output = sub_process.stdout.readline()
        if output:
                print(output)
                # publish the saved message to the AWS EC2 Instance_1 Broker
                pub_msgs = subprocess.run('mosquitto_pub -h ' + sys.argv[2] + ' -p 1886 -t test -m "' + str(output) + '"', shell=True)
