#include <stdio.h>
#include <arpa/inet.h>
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

void chat(unsigned int client_socket){
    char buff[MAX];
    int n;
    while(1){
        bzero(buff, MAX);
        read(client_socket, buff, sizeof(buff));
        printf("From client: %s\t To client : ", buff);
        bzero(buff, MAX);
        n = 0;
        while((buff[n++] = getchar()) != '\n');
        write(client_socket, buff, sizeof(buff));
        if(strncmp("exit", buff, 4) == 0){
            printf("Server Exit...\n");
            break;
        }
    }
}

int main() {

  unsigned int server_socket, client_socket, len;
  struct sockaddr_in server_address, client_address;

  server_socket = socket(AF_INET, SOCK_STREAM, 0);
  if( server_socket == -1 ) {
    printf("Socket creation failed...\n");
    exit(0);
  }
  else {
    printf("Socket successfully created..\n");
  }
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(PORT);
  server_address.sin_addr.s_addr = htonl(ADDRESS);

  if(bind(server_socket, (SA*) &server_address, sizeof(server_address)) != 0){
      printf("Socket bind failed...\n");
      exit(0);
  } else {
      printf("Socket bind was successful..\n");
  }

  //verifica se o servidor está ouvindo
  if(listen(server_socket, 5) != 0){
      printf("Listen failed...\n");
      exit(0);
  } else {
      printf("Server listening..\n");
  }

  len = sizeof(client_address);
  
  //verifica se o cliente se conectou 
  client_socket = accept(server_socket, (SA*)&client_address, &len);
  if(client_socket < 0){
      printf("Server accept failed...\n");
      exit(0);
  } else {
      printf("Server accept the client...\n");
  }

  chat(client_socket);

  // FECHA O SOCKET
  close(server_socket);

  return 0;
}
