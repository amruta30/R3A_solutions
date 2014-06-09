/*Data is stored in the pcap file as-->  header|data|header|data|header|data......
header is added by packet analyzer software like wireshark and data is the packet data i.e ethernet,tcp,ip information
header info is accessed by struct pcap_pkthdr ,struct pcap_stat header.data is accessed using following ether,ip,tcp structures
for accessing the hex data we need to type cast it as required...
                          
 
//structures defined below are defined for ethernet header,tcp header and ip header....*/


#include <pcap.h>
#include<iostream>
#include<stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include<string.h>
#include<stdlib.h>
#define ETHER_ADDR_LEN 6
using namespace std;
                
                    

 //Ethernet header 
    struct sniff_ethernet {
        u_char ether_dhost[ETHER_ADDR_LEN];
        u_char ether_shost[ETHER_ADDR_LEN];
        u_short ether_type; 
    };

struct sniff_tcp {
        u_short th_sport;   /* source port */
        u_short th_dport;   /* destination port */
        u_int32_t th_seq;       /* sequence number */
        u_int32_t th_ack;       /* acknowledgement number */

        u_char th_offx2;    /* data offset, rsvd */
    #define TH_OFF(th)  (((th)->th_offx2 & 0xf0) >> 4)
        u_char th_flags;
    #define TH_FIN 0x01
    #define TH_SYN 0x02
    #define TH_RST 0x04
    #define TH_PUSH 0x08
    #define TH_ACK 0x10
    #define TH_URG 0x20
    #define TH_ECE 0x40
    #define TH_CWR 0x80
    #define TH_FLAGS (TH_FIN|TH_SYN|TH_RST|TH_ACK|TH_URG|TH_ECE|TH_CWR)
        u_short th_win;     /* window */
        u_short th_sum;     /* checksum */
        u_short th_urp;     /* urgent pointer */
};


struct sniff_ip {
        u_char ip_vhl;      /* version */
        u_char ip_tos;      /* type of service */
        u_short ip_len;     /* total length */
        u_short ip_id;      /* identification */
        u_short ip_off;     /* fragment offset field */

    #define IP_RF 0x8000        /* reserved fragment flag */
    #define IP_DF 0x4000        /* dont fragment flag */
    #define IP_MF 0x2000        /* more fragments flag */
    #define IP_OFFMASK 0x1fff   /* mask for fragmenting bits */
        u_char ip_ttl;      /* time to live */
        u_char ip_p;        /* protocol */
        u_short ip_sum;     /* checksum */
        struct in_addr ip_src;
        struct in_addr ip_dst; /* source and dest address */
    };


    #define IP_HL(ip)       (((ip)->ip_vhl) & 0x0f)
    #define IP_V(ip)        (((ip)->ip_vhl) >> 4)
 
int main()
{
    int j;
    char errbuff[PCAP_ERRBUF_SIZE];          
   const u_char *data;   //for holding packet data
   u_char *ptr;
   int len;
   int packetCount = 0;

 struct pcap_pkthdr *header;
 struct pcap_stat object;
 
    string file = "tcp-ecn-sample.pcap";                    //name of the file.....
     pcap_t * pcap = pcap_open_offline(file.c_str(), errbuff);            //opening the pcap file
 
  //declaring structure objects
   struct sniff_ethernet *ethernet; /* The ethernet header */
   struct sniff_ip *ip; /* The IP header */
   struct sniff_tcp *tcp; /* The TCP header */

    u_int size_ip;
    u_int size_tcp;

//header info....

    while (int returnValue = pcap_next_ex(pcap, &header, &data) >= 0)
    {
       
     printf("no of packets received %u\n",object.ps_recv);
      printf("no of packets dropped %u\n",object.ps_drop);
 
        printf("Packet no # %d\n", ++packetCount);
 
        printf("Bytes on wire: %d\n", header->len);

        printf("Bytes captured:%d\n", header->caplen);
       
        if (header->len != header->caplen)
            printf("Capture size different than packet size: %ld bytes\n", header->len);
 
        printf("Epoch Time: %d:%d seconds\n", header->ts.tv_sec, header->ts.tv_usec);
 
        for (int i=0; (i < header->caplen ) ; i++)
        {
            if ( (i % 16) == 0) printf("\n");
            printf("%.2x ", data[i]);
        }

/**************ETHERNET INFO******************************/
           
    ethernet = (struct sniff_ethernet*)(data);

    if (ntohs (ethernet->ether_type) == 0x0800)     //type field of ethernet frame, for ip it is 0x0800
    {
        printf("\n\nEthernet is an IP packet");
    }else  if (ntohs (ethernet->ether_type) == 0x0806)    //type field of ethernet frame, for arp it is 0x0806
    {
        printf("\n\nEthernet is an ARP packet");
    }else {
        printf("\nEthernet type is not IP");
        exit(1);
    }

        ptr=ethernet->ether_dhost;
        printf("\n\nDESTINATION ADDRESS:");
        for(j=0;j<6;j++)                //mac address is 6 bytess
	{
	 printf("%.2x:",*ptr++);
	}

	ptr = ethernet->ether_shost;
	printf("\n\nSOURCE ADDRESS:");
	for(j=0;j<6;j++)              //mac address is 6 bytes
	{	
	 printf("%.2x:",*ptr++);
	}

       ip = (struct sniff_ip*)(data + 14);     //ip info is stored after ethernet info...hence adding size of ethernet...
                                                               //size of ethernet=14....6+6+2
                                                               //size of etheral frame type=2
        size_ip = IP_HL(ip)*4;                   
        

        /*********TCP HEADER INFORMATION****************************/
        tcp = (struct sniff_tcp*)(data + 14 + size_ip);

        printf("\n\nsrc port: %d dest port: %d \n", ntohs(tcp->th_sport), ntohs(tcp->th_dport));
        printf("\nseq number: %u ack number: %u \n", ntohl(tcp->th_seq), ntohl(tcp->th_ack));

        printf("\nWindow %u \n",tcp->th_win);
        
       /*************************IP HEADER INFO****************/
        char srcname[100];
        strcpy(srcname, inet_ntoa(ip->ip_src));
        char dstname[100];
        strcpy(dstname, inet_ntoa(ip->ip_dst));
        printf("\n\nsrc address: %s dest address: %s \n",srcname, dstname);
        printf("\n\nTYPE OF SERVICE:%d",ip->ip_tos);
        printf("\n\nTIME TO LIVE:%d",ip->ip_ttl);
        printf("\n\nIdentification number:%d",ip->ip_id);
        printf("\n\nTOTAL LENGTH:%x",ip->ip_len);
        printf("\n\n");
    }
}

