#include "standard.h"

void err(int no, int sock){ // closing program due to error
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
      std::cout << "Wrong arguments" << '\n';
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
  int c;
  while ((c=getopt(argc,argv,"d:i:p:u:t:l:")) != -1){ // parsing input arguments
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

  switch (PROGRAM) { // handling wrong argument input
    case DOS:
      if(args.device == 0 && args.ip_address.empty()){
        err(UNKNOWN, -1);
      }
      if(args.port == 0 ){
        err(UNKNOWN, -1);
      }
      break;
    case MAP:
      if(args.port == 0 || args.device == 0){
        err(UNKNOWN, -1);
      }
      break;
    case DOSC:
      if(args.pause == 0 || args.timeout == 0 || args.device == 0){
        err(UNKNOWN, -1);
      }
      if(args.ip_address.empty()){
        switch (arg.device) {
          case HUB:
            args.ip_address = "192.168.1.131";
            break;
          case CAMERA:
            args.ip_address = "192.168.1.133";
            break;
          default:
            err(UNKNOWN, -1);
          break;
        }
      }
      args.port=80; // connections to be made for HTTP port 80
      break;
    default:
      break;
  }



  return args;
}
