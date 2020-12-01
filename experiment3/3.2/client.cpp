#include <sys/socket.h>
#include <netinet/in.h>
#include <memory.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#include <iostream>

using namespace std;

class TCPClient{
    public:
        TCPClient(const char *_ip, int _port){
            port = _port;
            int len = 0;
            while(*(_ip + len)) len += 1;
            ip = new char[len + 1];
            strcpy(ip, _ip);
        }

        virtual ~TCPClient(){
            delete [] ip;
        }

        int run(){
            int client = socket(AF_INET, SOCK_STREAM, 0);
            if(client < 0){
                cout << "socket error" << endl;
                return -1;
            }

            sockaddr_in serverAddr;
            memset(&serverAddr, 0, sizeof(sockaddr_in));
            serverAddr.sin_family = AF_INET;

            if(inet_pton(AF_INET, this->ip, &serverAddr.sin_addr) != 1){
                cout << "inet_pton eroor" << endl;
                return -1;
            }

            serverAddr.sin_port = htons(this->port);
            if(connect(client, (sockaddr*)&serverAddr, sizeof(serverAddr)) == -1){
                cout << "connect error" << endl;
                return -1;
            }
            execute(client);

            close(client);
        }
        virtual void execute(int client){

        }
    private:
        char* ip;
        int port;
};

class MyTCPClient : public TCPClient{
    public:
        MyTCPClient(char *ip, int port):TCPClient(ip, port){

        }

        void execute(int client) override{
            char buf[1024];
            read(client, buf, 12);
            printf("%s", buf);
        }
};

int main(){
    char* ip = "127.0.0.1";
    int port = 4000;
    TCPClient *client = new MyTCPClient(ip, port);
    client->run();
    return 0;
}
