#include "Server.hpp"
using namespace std;

Server *Server::instance = NULL;

Server* Server::getInstance(){
    if(instance == NULL){
        instance = new Server();
    }
    return instance;
}

void Server::deleteInstance(){
    if(instance){
        delete instance;
        instance = NULL;
    }
}

Server::Server(){



}

Server::~Server(){
    close(serverSocket);
}

void Server::createSocket(int port){
    this->port = port;

    this->serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(this->serverSocket < 0){
        perror("Error creating socket");
        exit(1);
    }
    serverAddressStruct.sin_family = AF_INET;
    serverAddressStruct.sin_port = htons(port);
    serverAddressStruct.sin_addr.s_addr = INADDR_ANY;

    if(bind(serverSocket, (struct sockaddr*)&serverAddressStruct, sizeof(serverAddressStruct)) < 0){
        perror("Error binding socket");
        exit(1);
    }

    if(listen(serverSocket, 5) < 0){
        perror("Error listening on socket");
        exit(1);
    }
    cout << "Server listening on port " << port << endl;
}


void Server::start(){
    cout << "Server started" << endl;
    int clientSize = sizeof(clientAddressStruct);
    clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddressStruct, (socklen_t*)&clientSize);
    if(clientSocket < 0){
        perror("Error accepting connection");
        exit(1);
    }
    cout << "Client connected" << endl;
}

void Server::sendMessage(string message){
    send(clientSocket, message.c_str(), message.size(), 0);
}

string Server::receiveMessage(){
    char buffer[1024] = {0};
    recv(clientSocket, buffer, 1024, 0);
    return string(buffer);
}

void Server::closeConnection(){
    close(clientSocket);
}