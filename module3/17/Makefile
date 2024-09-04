all: server client sniffer

server: udpserver.c
	gcc -o udpserver udpserver.c

client: udpclient.c
	gcc -o udpclient udpclient.c

sniffer: sniffer.c 
	gcc -o sniffer sniffer.c