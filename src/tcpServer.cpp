#include<sys/socket.h>
#include<iostream>
#include<netinet/in.h>
#include<cstring>
#include<unistd.h>
#define PORT 8080
#define LOG_FATAL(msg) do{\
    std::cerr<<"Error in the code due to ===>"<<msg;\
    std::exit(EXIT_FAILURE);\
}while(0);
int TcpServer(){
    const char * messageFromserver = "hello from server S i am succefully connected to you";
    char maxBufferForData[512];
    int socketInit = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in socketAddr;
    struct sockaddr_in clientDetail;
    ssize_t sizeofByteSend;
    socklen_t cleintAddlen = sizeof(clientDetail);
    if (socketInit==-1){
        LOG_FATAL("Error while init socket");
    }
    socketAddr.sin_family=AF_INET;
    socketAddr.sin_port = htons(PORT);
    socketAddr.sin_addr.s_addr=INADDR_ANY;

    int bindStatus = bind(socketInit,(struct sockaddr*)&socketAddr,sizeof(socketAddr));
    if (bindStatus==-1){
        LOG_FATAL("Connection while bind address");
    }
    int listenStatus = listen(socketInit,sizeof(maxBufferForData));
    if (listenStatus==-1){
        LOG_FATAL("Error while lsitening the code");
    }
    int clientSocket = accept(socketInit,(struct sockaddr*)&clientDetail,&cleintAddlen);
    if (clientSocket==-1){
        LOG_FATAL("Error while accepting the connection");
    }
    sizeofByteSend = send(clientSocket,messageFromserver,strlen(messageFromserver),0);
    if (sizeofByteSend==-1){
        LOG_FATAL("Error in sedning the resposne");
    }
    close(clientSocket);
    close(socketInit);

return 0;
}