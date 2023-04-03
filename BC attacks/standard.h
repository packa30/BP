#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <netdb.h>
#include<netinet/tcp.h>
#include<netinet/ip.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <inttypes.h>
#include <fcntl.h>
#include <chrono>

#define SOCKET_ERR 0
#define SEND_ERR 1
#define NETWORK_ERR 2
#define DEVICE_ERR 3
#define IP_ERR 4
#define UNKNOWN 98
#define OK 99

#define HUB 1
#define CAMERA 2
#define GATEWAY 3

#define DOS 1
#define MAP 2
#define DOSC 3


#ifdef E_FIRST
  #define PROGRAM 1
#elif defined E_SECOND
  #define PROGRAM 2
#elif defined E_THIRD
  #define PROGRAM 3
#else
  #define PROGRAM 1
#endif

using namespace std;

typedef struct  arguments{
  string ip_address;
  int device;
  unsigned int port;
  int timeout;
  int pause;
}arg;

void err(int no, int sock);
arg argParse(int argc, char **argv);
