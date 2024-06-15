#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

void str_to_bin(char* str, int str_len, char* bin, int* bin_len){
  int i, j;
  (*bin_len)=8*str_len;
  for(i = 0; i < str_len; i++){
    for(j = 0; j < 8; j++){
      bin[i*8+j]=((str[i] & (1 << 7-j)) >> 7-j);
    }
  }
}

void bin_to_c2b1q(char* bin, int bin_len, char* cod, int* cod_len){
  int i, j = 0, pos = 1;
  (*cod_len) = bin_len/2;
  for(i = 0; i < bin_len; i+=2){
    if(bin[i] == 0 && bin[i+1] == 0){
      cod[j++] = (pos ? 1 : -1);
    }
    else if(bin[i] == 0 && bin[i+1] == 1){
      cod[j++] = (pos ? 3 : -3);
    }
    else if(bin[i] == 1 && bin[i+1] == 0){
      cod[j++] = (pos ? -1 : 1);
      pos = !pos;
    }
    else if(bin[i] == 1 && bin[i+1] == 1){
      cod[j++] = (pos ? -3 : 3);
      pos = !pos;
    }
    else{
      cod[j++] = 0;
    }
  }
}

int PotModN(int base, int power, int modulus){
  int ans = 1;
  for(int i = 0; i < power & 0xFF; i++){
    ans *= base & 0xFF;
    ans %= modulus & 0xFF;
  }
  return ans & 0xFF;
}

void encrypt(char* msg, int msg_len, int publicKey, int modulus){
  for(int i = 0; i < msg_len; i++){
    msg[i] = PotModN(msg[i], publicKey, modulus);
  }
}

int main(){
  int server_sock;
  struct sockaddr_in server_addr;

  server_sock = socket(PF_INET, SOCK_STREAM, 0);
  if(server_sock < 0){
    return 1;
  }

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(3000);
  server_addr.sin_addr.s_addr = inet_addr("10.181.5.209");
  if(connect(server_sock, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0){
    return 1;
  }

  char rsa_header[2];
  ssize_t bytes_rec = recv(server_sock, rsa_header, sizeof(rsa_header), 0);
  int n = rsa_header[0] & 0xFF;
  int e = rsa_header[1] & 0xFF;
  printf("Public key(e, n): (%d, %d)\n", e, n);

  char message[] = "O pé do zé tem chulé";
  printf("Message: %s\n", message);

  encrypt(message, sizeof(message), e, n);
  printf("Encrypted Message: ");
  for(int i = 0; i < sizeof(message); i++){
    printf("%c", message[i]);
  }
  printf("\n");

  char bin[256];
  int bin_len;
  str_to_bin(message, sizeof(message), bin, &bin_len);
  printf("Binary Message: ");
  for(int i = 0; i < bin_len; i++){
    printf("%d", bin[i]);
  }
  printf("\n");

  char cod[256];
  int cod_len;
  bin_to_c2b1q(bin, bin_len, cod, &cod_len);
  printf("Codification Message: ");
  for(int i = 0; i < cod_len; i++){
    printf("%d ", cod[i]);
  }
  printf("\n");

  FILE *fptr;
  fptr = fopen("client.txt", "w");

  for(int i = 0; i < cod_len; i++){
    fprintf(fptr, "%d %d\n", i, cod[i]);
  }

  fclose(fptr);

  ssize_t bytes_sent = send(server_sock, cod, cod_len, 0);
  printf("Sent %zd Bytes\n", bytes_sent);

  close(server_sock);
  return 0;
}