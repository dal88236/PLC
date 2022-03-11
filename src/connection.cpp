#include "connection.h"
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sstream>
#include <iomanip>

using namespace std;

SocketConnection::SocketConnection() : _domain(AF_INET), _type(SOCK_STREAM), _protocol(0), _connectionStatus(false),
                                       _port(8192), PCST("FF"), ENTST("00"), STNO("00")
{
    _socketfd = socket(_domain, _type, _protocol);

    if (_socketfd == -1)
    {
        cerr << "Fail to create a socket." << endl;
    }

    _clientInfo.sin_family = AF_INET;
    _clientInfo.sin_addr.s_addr = INADDR_ANY;
    _clientInfo.sin_port = htons(_port);
}

SocketConnection::SocketConnection(int domain, int type, int protocol) : 
    _domain(domain), _type(type), _protocol(protocol), _connectionStatus(false), PCST("FF"), ENTST("00"), STNO("00")
{
    _socketfd = socket(_domain, _type, _protocol);

    if (_socketfd == -1)
    {
        cerr << "Fail to create a socket." << endl;
        _connectionStatus = false;
    }

    _clientInfo.sin_family = AF_INET;
    _clientInfo.sin_addr.s_addr = INADDR_ANY;
    _clientInfo.sin_port = htons(8192);
    bind(_socketfd, (struct sockaddr *)&_clientInfo, sizeof(_clientInfo));
    listen(_socketfd,5);
}

SocketConnection::SocketConnection(int domain, int type, int protocol, int port) : 
    _domain(domain), _type(type), _protocol(protocol), _connectionStatus(false), _port(port), 
    PCST("FF"), ENTST("00"), STNO("00")
{
    _socketfd = socket(_domain, _type, _protocol);

    if (_socketfd == -1)
    {
        cerr << "Fail to create a socket." << endl;
        _connectionStatus = false;
    }

    _clientInfo.sin_family = AF_INET;
    _clientInfo.sin_addr.s_addr = INADDR_ANY;
    _clientInfo.sin_port = htons(_port);
    bind(_socketfd, (struct sockaddr *)&_clientInfo, sizeof(_clientInfo));
    listen(_socketfd,5);
}

SocketConnection::~SocketConnection()
{
    cout << "Closing socket..." << endl;
    close(_socketfd);
}

void SocketConnection::setIP(std::string IPAddress)
{
    const char* IPAddress_cstr = IPAddress.c_str();
    _clientInfo.sin_addr.s_addr = inet_addr(IPAddress_cstr);
    delete IPAddress_cstr;
}

void SocketConnection::setIP(const char* IPAddress)
{
    _clientInfo.sin_addr.s_addr = inet_addr(IPAddress);
}

void SocketConnection::setPort(int port)
{
    _port = port;
    _clientInfo.sin_port = htons(_port);
}

bool SocketConnection::connectPLC()
{
    int connection = connect(_socketfd, (struct sockaddr*)&_clientInfo, sizeof(_clientInfo));

    if (connection < 0)
        cerr << "Failed to build connection to: " << inet_ntoa(_clientInfo.sin_addr) << endl;
    else
        cout << "Connection built" << endl;

    _connectionStatus = (connection < 0) ? false : true;
}

void SocketConnection::writeToPLC(char* message)
{
    if (!_connectionStatus)
        return;

    int len = strlen(message);
    BYTE arr[len];
    // Hardcoded DREAD value
    string DREAD("D0000");
    string result = PLCTELNET(DREAD, PCST, ENTST, inet_ntoa(*((struct in_addr*)&_clientInfo.sin_addr.s_addr)), to_string(_port), "0401", message, STNO);
    // stringToByteArray(message, arr);
    // try
    // {
    //     int result = send(_socketfd, message, strlen(message), 0);
        
    //     if (result < 0)
    //         cerr << "Failed to send message" << endl;
    //     else
    //         cout << "Data sent" << endl;
    // }
    // catch(...)
    // {
    //     cerr << "Broken Pipeline" << endl;
    // }
}

char* SocketConnection::readFromPLC()
{
    char* reply;
    int result = read(_socketfd, reply, 2000);

    if (result < 0)
        cerr << "Unable to receive data from: " << inet_ntoa(_clientInfo.sin_addr) << endl;

    return reply;
}

void SocketConnection::stringToByteArray(char* input, BYTE* output)
///
/// Convert char array to byte array, code stolen from https://www.includehelp.com/c/convert-ascii-string-to-byte-array-in-c.aspx
///
{
    int loop = 0;
    int i = 0;
    char inputArray[strlen(input)];
    BYTE outputArray[strlen((char*)output)];
    strcpy(inputArray, input);

    while(inputArray[loop] != '\0')
    {
        outputArray[i++] = inputArray[loop++];
    }

    output = outputArray;
}

string SocketConnection::PLCTELNET(string DREAD, string PST, string EST, string IP, 
                                   string Port, string COMMAND, string WRITEDATA, string STNO)
{
    BYTE asciiPLCRByteReceives[256];
    int receiveLength = 0;
    BYTE receiveBytes[4];
    string PLCRs;
    string PLCRNs;
    string DREADs = "";

    // Check the correctness of input's format
    if (PST.length() != 2 && EST.length() != 2)
    {
        cerr << "Wrong format. Length of PST and EST must be 2" << endl;
        return "";
    }

    for (int i1 = 0; i1 < DREAD.length(); i1++)
    {
        if (isdigit(DREAD[i1]))
            DREADs += DREAD[i1];
    }

    if (DREADs.length() != 4)
        cerr << "Input format of PLC number must be Dxxxx, e.g. D0001" << endl;

    // Write MCPROTOCOL code
    if (COMMAND == "0401")
    {
        PLCRs = "5000" + EST + PST + "03FF" + STNO + "0018" + "0000" + COMMAND + "0000" + "D*00" + DREADs + "0001" + WRITEDATA;
        cout << "PLCRs: " << PLCRs << endl;
    }
    else
    {
        int WRITEDATAs = stoi(WRITEDATA);
        stringstream ss;
        ss << hex << WRITEDATAs;  
        string WRITEDATAss(ss.str());
        string padLeft = "0000";
        string WRITEDATAsss = WRITEDATAss.insert(0, padLeft);
        PLCRs = "5000" + EST + PST + "03FF" + STNO + "001C" + "0000" + COMMAND + "0000" + "D*00" + DREADs + "0001" + WRITEDATAsss;
    }

    //BYTE* asciiPLCRbytes;
    //stringToByteArray((char*)PLCRs.c_str(), asciiPLCRbytes);
    
    // Connection
    try
    {
        //char* message = reinterpret_cast<char*>(asciiPLCRbytes);
        //printf("Message in bytes: %s\n", message);
        int result = send(_socketfd, PLCRs.c_str(), strlen(PLCRs.c_str()), 0);
        
        if (result < 0)
            cerr << "Failed to send message" << endl;
        else
            cout << "Data sent" << endl;
    
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    char* reply = readFromPLC();
    BYTE* replyBytes = reinterpret_cast<BYTE*>(reply);
    
    for (int i4 = 0; i4 < 256; i4++)
    {
        if (replyBytes[i4] != 0)
            receiveLength++;
        asciiPLCRByteReceives[i4] = replyBytes[i4];
    }
    
    for (int i5 = receiveLength - 4; i5 < receiveLength; i5++)
        receiveBytes[i5 - receiveLength + 4] = asciiPLCRByteReceives[i5];

    // Convert the received data to hex string
    string receiveData = hexStr(receiveBytes, receiveLength);

    // Convert hex string to decimal int
    int receiveDataDec = stoul(receiveData, nullptr, 16);

    // Convert int to string
    PLCRNs = to_string(receiveDataDec);

    return PLCRNs;
}

std::string SocketConnection::hexStr(BYTE* data, int len)
{
    stringstream ss;
    ss << hex;

    for (int i = 0; i < len; i++)
        ss << setw(2) << setfill('0') << (int)data[i];

    return ss.str();
}