import subprocess

sub_process = subprocess.Popen("mosquitto_sub -h 2001:660:5307:3000::67 -p 1886 -t test", stdout=subprocess.PIPE, shell=True)
while True:
        output = sub_process.stdout.readline()
        if output:
                print(output)
                pub_msgs = subprocess.run('mosquitto_pub -h 100.26.213.64 -p 1886 -t test -m "' + str(output) + '"', shell=True)
