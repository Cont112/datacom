#include "Client.hpp"

using namespace std;

Client *Client::instance = NULL;

Client* Client::getInstance(){
    if(instance == NULL){
        instance = new Client();
    }
    return instance;
}

void Client::deleteInstance(){
    if(instance){
        delete instance;
        instance = NULL;
    }
}

Client::Client(){

}

Client::~Client(){
    close(clientSocket);
    deleteInstance();
}

void Client::createSocket(string serverAddress, int port){
    this->serverAddress = serverAddress;
    this->port = port;
    this->clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    if(this->clientSocket < 0){
        perror("Error creating socket");
        exit(1);
    }
    cout << "Socket created" << endl;

    serverAddressStruct.sin_family = AF_INET;
    serverAddressStruct.sin_port = htons(port);
    serverAddressStruct.sin_addr.s_addr = inet_addr(serverAddress.c_str());
}

void Client::connectToServer(){
    if(connect(clientSocket, (struct sockaddr*)&serverAddressStruct, sizeof(serverAddressStruct)) < 0){
        perror("Error connecting to server");
        exit(1);
    }
    cout << "Connected to server" << endl;
}

void Client::sendMessage(string message){
    send(clientSocket, message.c_str(), message.size(), 0);
}

string Client::receiveMessage(){
    char buffer[1024] = {0};
    recv(clientSocket, buffer, 1024, 0);
    return string(buffer);
}
