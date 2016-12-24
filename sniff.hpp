#ifndef SNIFF_H
#define SNIFF_H

#define ETHER_ADDR_LEN	6
#define IP_ADDR_LEN	4
#define LINE_LEN 16
#define MAX_ADDR_LEN 16

/*Ethernet header defined*/
typedef struct ether_header {
    unsigned char ether_dhost[ETHER_ADDR_LEN];		/* Destination host address */
    unsigned char ether_shost[ETHER_ADDR_LEN];		/* Source host address */
	unsigned short ether_type;			/* IP? ARP? RARP? etc */
}sniff_ethernet;

// 4 bytes IP address
typedef struct ip_address{
    unsigned char byte1;
    unsigned char byte2;
    unsigned char byte3;
    unsigned char byte4;
}ip_address;

/*IP header defined*/
typedef struct ip_header {
    unsigned char ip_vhl;				/* version */
    unsigned char ip_tos;				/* type of service */
	unsigned short ip_len;				/* total length */
	unsigned short ip_id;				/* identification */
	unsigned short ip_off;				/* fragment offset field */
    unsigned char ip_ttl;				/* time to live */
    unsigned char ip_p;                 /* portocol */
	unsigned short ip_sum;				/* checksum */
    ip_address saddr;                   /* Source address */
    ip_address daddr;                   /* Destination address */
    //unsigned int ip_src,ip_dst;		/* source and dest address */
}sniff_ip;


/*TCP header defined*/
typedef struct tcp_header {
	unsigned short th_sport;
	unsigned short th_dport;
	unsigned int th_seq;		/* sequence number */
	unsigned int th_ack;		/* acknowledgement number */
    unsigned char th_hlen;
    unsigned char th_flags;
	unsigned short th_win;		/* windows */
	unsigned short th_sum;		/* checksum */
	unsigned short th_urp;		/* urgent_pointer */
}sniff_tcp;

/*UDP header defined*/
typedef struct udp_header {
	unsigned short uh_sport;		
	unsigned short uh_dport;		
	unsigned short uh_dlen;		/* datalen */
	unsigned short uh_sum;			/* checksum */ 
}sniff_udp;

/*ICMP header defined*/
typedef struct icmp_header {
    unsigned char ich_type;		/* icmp type */
    unsigned char ich_code;		/* icmp code */
	unsigned short ich_sum;		/* checksum */
	unsigned short ich_id;			/* identification */
	unsigned short ich_seq;		/* sequence */
	unsigned long  ich_ts;			/* timestamp */
}sniff_icmp;

/*ARP header defined*/
typedef struct arp_header {
	unsigned short arp_hwt;				/* hardware_type */
	unsigned short arp_pt;					/* protocol_type */
    unsigned char arp_hwl;					/* hardware_length */
    unsigned char arp_pl;					/* protocol_length */
	unsigned short arp_opecode;			/* operation_code */
    unsigned char arp_src_ether_addr[ETHER_ADDR_LEN];	/* source_ethernet_address */
    unsigned char arp_source_ip_addr[IP_ADDR_LEN];		/* source_ip_address */
    unsigned char arp_dest_ether_addr[ETHER_ADDR_LEN];	/* destination_ethernet_address */
    unsigned char arp_dest_ip_addr[IP_ADDR_LEN];		/* destination_ip_address */
}sniff_arp;

#endif
