#pragma once
#include <iostream>
#include <string>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#include <locale.h>

using namespace std;

class Client{
private:
private:
    int clientSocket;
    string serverAddress;
    int port;
    sockaddr_in serverAddressStruct;

public:
    Client(string serverAddress, int port);
    ~Client();

    void connectToServer();
    void sendMessage(string message);
    string receiveMessage();
    void closeConnection();

    // void str_to_bin(char* str, int str_len, char* bin, int* bin_len);
    // void bin_to_c2b1q(char* bin, int bin_len, char* cod, int* cod_len);
    // int PotModN(int base, int power, int modulus);
    // void encrypt(char* msg, int msg_len, int publicKey, int modulus);

};