#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int server_socket;
int client_socket;

struct sockaddr_in server_address;
struct sockaddr_in client_address;

void init_server(){
  // CRIA UM SOCKET
  server_socket = socket(AF_INET, SOCK_STREAM, 0);

  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(9002);
  server_address.sin_addr.s_addr = INADDR_ANY; //IP ADDRESS

  if(!bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address))){
      printf("Binded succesfully!\n");
  }

}
void send_message(char* message){
  char server_message[256];
  strcpy(server_message, message);

  send(client_socket, server_message, sizeof(server_message), 0);
}

int main() {

  init_server();

  char client_message[255];
  scanf("%[^\n]",client_message);

  listen(server_socket, 5);

  unsigned int len = sizeof(client_address);
  client_socket = accept(server_socket, (struct sockaddr*)&client_address, &len);

  // ENVIA MENSAGEM
  
  send_message(client_message);

  recv(client_socket, &client_message, sizeof(client_message), 0);
  printf("Client: %s\n", client_message);
  // FECHA O SOCKET
  close(server_socket);

  return 0;
}
