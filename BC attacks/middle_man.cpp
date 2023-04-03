#include "middle_man.h"

void middle_man::openCon(arg arg){
  int sock;
  struct sockaddr_in addr;
  string message;
  char answer[1024];
  struct hostent *hent;

  if ((sock = socket(AF_INET,SOCK_STREAM,0))<0) {
    close(sock);
    cout<<"socket bad"<<endl;
  }

  bzero(&addr, sizeof(addr));
  if((hent = gethostbyname("kpns-1419655201.us-east-1.elb.amazonaws.com"))==NULL){std::cout << "neexistuje host" << '\n';}
  bcopy(hent->h_addr,&addr.sin_addr.s_addr,hent->h_length);
  addr.sin_family = AF_INET;
  addr.sin_port = htons(7379);

  //inet_aton("push.iotplatform.com",&addr.sin_addr);

  if ((connect(sock,(sockaddr*)&addr,sizeof(addr))) != 0) {
    close(sock);
    cout<<"connection bad"<<endl;
  }

  //message = "GET /tpns?cmd=device&uid=8KS8M9MFCX3WPR8W111A HTTP/1.1\r\nHost: 18.233.77.114\r\nConnection: keep-alive\r\nUser-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/536.5 (KHTML, like Gecko) Chrome/19.0.1084.52 Safari/536.5\r\nAccept: */*\r\nAccept-Encoding: gzip,deflate,sdch\r\nAccept-Language: zh-TW,zh;q=0.8,en-US;q=0.6,en;q=0.4\r\nAccept-Charset: Big5,utf-8;q=0.7,*;q=0.3\r\nPragma: no-cache\r\nCache-Control: no-cache\r\n\r\n";
  //while (true) {
  //send(sock,message.c_str(),strlen(message.c_str()),MSG_NOSIGNAL);

  //recv(sock,answer,1024,0);
  //cout<<answer<<endl;
  message = "GET /tpns?cmd=event&uid=8KS8M9MFCX3WPR8W111A&event_type=204&event_time=1538920002 HTTP/1.1\r\nHost: 18.233.77.114\r\nConnection: keep-alive\r\nUser-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/536.5 (KHTML, like Gecko) Chrome/19.0.1084.52 Safari/536.5\r\nAccept: */*\r\nAccept-Encoding: gzip,deflate,sdch\r\nAccept-Language: zh-TW,zh;q=0.8,en-US;q=0.6,en;q=0.4\r\nAccept-Charset: Big5,utf-8;q=0.7,*;q=0.3\r\nPragma: no-cache\r\nCache-Control: no-cache\r\n\r\n";
int i = 1;
while (i<=1000) {
  send(sock,message.c_str(),strlen(message.c_str()),MSG_NOSIGNAL);
  i++;
  recv(sock,answer,1024,0);
  std::cout << answer << '\n';
}
  //while (true) {


  //}

  while(recv(sock,answer,1024,0) > 0)
  cout<<answer<<endl;

  close(sock);
}
