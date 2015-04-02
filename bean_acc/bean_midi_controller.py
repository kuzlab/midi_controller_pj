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

#usbport = '/dev/' + com.output.rstrip('\n')
usbport = '/tmp/tty.LightBlue-Bean'
#usbport = '/dev/tty.Bluetooth-Incoming-Port'
ser = serial.Serial(usbport, 57600, timeout=1)

data = ['','','']
index = ['','']

count = 0
index_count = 0

data_count = 0

while (1):
    result=ser.read(ser.inWaiting())
#    if result != '':
    while(result.find("$") < 0):
        result+=ser.read(ser.inWaiting())
#        print result
    result = result[:result.find("$")-1]
    temp = result.find("$")
#    print "temp = " + str(temp)
#    print "-> " + str(result.rfind('$'))
    while(result.rfind('$') == temp):
        result +=ser.read(ser.inWaiting())
#        print result
#        print result.rfind('$')
#    print "two $? " + result
    print result
    data = result.split("$")[0].split(",")
    print data
    if len(data) == 3:
        if data[0] == '' or data[1] == '' or data[2] == '':
            pass
        elif data[0] == '-' or data[1] == '-' or data[2] == '-':
            pass
        else:
            for i in range(len(data)):
                data[i] = int(data[i])
            print data
            senddata = [0xB0,1,int((data[0] + 256)/4)]
            send_midi((senddata))
            print senddata
            senddata = [0xB0,2,int((data[1] + 256)/4)]
            send_midi((senddata))
            print senddata        
            senddata = [0xB0,3,int((data[2] + 256)/4)]
            send_midi((senddata))
            print senddata
        

ser.close()


