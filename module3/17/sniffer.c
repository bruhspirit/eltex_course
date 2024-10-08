#include<stdio.h>	//For standard things
#include<stdlib.h>	//malloc
#include<string.h>	//memset
#include<netinet/ip_icmp.h>	//Provides declarations for icmp header
#include<netinet/udp.h>	//Provides declarations for udp header
#include<netinet/tcp.h>	//Provides declarations for tcp header
#include<netinet/ip.h>	//Provides declarations for ip header
#include<sys/socket.h>
#include<arpa/inet.h>
#include <signal.h>
#include <unistd.h>


void stop_handler(int);
void print_ip_header(unsigned char* Buffer, int Size);
void print_udp_packet(unsigned char * , int);
void PrintData (unsigned char* data , int Size);

int sock_raw,
	total_packages;

FILE *logfile;

struct sockaddr_in source,dest;

int main(int argc, char const *argv[])
{
	int saddr_size , data_size;
	struct sockaddr saddr;
	struct in_addr in;

	unsigned char *buffer = (unsigned char *)malloc(65536);

	logfile=fopen("log.txt","w");
	if(logfile==NULL) 
		printf("[-]Error: Unable to create file.\n");

	printf("Starting...To stop capturing press Ctrl+C\n");

	sock_raw = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
	if(sock_raw < 0)
	{
		printf("[-]Error: Unable to create raw socket\n");
		return 1;
	}

	while(1)
	{

		saddr_size = sizeof saddr;
		data_size = recvfrom(sock_raw , buffer , 65536 , 0 , &saddr , &saddr_size);
		if(data_size < 0 )
		{
			printf("[-]Error: Recvfrom error , failed to get packets\n");
			return 1;
		}
		struct iphdr *iph = (struct iphdr*)buffer;
		total_packages++;

		print_udp_packet(buffer, data_size);
		
	}
	close(sock_raw);
	return 0;
}

void print_ip_header(unsigned char* Buffer, int Size)
{
	unsigned short iphdrlen;
		
	struct iphdr *iph = (struct iphdr *)Buffer;
	iphdrlen =iph->ihl*4;
	
	memset(&source, 0, sizeof(source));
	source.sin_addr.s_addr = iph->saddr;
	
	memset(&dest, 0, sizeof(dest));
	dest.sin_addr.s_addr = iph->daddr;
	
	fprintf(logfile,"\n");
	fprintf(logfile,"IP Header\n");
	fprintf(logfile,"   |-IP Version        : %d\n",(unsigned int)iph->version);
	fprintf(logfile,"   |-IP Header Length  : %d DWORDS or %d Bytes\n",(unsigned int)iph->ihl,((unsigned int)(iph->ihl))*4);
	fprintf(logfile,"   |-Type Of Service   : %d\n",(unsigned int)iph->tos);
	fprintf(logfile,"   |-IP Total Length   : %d  Bytes(Size of Packet)\n",ntohs(iph->tot_len));
	fprintf(logfile,"   |-Identification    : %d\n",ntohs(iph->id));
	//fprintf(logfile,"   |-Reserved ZERO Field   : %d\n",(unsigned int)iphdr->ip_reserved_zero);
	//fprintf(logfile,"   |-Dont Fragment Field   : %d\n",(unsigned int)iphdr->ip_dont_fragment);
	//fprintf(logfile,"   |-More Fragment Field   : %d\n",(unsigned int)iphdr->ip_more_fragment);
	fprintf(logfile,"   |-TTL      : %d\n",(unsigned int)iph->ttl);
	fprintf(logfile,"   |-Protocol : %d\n",(unsigned int)iph->protocol);
	fprintf(logfile,"   |-Checksum : %d\n",ntohs(iph->check));
	fprintf(logfile,"   |-Source IP        : %s\n",inet_ntoa(source.sin_addr));
	fprintf(logfile,"   |-Destination IP   : %s\n",inet_ntoa(dest.sin_addr));
}

void print_udp_packet(unsigned char *Buffer , int Size)
{
	
	unsigned short iphdrlen;
	
	struct iphdr *iph = (struct iphdr *)Buffer;
	iphdrlen = iph->ihl*4;
	
	struct udphdr *udph = (struct udphdr*)(Buffer + iphdrlen);
	
	fprintf(logfile,"\n\n***********************UDP Packet*************************\n");
	
	print_ip_header(Buffer,Size);			
	
	fprintf(logfile,"\nUDP Header\n");
	fprintf(logfile,"   |-Source Port      : %d\n" , ntohs(udph->source));
	fprintf(logfile,"   |-Destination Port : %d\n" , ntohs(udph->dest));
	fprintf(logfile,"   |-UDP Length       : %d\n" , ntohs(udph->len));
	fprintf(logfile,"   |-UDP Checksum     : %d\n" , ntohs(udph->check));
	
	fprintf(logfile,"\n");
	fprintf(logfile,"IP Header\n");
	PrintData(Buffer , iphdrlen);
		
	fprintf(logfile,"UDP Header\n");
	PrintData(Buffer+iphdrlen , sizeof udph);
		
	fprintf(logfile,"Data Payload\n");	
	PrintData(Buffer + iphdrlen + sizeof udph ,( Size - sizeof udph - iph->ihl * 4 ));
	
	fprintf(logfile,"\n###########################################################");
}

void PrintData (unsigned char* data , int Size)
{
	
	for(int i = 0 ; i < Size ; i++)
	{
		if( i != 0 && i % 16 == 0)   //if one line of hex printing is complete...
		{
			fprintf(logfile,"         ");
			for(int j = i - 16 ; j < i ; j++)
			{
				if(data[j] >= 32 && data[j] <= 128)
					fprintf(logfile,"%c",(unsigned char)data[j]); //if its a number or alphabet
				
				else fprintf(logfile,"."); //otherwise print a dot
			}
			fprintf(logfile,"\n");
		} 
		
		if(i % 16 == 0) fprintf(logfile,"   ");
			fprintf(logfile," %02X",(unsigned int)data[i]);
				
		if( i == Size - 1)  //print the last spaces
		{
			for(int j = 0; j < 15 - i % 16; j++) fprintf(logfile,"   "); //extra spaces
			
			fprintf(logfile,"         ");
			
			for(int j = i - i % 16 ; j <= i ; j++)
			{
				if(data[j] >= 32 && data[j] <= 128) fprintf(logfile,"%c",(unsigned char)data[j]);
				else fprintf(logfile,".");
			}
			fprintf(logfile,"\n");
		}
	}
}

