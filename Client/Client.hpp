#pragma once
#include <iostream>
#include <string>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>

#include <locale.h>

using namespace std;

class Client{
private:
private:
    int clientSocket;
    bool socketCreated = false;
    string serverAddress;
    int port;
    bool hasReceived;
    sockaddr_in serverAddressStruct;

    static Client* instance;
    Client();
    
public:
    ~Client();

    static Client* getInstance();
    void deleteInstance();

    void connectToServer();
    void createSocket(string serverAddress, int port);
    void sendMessage(string message);
    string receiveMessage();
    void closeConnection();

    bool getScoketCreated() {return socketCreated;}
    void setHasReceived(bool hasReceived) {this->hasReceived = hasReceived;}
    bool getHasReceived() {return hasReceived;}

    void setNonBlocking(bool nonBlocking);
    bool checkConnectionStatus();

    int getClientSocket() {return clientSocket;}

    // void str_to_bin(char* str, int str_len, char* bin, int* bin_len);
    // void bin_to_c2b1q(char* bin, int bin_len, char* cod, int* cod_len);
    // int PotModN(int base, int power, int modulus);
    // void encrypt(char* msg, int msg_len, int publicKey, int modulus);

};