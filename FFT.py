import matplotlib.pyplot as plt
import numpy as np
import serial
import time

serdev = '/dev/ttyACM0'
s = serial.Serial(serdev)
while (1): 
    line = s.readline()
    print(line)
# for i in range(1024):
#     line = s.readline()
#     print(line)
s.close()