#! /bin/python3

import serial
import sys
#### INICIALIZO EL SERIAL ####

init = False
port = "/dev/"+str(sys.argv[1])

print("Initializing serial port "+port+" (ctrl+C to break)")

while (not init):
    try:
        ser = serial.Serial(port, baudrate=38400)
        ser.flushInput()
        init = True
    except:
        pass

#### UNA VEZ INICIALIZADO EL SERIAL EMPIEZO LAS LECTURAS ####

while True:
    try:
        ser_bytes = ser.readline()
        decoded_bytes = ser_bytes.decode('UTF-8')
        print(decoded_bytes)
    except:
        print("Keyboard Interrupt")
        break
