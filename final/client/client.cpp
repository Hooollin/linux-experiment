#include <sys/socket.h>
#include <netinet/in.h>
#include <memory.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#include <string>
#include <fstream>
#include "../common/Command.h"

#include <iostream>

template<typename T>
class CTCPClient
{
    public:
        CTCPClient(int nServerPort, const char *strServerIP)
        {
            m_nServerPort = nServerPort;

            int nlength = strlen(strServerIP);
            m_strServerIP = new char [nlength + 1];
            strcpy(m_strServerIP, strServerIP);
        }

        virtual ~CTCPClient()
        {
            delete [] m_strServerIP;
        }

    public:
        int Run(int encryptionFunction, const char *p)
        {
            int nClientSocket = socket(AF_INET, SOCK_STREAM, 0);
            if(-1 == nClientSocket)
            {
                std::cout << "socket error" << std::endl;
                return -1;
            }

            sockaddr_in ServerAddress;
            memset(&ServerAddress, 0, sizeof(sockaddr_in));
            ServerAddress.sin_family = AF_INET;
            if(inet_pton(AF_INET, m_strServerIP, &ServerAddress.sin_addr) != 1)
            {
                std::cout << "inet_pton error" << std::endl;
                close(nClientSocket);
                return -1;
            }

            ServerAddress.sin_port = htons(m_nServerPort);

            if(connect(nClientSocket, (sockaddr*)&ServerAddress, sizeof(ServerAddress)) == -1)
            {
                std::cout << "connect error" << std::endl;
                close(nClientSocket);
                return -1;
            }

            T *pT = static_cast<T*>(this);
            pT->ClientFunction(nClientSocket, encryptionFunction, p);

            close(nClientSocket);

            return 0;
        }

        void ClientFunction(int nConnectedSocket, int encryptionFunction, const char *p){
        }

    private:
        int m_nServerPort;
        char *m_strServerIP;
};

class CMyTCPClient : public CTCPClient<CMyTCPClient>
{
    public:
        CMyTCPClient(int nServerPort, const char *strServerIP) : CTCPClient<CMyTCPClient>(nServerPort, strServerIP)
    {
    }

        virtual ~CMyTCPClient()
        {
        }

        void ClientFunction(int nConnectedSocket, int encryptionFunction, const char *p){
            string line;
            if(encryptionFunction == -1 && strcmp(p, "help") == 0){
                Command *cmd = new Command(encryptionFunction, "");
                cmd->serialize("serialized_data");
                ifstream ifserialized("serialized_data");
                string serializedContent;
                while(std::getline(ifserialized, line)){
                    serializedContent += line;
                    serializedContent += '\n';
                }
                write(nConnectedSocket, serializedContent.c_str(), serializedContent.size());
                char buf[MAX_LEN];
                int len = read(nConnectedSocket, buf, MAX_LEN);
                for(int i = 0; i < len; i++){
                    cout << buf[i];
                }
                ifserialized.close();
                cout << endl;
                return;
            }
            ifstream ifsraw(p);
            // 调用远程方法
            string fileContent;
            while(std::getline(ifsraw, line)){
                fileContent += line;
                fileContent += '\n';
            }
            Command *cmd = new Command(encryptionFunction, fileContent);
            cmd->serialize("serialized_data");

            ifstream ifserialized("serialized_data");
            string serializedContent;
            while(std::getline(ifserialized, line)){
                serializedContent += line;
                serializedContent += '\n';
            }
            // 演示用，不需要删除
            //remove("serialized_data");

            write(nConnectedSocket, serializedContent.c_str(), serializedContent.size());

            char buf[MAX_LEN];
            int len = read(nConnectedSocket, buf, MAX_LEN);
            ofstream ofs(p);
            ofs.write(buf, len);

            ifserialized.close();
            ofs.close();
            close(nConnectedSocket);
        }

    private:
        const static int MAX_LEN = 1024 * 1024;
};

int main(int argc, char *argv[]){
    CMyTCPClient client(4000, "127.0.0.1");
    int functionType = -1;
    char *file = strdup("help");
    if (argc == 2){
        if(strcmp(argv[1], "help") == 0){
            client.Run(functionType, file);   
        }else{
            cerr << "too few arguments" << endl;
        }
        return 0;
    }
    if(argc < 2){
        std::cerr << "too few arguments" << std::endl;
        return -1;
    }
    if(argc > 3){
        std::cerr << "too many arguments" << std::endl;
        return -1;
    }
    if(argc == 3){
        functionType = atoi(argv[1]);
        file = argv[2];
    }
    client.Run(functionType, file);
    return 0;
}

