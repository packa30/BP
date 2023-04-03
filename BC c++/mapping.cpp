#include "mapping.h"

void mapping::openCon(arg arg){
  int sock;
  struct sockaddr_in addr;
  string message;
  char answer[1024];
  struct hostent *hent;

  if ((sock = socket(AF_INET,SOCK_STREAM,0))<0) { // creation of socket
    close(sock);
    cout<<"socket bad"<<endl;
  }

  bzero(&addr, sizeof(addr));
  if((hent = gethostbyname("kpns-1419655201.us-east-1.elb.amazonaws.com"))==NULL){std::cout << "neexistuje host" << '\n';} // obtaining host trough DNS service
  bcopy(hent->h_addr,&addr.sin_addr.s_addr,hent->h_length);
  addr.sin_family = AF_INET;
  addr.sin_port = htons(7379); // destination port 7379 - port on what could a cloud recive event messages

  if ((connect(sock,(sockaddr*)&addr,sizeof(addr))) != 0) { // TCP three way hand shake connection
    close(sock);
    cout<<"connection bad"<<endl;
  }

  switch (arg.device) { // generating a message that describes an event on choosen device
    case HUB:
      message = "GET /tpns?cmd=event&uid=8KS8M9MFCX3WPR8W111A&event_type="+std::to_string(arg.port)+"&event_time=1538920002 HTTP/1.1\r\nHost: 18.233.77.114\r\nConnection: keep-alive\r\nUser-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/536.5 (KHTML, like Gecko) Chrome/19.0.1084.52 Safari/536.5\r\nAccept: */*\r\nAccept-Encoding: gzip,deflate,sdch\r\nAccept-Language: zh-TW,zh;q=0.8,en-US;q=0.6,en;q=0.4\r\nAccept-Charset: Big5,utf-8;q=0.7,*;q=0.3\r\nPragma: no-cache\r\nCache-Control: no-cache\r\n\r\n";
    break;
    case CAMERA:
      message = "GET /apns/apns.php?cmd=raise_event&uid=FMSNM73XXPEXGS2V111A&event_type="+std::to_string(arg.port)+"&event_time=1554733346 HTTP/1.1\r\nHost: 107.21.39.188\r\nConnection: keep-alive\r\nUser-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/536.5 (KHTML, like Gecko) Chrome/19.0.1084.52 Safari/536.5\r\nAccept: */*\r\nAccept-Encoding: gzip,deflate,sdch\r\nAccept-Language: zh-TW,zh;q=0.8,en-US;q=0.6,en;q=0.4\r\nAccept-Charset: Big5,utf-8;q=0.7,*;q=0.3\r\nPragma: no-cache\r\nCache-Control: no-cache\r\n\r\n";
      break;
    case GATEWAY:
      err(UNKNOWN, -1);
      break;
    default:
      err(UNKNOWN, -1);
      break;
  }

  send(sock,message.c_str(),strlen(message.c_str()),MSG_NOSIGNAL);
  recv(sock,answer,1024,0);
  std::cout << answer << '\n';
  close(sock);
}
