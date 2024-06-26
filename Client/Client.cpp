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
    hasReceived = true;

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
    setNonBlocking(true);

    socketCreated = true;
}

void Client::connectToServer(){
    if (connect(clientSocket, (struct sockaddr*)&serverAddressStruct, sizeof(serverAddressStruct)) < 0) {
        if (errno != EINPROGRESS) {
            perror("Error connecting to server");
            exit(1);
        }
    }

    while (!checkConnectionStatus()) { 
        // Aguardar até que a conexão seja estabelecida ou ocorra um erro
    }
    if (checkConnectionStatus()) {
         cout << "Conectado ao servidor" << endl;
    }
}

void Client::sendMessage(string message){
    send(clientSocket, message.c_str(), message.size(), 0);
}

void Client::closeConnection(){
    close(clientSocket);
}

string Client::receiveMessage(){
    char buffer[1024] = {0};
    int bytesReceived = recv(clientSocket, buffer, 1024, 0);

    if (bytesReceived > 0) {
        return string(buffer, bytesReceived); // Retorna apenas os bytes recebidos
    } else if (bytesReceived == 0) {
        // Conexão encerrada
        return "";
    } else if (errno == EAGAIN || errno == EWOULDBLOCK) {
        // Não há dados disponíveis
        return "";
    } else {
        // Erro na recepção
        perror("Error receiving message");
        return "";
    }
}

void Client::setNonBlocking(bool nonBlocking) {
    int flags = fcntl(clientSocket, F_GETFL, 0);
    if (nonBlocking) {
        fcntl(clientSocket, F_SETFL, flags | O_NONBLOCK);
    } else {
        fcntl(clientSocket, F_SETFL, flags & ~O_NONBLOCK);
    }
}

bool Client::checkConnectionStatus() {
    fd_set writefds;
    FD_ZERO(&writefds);
    FD_SET(clientSocket, &writefds);

    struct timeval timeout = {0, 100000}; // 100 ms de timeout
    int ready = select(clientSocket + 1, NULL, &writefds, NULL, &timeout);
    if (ready > 0 && FD_ISSET(clientSocket, &writefds)) {
        int error = 0;
        socklen_t len = sizeof(error);
        if (getsockopt(clientSocket, SOL_SOCKET, SO_ERROR, &error, &len) == 0) {
            return error == 0; // Retorna true se a conexão foi estabelecida
        }
    }
    return false; // Conexão ainda em progresso ou erro
}
