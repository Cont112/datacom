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
    close(clientSocket);
    close(serverSocket);
    if(instance){
        delete instance;
        instance = NULL;
    }
}

Server::Server(){
    hasReceived = true;
}

Server::~Server() {
    deleteInstance();
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


void Server::start() {
    socketCreated = true;
    cout << "Server started" << endl;
    int clientSize = sizeof(clientAddressStruct);
    clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddressStruct, (socklen_t*)&clientSize);
    if (clientSocket < 0) {
        perror("Error accepting connection");
        exit(1);
    }

    fcntl(clientSocket, F_SETFL, O_NONBLOCK); // Tornar o socket do cliente não bloqueante
    cout << "Client connected" << endl;


    unsigned char serverPrivateKey;/* ... obter a public key do servidor ... */;
    GetPrivateKey(&serverPrivateKey);
    privateKey = serverPrivateKey;
    printf("Private ke y%d\n", privateKey);

    unsigned char serverPublicKey[2];
    serverPublicKey[0] = N;
    serverPublicKey[1] = E;
     
    if (send(clientSocket, serverPublicKey, sizeof(serverPublicKey), 0) < 0) {
        perror("Error sending public key");
        // Lidar com o erro
    }
}

void Server::sendMessage(string message){
    send(clientSocket, message.c_str(), message.size(), 0);
}

void Server::sendChar(unsigned char ch){
    send(clientSocket,&ch,1,0);
}


string Server::receiveMessage() {
    char buffer[1024] = {0};
    int bytesReceived = recv(clientSocket, buffer, 1024, 0);

    if (bytesReceived > 0) {
        return string(buffer, bytesReceived);
    } else if (bytesReceived == 0) {
        return ""; // Conexão encerrada
    } else if (errno == EAGAIN || errno == EWOULDBLOCK) {
        return ""; // Não há dados disponíveis
    } else {
        perror("Error receiving message");
        return "";
    }
}

void Server::closeConnection() {
    close(clientSocket);
    clientSocket = -1; // Indicar que não há cliente conectado
}
