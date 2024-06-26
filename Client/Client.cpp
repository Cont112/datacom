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

    unsigned char receivedPublicKey[2];
    int bytesReceived = 0;
    while (bytesReceived <= 0) { // Loop até receber dados
        bytesReceived = recv(clientSocket, receivedPublicKey, sizeof(receivedPublicKey), 0);
        if (bytesReceived < 0 && (errno != EAGAIN && errno != EWOULDBLOCK)) {
            perror("Error receiving public key");
            break;
        }
        std::this_thread::sleep_for(chrono::milliseconds(10)); // Pequeno atraso
    }
    printf("%d %d", receivedPublicKey[0], receivedPublicKey[1]);
    this->N_c = receivedPublicKey[0];
    this->E_c = receivedPublicKey[1];
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

unsigned char Client::receiveChar(){
    unsigned char buffer[2];
    int bytesReceived = recv(clientSocket, buffer, 1, 0);

    if (bytesReceived > 0) {
        cout << "chegaram %d" << bytesReceived << "bytes" << endl;
        return buffer[0]; // Retorna apenas os bytes recebidos
    } else if (bytesReceived == 0) {
        // Conexão encerrada
        return 0;
    } else if (errno == EAGAIN || errno == EWOULDBLOCK) {
        // Não há dados disponíveis
        return 0;
    } else {
        // Erro na recepção
        perror("Error receiving message");
        return 0;
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
