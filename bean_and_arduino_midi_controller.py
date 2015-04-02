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

beanport = '/tmp/tty.LightBlue-Bean'
beanser = serial.Serial(beanport, 57600, timeout=1)

usbser = serial.Serial(usbport, 38400, timeout=1)

data = ['','','']

prebeanval = 0.0

while (1):
    result=usbser.read(usbser.inWaiting())
    if result != '':
        while(result.find("$") < 0):
            result=usbser.read(usbser.inWaiting())
        temp = result.find("$")
        while(result.rfind('$') == temp):
            result=usbser.read(usbser.inWaiting())
        data = result.split("$")[1].split(",")
        if len(data) >= 3:
            for i in range(len(data)):
                data[i] = int(data[i])
            print data
            send_midi((data))
            
    result=beanser.read(beanser.inWaiting())
    if result != '':
        while(result.find("$") < 0):
            result+=beanser.read(beanser.inWaiting())
        result = result[:result.find("$")-1]
        temp = result.find("$")
        while(result.rfind('$') == temp):
            result +=beanser.read(beanser.inWaiting())
#        print result
        data = result.split("$")[0].split(",")
#        print data
        if len(data) == 3:
            if data[0] == '' or data[1] == '' or data[2] == '':
                pass
            elif data[0] == '-' or data[1] == '-' or data[2] == '-':
                pass
            else:
                for i in range(len(data)):
                    data[i] = int(data[i])
#                print data
#                senddata = [0xB0,1,int((data[0] + 256)/4)]
                temp = abs(data[0]) * 128/256
                if temp > 127:
                    temp = 127
                senddata = [0xB0, 1, int(prebeanval + (temp - prebeanval)/3)]
                send_midi((senddata))
                senddata = [0xB0, 1, int(prebeanval + (temp - prebeanval)*2/3)]
                send_midi((senddata))                
                senddata = [0xB0, 1, int(temp)]
                send_midi((senddata))
                print senddata
#                senddata = [0xB0,2,int((data[1] + 256)/4)]
#                send_midi((senddata))
#                print senddata        
#                senddata = [0xB0,3,int((data[2] + 256)/4)]
#                send_midi((senddata))
#                print senddata

#                if abs(data[0]) + abs(data[1]) > 200:
#                    temp = (abs(data[0]) + abs(data[1]) - 200) * 128/1000
#                    if temp >= 128:
#                        temp = 127
#                    print temp
#                    senddata = [0xB0,3,int(temp)]
#               #       senddata = [0x90,0x30,int(temp)]
#                    send_midi((senddata))
usbser.close()
beanser.close()


