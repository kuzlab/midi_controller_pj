from simplecoremidi import send_midi
import time
import serial
import os

class Command(object):
    """Run a command and capture it's output string, error string and exit status"""
    def __init__(self, command):
        self.command = command 
    def run(self, shell=True):
        import subprocess as sp
        process = sp.Popen(self.command, shell = shell, stdout = sp.PIPE, stderr = sp.PIPE)
        self.pid = process.pid
        self.output, self.error = process.communicate()
        self.failed = process.returncode
        return self
    @property
    def returncode(self):
        return self.failed

com = Command("ls /dev |grep tty |grep usb").run()
print com.output

usbport = '/dev/' + com.output.rstrip('\n')
ser = serial.Serial(usbport, 38400, timeout=1)

data = ['','','']
index = ['','']

count = 0
index_count = 0

data_count = 0

while (1):
#    response=ser.read()
#    time.sleep=2
    result=ser.read(ser.inWaiting())
    while(result.find("$") < 0):
        result=ser.read(ser.inWaiting())
    temp = result.find("$")
    while(result.rfind('$') == temp):
        result=ser.read(ser.inWaiting())
    data = result.split("$")[1].split(",")
    if len(data) >= 3:
        for i in range(len(data)):
            data[i] = int(data[i])
        print data        
#        send_midi((hex(int(data[0])), hex(int(data[1])), hex(int(data[2]))))
#        send_midi((0xb0, 0x02, 0x5f))
        send_midi((data))
#        send_midi((int(data[0]),int(data[1]), int(data[2])))

ser.close()


