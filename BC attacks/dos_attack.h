#include "standard.h"

using namespace std;

struct header
{
  unsigned int source;
  unsigned int destination;
  unsigned char placeholder;
  unsigned char protocol;
  unsigned short length;

  struct tcphdr tcp;
};

class dos_attack {
public:
  void Flood(arg arg);
private:
  unsigned short csum (unsigned short *buf, int nwords);
  void Fill(ip *ip, tcphdr *tcp, sockaddr_in *addr, int port);

};
