# Pero 2015
#
# Interface with the Loveread Lamp prototype.
# The program gets the acceletometer data from the MPU6050.
# Based on the code from Henrik Forsten
# 
# Februrary 2016
#


import serial
import sys
import argparse
import time
from collections import deque

import matplotlib.pyplot as plt
import matplotlib.animation as animation

BAUDRATE = 115200
PARITY = False

class AnalogPlot:
    def __init__(self, ser, maxlen):
        self.x = deque([0]*maxlen, maxlen)
        self.y1 = deque([0]*maxlen, maxlen)
        self.y2 = deque([0]*maxlen, maxlen)        
        self.y3 = deque([0]*maxlen, maxlen)
        self.maxlen = maxlen
        self.starttime = time.time()
        self.ser = ser

    def add(self, status):
        #Only add datapoint when it's possible to add in
        #both plots
        if 'acc_x' in status:
            self.x.appendleft(time.time() - self.starttime)
            self.y1.appendleft(status['acc_x'])
            self.y2.appendleft(status['acc_y'])
            self.y3.appendleft(status['acc_z'])

    def update(self, frameNum, p0, p1, p2, ax):
        try:
            status = get_status(self.ser)
            self.add(status)
            print_status(status)
            fajl.write(str(self.x[1]))
            fajl.write('\t')
            fajl.write(str(status['acc_y']))
            fajl.write('\n')
            
        except TypeError:
            pass
        ax.set_xlim(self.x[-1], max(10,self.x[0]))
        ax.set_ylim((min(-250,min(self.y1),min(self.y2),min(self.y3)), max(250,max(self.y2),max(self.y1),max(self.y3))))
        p0.set_data(self.x, self.y1)
        p1.set_data(self.x, self.y2)
        p2.set_data(self.x, self.y3)
        return (p0,p1,p2,ax)

#Configures serial port
def configure_serial(serial_port):
    return serial.Serial(
        port=serial_port,
        baudrate=BAUDRATE,
        parity=serial.PARITY_EVEN if PARITY else serial.PARITY_NONE,
        stopbits=serial.STOPBITS_TWO,
        bytesize=serial.EIGHTBITS,
        timeout=0.05)

def get_status(ser):
    s = ser.readline()
    if (s and s[0] == 'a'):     # get only accelerometer data
        s = s.replace('accel x,y,z: ', '')
        data = s.split(',')
#        print data
        try:
            x = float(data[0])
            y = float(data[1])
            z = float(data[2])
#            print x,y,z
            return {'acc_x':x, 'acc_y':y, 'acc_z':z}
        except:
            print 'Neki kurac nevalja u get_status'
            pass
    return None

def print_status(status):
    try:
        print 'X: {acc_x:3.2f}, Y: {acc_y:3.2f}, Z: {acc_z:3.2f}'.format(**status)
    except (TypeError, KeyError):
        pass
#        print 'Neki kurac nevalja u print_status'

if __name__ == "__main__":
#    parser = argparse.ArgumentParser(description="PID controller for Reflow oven")
#    parser.add_argument('-p','--set_pid', nargs=3, metavar=('P','I','D'), type=float, help='Set PID coefficients')
#    parser.add_argument('-g','--get', action='store_true', help='Get the current profile')
#    parser.add_argument('-l','--plot', dest='plot', action='store_true', help="Draw plot")
#    parser.add_argument('-n','--no-plot', dest='plot', action='store_false', help="Don't draw plot")
#    parser.add_argument('port',metavar='Port', help='Serial port')
#    parser.set_defaults(get=False, plot=True)
#    args = parser.parse_args()

#    if len(sys.argv)<2:
#        print "Give serial port address as a command line argument."
#        exit()
    port = "COM3"
    try:
        ser = configure_serial(port)
        if not ser.isOpen():
            raise Exception
    except:
        print('Opening serial port %s failed.' %port)
        exit(1)
        
    print('reading from serial port %s...' %port)

    fajl = open('Acctest.txt','w')
    analogPlot = AnalogPlot(ser, 3000)

    fig = plt.figure()
    ax = plt.axes(xlim=(0, 100), ylim=(0, 300))
    p0, = ax.plot([], [])
    p1, = ax.plot([], [])     
    p2, = ax.plot([], [])     
    
    anim = animation.FuncAnimation(fig, analogPlot.update,
                                     fargs=(p0,p1,p2,ax),
                                     interval=10)
    plt.show()
    exit()

    while True:
        try:
            try:
                print_status(get_status(ser))
            except serial.serialutil.SerialException:
                continue
            except OSError:
                continue
            except KeyError:
                continue
        except KeyboardInterrupt:
            ser.close()
            fajl.close()
            break
