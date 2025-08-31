#include "tcpClient.h"
#include "tcpServer.h"
#include <thread> 
int main(){
    std::thread serverThread(TcpServer);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    TCPClient();
    serverThread.join();
    return 0;
}