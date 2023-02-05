# Author: Frederik Kliemt (1465987)
import subprocess
import sys

sub_process = subprocess.Popen("mosquitto_sub -h " + sys.argv[1] + " -p 1886 -t test", stdout=subprocess.PIPE, shell=True)
while True:
        output = sub_process.stdout.readline()
        if output:
                print(output)
                pub_msgs = subprocess.run('mosquitto_pub -h ' + sys.argv[2] + ' -p 1886 -t test -m "' + str(output) + '"', shell=True)
