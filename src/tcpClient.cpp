#include <sys/socket.h>
#include "tcpClient.h"
#include <iostream>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include<cstring>
#define PORTNO 80
#define FATAL_LOG(message) do{\
    std::cerr<<"Closing the code due to error====>"<<message<<'\n'; \
    std::exit(EXIT_FAILURE); \
}while(0);
int TCPClient(){
    const char* hostname = "www.google.com";
    int socketInit =  socket(AF_INET,SOCK_STREAM,0);
    ssize_t sizeOfByteReceived;
    struct hostent* ipaddress = gethostbyname(hostname);
    char bufferToStoreMsg[1024];
    std::string response; 
    struct sockaddr_in socketDetail;
    if (socketInit<0){
        FATAL_LOG("Error while initializing the socket")
    }
    socketDetail.sin_port=htons(PORTNO);
    socketDetail.sin_family=AF_INET;
    socketDetail.sin_addr=*(struct in_addr*)ipaddress->h_addr_list[0];
   
   int connectionStatus = connect(socketInit,(struct sockaddr*)&socketDetail,sizeof(socketDetail));
   if (connectionStatus!=0){
    FATAL_LOG("Connection error")
   }
   const char* requestfromClient ="GET / HTTP/1.1\r\n"
                                    "Host: www.google.com\r\n"
                                    "Connection: close\r\n\r\n";
   int sendStatus = send(socketInit,requestfromClient,strlen(requestfromClient),0);
   if (sendStatus ==-1){
    FATAL_LOG("Sending Data Error");
   }
  
   while ((sizeOfByteReceived = recv(socketInit, bufferToStoreMsg, sizeof(bufferToStoreMsg), 0)) > 0) {
    response.append(bufferToStoreMsg, sizeOfByteReceived);
    std::cout<<response;
}
 if (sizeOfByteReceived==-1){
    FATAL_LOG("Received appraoch failed");
   }
  std::cout<<"Send passed"<<"\n";
  close(socketInit);
    return 0;
}