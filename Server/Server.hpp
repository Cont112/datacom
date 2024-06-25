#pragma once

#include <iostream>
#include <string>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <unistd.h>

using namespace std;

class Server {
private:
    int serverSocket;
    int clientSocket;
    sockaddr_in serverAddressStruct;
    sockaddr_in clientAddressStruct;
    int port;

public:
    Server(int port);
    ~Server();

    void start();
    void sendMessage(string message);
    string receiveMessage();
    void closeConnection();
};