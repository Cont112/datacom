#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

#define MAX 256
#define PORT 9002
#define ADDRESS INADDR_ANY
#define SA struct sockaddr

void chat(unsigned int network_socket){
  char buffer[MAX];
  int n;

  while(1) {
    bzero(buffer, sizeof(buffer));
    printf("Enter the string : ");
    n = 0;
    while((buffer[n++] = getchar()) != '\n');
    write(network_socket, buffer, sizeof(buffer));
    bzero(buffer, sizeof(buffer));
    read(network_socket, buffer, sizeof(buffer));
    printf("From Server : %s", buffer);
    if((strncmp(buffer, "exit", 4)) == 0) {
      printf("Client Exit...\n");
      break;
    }
  }
}


int main() {

  // CRIA UM SOCKET
  unsigned int network_socket;
  struct sockaddr_in server_address, client_address;

  network_socket = socket(AF_INET, SOCK_STREAM, 0);
  if( network_socket == -1 ) {
    printf("Socket creation failed...\n");
    exit(0);
  }
  else {
    printf("Socket successfully created..\n");
  }

  bzero(&server_address, sizeof(server_address));

  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(PORT);
  server_address.sin_addr.s_addr = htonl(ADDRESS);

  if( connect(network_socket, (SA*)&server_address, sizeof(server_address)) != 0 ) {
    printf("Connection with the server failed...\n");
    exit(0);
  }
  else {
    printf("Connected to the server..\n");
  }

  chat(network_socket);

  // FECHA O SOCKET
  close(network_socket);

  return 0;
}
