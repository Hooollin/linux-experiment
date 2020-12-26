#include <arpa/inet.h>
#include <memory.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#include "../common/Command.h"
#include "CPluginController.h"
#include "CPluginEnumerator.h"
#include <string>

#include <iostream>

template <typename T> class CTCPServer {
    public:
        CTCPServer(int nServerPort, int nLengthOfQueueOfListen = 100,
                const char *strBoundIP = NULL) {
            m_nServerPort = nServerPort;
            m_nLengthOfQueueOfListen = nLengthOfQueueOfListen;

            if (NULL == strBoundIP) {
                m_strBoundIP = NULL;
            } else {
                int length = strlen(strBoundIP);
                m_strBoundIP = new char[length + 1];
                memcpy(m_strBoundIP, strBoundIP, length + 1);
            }
        }

        virtual ~CTCPServer() {
            if (m_strBoundIP != NULL) {
                delete[] m_strBoundIP;
            }
        }

    public:
        int Run() {
            int nListenSocket = socket(AF_INET, SOCK_STREAM, 0);
            if (-1 == nListenSocket) {
                std::cout << "socket error" << std::endl;
                return -1;
            }

            sockaddr_in ServerAddress;
            memset(&ServerAddress, 0, sizeof(sockaddr_in));
            ServerAddress.sin_family = AF_INET;

            if (NULL == m_strBoundIP) {
                ServerAddress.sin_addr.s_addr = htonl(INADDR_ANY);
            } else {
                if (inet_pton(AF_INET, m_strBoundIP, &ServerAddress.sin_addr) != 1) {
                    std::cout << "inet_pton error" << std::endl;
                    close(nListenSocket);
                    return -1;
                }
            }

            ServerAddress.sin_port = htons(m_nServerPort);

            if (bind(nListenSocket, (sockaddr *)&ServerAddress, sizeof(sockaddr_in)) ==
                    -1) {
                std::cout << "bind error" << std::endl;
                close(nListenSocket);
                return -1;
            }

            if (listen(nListenSocket, m_nLengthOfQueueOfListen) == -1) {
                std::cout << "listen error" << std::endl;
                close(nListenSocket);
                return -1;
            }

            sockaddr_in ClientAddress;
            socklen_t LengthOfClientAddress = sizeof(sockaddr_in);
            while (true) {
                // 一直等待用户的请求
                std::cout << "waiting for client..." << std::endl;
                int nConnectedSocket = accept(nListenSocket, (sockaddr *)&ClientAddress,
                        &LengthOfClientAddress);
                if (-1 == nConnectedSocket) {
                    std::cout << "accept error" << std::endl;
                    close(nListenSocket);
                    return -1;
                }
                T *pT = static_cast<T *>(this);
                pT->ServerFunction(nConnectedSocket, nListenSocket);
                close(nConnectedSocket);
            }
            close(nListenSocket);
            return 0;
        }

    private:
        void ServerFunction(int nConnectedSocket, int nListenSocket) {}

    private:
        int m_nServerPort;
        char *m_strBoundIP;
        int m_nLengthOfQueueOfListen;
};

class CMyTCPServer : public CTCPServer<CMyTCPServer> {
    public:
        CMyTCPServer(int nServerPort, int nLengthOfQueueOfListen = 100,
                const char *strBoundIP = NULL)
            : CTCPServer<CMyTCPServer>(nServerPort, nLengthOfQueueOfListen,
                    strBoundIP) {}

        virtual ~CMyTCPServer() {}

        void ServerFunction(int nConnectedSocket, int nListenSocket) {
            // 序列化的数据读到buf里面
            char buf[MAX_LEN];
            size_t size = read(nConnectedSocket, buf, MAX_LEN);

            // 存一下buf
            fp = fopen("input", "w");
            write(fileno(fp), buf, size);

            // 反序列化
            Command *cmd = new Command();
            cmd->deserialize("input");
            remove("input");

            int functionID = cmd->getEncryptionFunction();
            string content = cmd->getFileContent();

            // todo: 根据加密类型执行加密过程
            CPluginController pc;

            pc.InitializeController();

            if (functionID == -1) {
                content = pc.ProcessHelp();
            } else {
                content = pc.ProcessRequest(functionID, content);
            }

            // 把结果写回给客户
            write(nConnectedSocket, content.c_str(), content.size());
        }

    private:
        // 最长接受(传送)大小为1M的序列化文件
        const static int MAX_LEN = 1024 * 1024;
        FILE *fp;
};

int main() {
    CMyTCPServer myserver(4000);
    myserver.Run();
    return 0;
}
