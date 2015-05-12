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
        
USB_SERIAL = 2

com = Command("ls /dev |grep tty |grep usb").run()
#print com.output

if com.output == '':
    USB_SERIAL = 0

if USB_SERIAL:
    temp = com.output.strip('\n')
    print """com = Command("ls /dev |grep tty |grep usb").run() -> """
    print temp
    print(len(temp))
    print temp.find('\n')
    print temp.rfind('\n')
    if len(temp) <= 0:
        USB_SERIAL = 0
    elif temp.find('\n') > 0:
        usbport1 = '/dev/' + temp[:temp.find('\n')]
        usbport2 = '/dev/' + temp[temp.find('\n')+1:]
        USB_SERIAL = 2
        print "USB PORT detected"
        print usbport1
        print usbport2
    else:
        usbport1 = '/dev/' + temp
        print "USB PORT detected"        
        print usbport1
        USB_SERIAL = 1
    

com = Command("ls /tmp |grep tty | grep LightBlue-Bean").run()
#print com.output

if com.output == '':
    BEAN_SERIAL = 0
else:
    BEAN_SERIAL = 1
#    beanport = '/tmp/tty.LightBlue-Bean'
#    beanport = '/tmp/cu.LightBlue-Bean'
    beanport = '/dev/cu.LightBlue-Bean'
    beanser = serial.Serial(beanport, 57600, timeout=1)

if USB_SERIAL > 0:
    usbser1 = serial.Serial(usbport1, 57600, timeout=1)
if USB_SERIAL > 1:
    usbser2 = serial.Serial(usbport2, 57600, timeout=1)

data = ['','','']

prebeanval = 0.0


while (1):
    if USB_SERIAL > 0:
        result=usbser1.read(usbser1.inWaiting())
        if result != '':
            while(result.find("$") < 0):
                result=usbser1.read(usbser1.inWaiting())
            temp = result.find("$")
#            while(result.rfind('$') == temp):
            while(result.rfind('%') < 0):
                result+=usbser1.read(usbser1.inWaiting())
#            data = result.split("$")[1].split(",")
            temp = result.split('$')[1].split('%')[0]
            data = temp.split(',')
            if len(data) >= 3:
                for i in range(len(data)):
                    data[i] = int(data[i])
                print data
                send_midi((data))
    if USB_SERIAL > 1:
        result=usbser2.read(usbser2.inWaiting())
        if result != '':
            while(result.find("$") < 0):
                result=usbser2.read(usbser2.inWaiting())
            temp = result.find("$")
            while(result.rfind('%') < 0):
                result+=usbser2.read(usbser2.inWaiting())
            temp = result.split('$')[1].split('%')[0]
            data = temp.split(',')
            if len(data) >= 3:
                for i in range(len(data)):
                    data[i] = int(data[i])
                print data
                send_midi((data))
    if BEAN_SERIAL:
        result=beanser.read(beanser.inWaiting())
        if result != '':
            while(result.find("$") < 0):
                result+=beanser.read(beanser.inWaiting())
    #        result = result[:result.find("$")-1]
            result = result[result.find("$"):]
    #        temp = result.find("$")
    #        while(result.rfind('$') == temp):
            while(result.rfind('%') < 0):
                result +=beanser.read(beanser.inWaiting())
    #        print result
            print "bean serial: " + result
    #        data = result.split("$")[1].split(",")
            temp = result.split('$')[1].split('%')[0]
            data = temp.split(',')
    #        print data

    #        if len(data) == 3:
    #            if data[0] == '' or data[1] == '' or data[2] == '':
    #                pass
    #            elif data[0] == '-' or data[1] == '-' or data[2] == '-':
    #                pass
    #            else:
    #                for i in range(len(data)):
    #                    data[i] = int(data[i])
    #                temp = (data[0] + 512) * 128/1024
    #                if temp > 127:
    #                    temp = 127
    #                senddata = [0xB0, 1, int(prebeanval + (temp - prebeanval)/3)]
    #                send_midi((senddata))
    #                senddata = [0xB0, 1, int(prebeanval + (temp - prebeanval)*2/3)]
    #                send_midi((senddata))                
    #                senddata = [0xB0, 1, int(temp)]
    #                send_midi((senddata))
            if len(data) >= 3:
                if data[0] == '' or data[1] == '' or data[2] == '':
                    pass
                else:
                    for i in range(len(data)):
                        data[i] = int(data[i])
                    print data
                    send_midi((data))
    #            print "\t\tmidi sent! = " + str(senddata)
    #            prebeanval = temp    

if USB_SERIAL > 0:
    usbser1.close()
if USB_SERIAL > 1:
    usbser2.close()
beanser.close()


