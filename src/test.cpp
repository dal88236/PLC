#include "connection.h"
#include <iostream>
#include <string.h>

using namespace std;

int main()
{
    SocketConnection connection;
    connection.setIP("192.168.16.2");
    connection.connectPLC();

    connection.writeToPLC("1");

    return 0;
}