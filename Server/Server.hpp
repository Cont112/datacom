#pragma once

#include <iostream>
#include <string>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include "../stdafx.hpp"
#include <time.h>


using namespace std;

class Server {
private:
    int serverSocket;
    int clientSocket;
    bool socketCreated = false;
    sockaddr_in serverAddressStruct;
    sockaddr_in clientAddressStruct;
    int port;
    bool hasReceived;
    int privateKey;

    Server();
    static Server* instance;

public:
    ~Server();

    static Server* getInstance();
    void deleteInstance();


    void createSocket(int port);
    void start();
    void sendMessage(string message);
    void sendChar(unsigned char ch);
    string receiveMessage();
    void closeConnection();


    bool getScoketCreated() {return socketCreated;}
    void setHasReceived(bool hasReceived) {this->hasReceived = hasReceived;}
    bool getHasReceived() {return hasReceived;}
    int getPrivateKey(){return privateKey;}

    int getClientSocket() {return clientSocket;}
};