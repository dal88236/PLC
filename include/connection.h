#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string>

typedef unsigned char BYTE;

class SocketConnection
{
public:
    SocketConnection();
    SocketConnection(int domain, int type, int protocol);
    SocketConnection(int domain, int type, int protocol, int port);
    ~SocketConnection();

    void setIP(std::string IPAddress);
    void setIP(const char* IPAddress);
    void setPort(int port);
    void sendRequest(int request);
    bool connectPLC();
    void writeToPLC(char* message);
    char* readFromPLC();
    void stringToByteArray(char* input, BYTE* output);

private:
    // Variables
    sockaddr_in _clientInfo;
    int _domain;
    int _type;
    int _protocol;
    int _socketfd;
    int _port;
    bool _connectionStatus;
    std::string PCST;
    std::string ENTST;
    std::string STNO;

    int convertToASCII(std::string input);
    std::string hexStr(BYTE* data, int len);
    std::string PLCTELNET(std::string DREAD, std::string PST, std::string EST, std::string IP, 
                          std::string Port, std::string COMMAND, std::string WRITEDATA, std::string STNO);
};