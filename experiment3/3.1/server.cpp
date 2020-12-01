#include <netinet/in.h>
#include <memory.h>
#include <unistd.h>
#include <iostream>

using namespace std;
int main(){
    int server = socket(AF_INET, SOCK_STREAM, 0);
    if(server < 0){
        cout << "socket error" << endl;
        return 0;
    }

    sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(sockaddr_in));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(4000);

    if(bind(server, (sockaddr*)&serverAddr, sizeof(sockaddr_in)) < 0){
        cout << "bind error" << endl;
        close(server);
        return 0;
    }

    if(listen(server, 20) < 0){
        cout << "listen error" << endl;
        close(server);
        return 0;
    }

    sockaddr_in clientAddr;
    socklen_t lenOfAddr = sizeof(sockaddr_in);
    int connected = accept(server, (sockaddr*)&clientAddr, &lenOfAddr);
    if(connected < 0){
        cout << "accept error" << endl;
        close(server);
        return 0;
    }
    write(connected, "Hello World\n", 12);
    close(server);
    close(connected);
    return 0;
}
