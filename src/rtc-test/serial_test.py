import serial
import time

port = '/dev/ttyUSB0'
baud = 1200

ser = serial.Serial( port, baud)

if not ser.is_open:
    print("Can't open port")
    exit

while True:
    ser.write( b'Hello\r\n')
    time.sleep(1)
    
    
