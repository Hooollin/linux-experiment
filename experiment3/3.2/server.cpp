#include <sys/socket.h>
#include <netinet/in.h>
#include <memory.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#include <iostream>

using namespace std;

class TCPServer{
    public:
        TCPServer(int _port){
            port = _port;
        }

        virtual ~TCPServer(){
        }

        int run(){
            int server = socket(AF_INET, SOCK_STREAM, 0);
            if(server < 0){
                cout << "socket error" << endl;
                return -1;

            }
            sockaddr_in serverAddr;
            memset(&serverAddr, 0, sizeof(sockaddr_in));
            serverAddr.sin_family = AF_INET;
            serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
            serverAddr.sin_port = port;

            serverAddr.sin_port = htons(this->port);
            if(bind(server, (sockaddr*)&serverAddr, sizeof(sockaddr_in)) == -1){
                cout << "bind error" << endl;
                return -1;
            }
            
            if(listen(server, 20) < 0){
                cout << "listen error" << endl;
                return -1;
            }

            sockaddr_in clientAddr;
            socklen_t lenOfclient = sizeof(sockaddr_in);
            int client = accept(server, (sockaddr*)&clientAddr, &lenOfclient);

            if(client < 0){
                cout << "accept error" << endl;
                return -1;
            }
            execute(client);

            close(server);
            close(client);
            return 0;
        }

        virtual void execute(int client){

        }
    private:
        int port;
};

class MyTCPServer: public TCPServer{
    public:
        MyTCPServer(int port):TCPServer(port){}

        void execute(int client) override{
            char buf[1024] = "Hello Hollin";
            write(client, buf, 12);
        }
};

int main(){
    int port = 4000;
    TCPServer *server = new MyTCPServer(port);
    server->run();
    return 0;
}
