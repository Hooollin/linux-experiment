#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <memory.h>
#include <unistd.h>
#include <iostream>

using namespace std;

int main(){
    int client = socket(AF_INET, SOCK_STREAM, 0);
    if(client < 0){
        cout << "socket error" << endl;
        return -1;
    }

    sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(sockaddr_in));
    serverAddr.sin_family = AF_INET;

    if(inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr) != 1){
        cout << "inet_pton eroor" << endl;
        return -1;
    }

    serverAddr.sin_port = htons(4000);
    if(connect(client, (sockaddr*)&serverAddr, sizeof(serverAddr)) == -1){
        cout << "connect error" << endl;
        return -1;
    }
    
    char buf[100];

    read(client, buf, 12);

    printf("%s", buf);

    close(client);
    return 0;
}
