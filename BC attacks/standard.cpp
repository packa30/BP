#include "standard.h"

void err(int no, int sock){
  switch (no) {
    case SOCKET_ERR:
      std::cout << "Unable to open socket" << '\n';
      break;
    case SEND_ERR:
      std::cout << "Unable to send data" << '\n';
      break;
    case NETWORK_ERR:
      std::cout << "Network error" << '\n';
      break;
    case DEVICE_ERR:
      std::cout << "Wrong device arguments" << '\n';
      break;
    case IP_ERR:
      std::cout << "Wrong IP address" << '\n';
      break;
    case UNKNOWN:
      std::cout << "Unknown argument" << '\n';
    default:
      break;
  }
  if(no <= UNKNOWN){
    if(sock != -1){
      close(sock);
    }
    exit(1);
  }
}

arg argParse(int argc, char **argv){
  arg args;// = (arg)malloc(sizeof(arg));
  // args.device = UNKNOWN;
  // args.port=80;
  // args.timeout=1;
  // args.pause=1;
  // args.ip_address = " ";
  int c;
  while ((c=getopt(argc,argv,"d:i:p:u:t:l:")) != -1){
    switch (c) {
      case 'd':
        if ((atoi(optarg) & 3) != 0 && (atoi(optarg) <= 3)) {
          args.device = atoi(optarg);
          break;
        }
        err(DEVICE_ERR, -1);
      case 'i':
        args.ip_address=optarg;
        break;
      case 'p':
        args.port=atoi(optarg);
        break;
      case 't':
        args.timeout=atoi(optarg);
        break;
      case 'l':
        args.pause=atoi(optarg);
        break;
      default:
        err(UNKNOWN, -1);
    }
  }
  return args;
}
