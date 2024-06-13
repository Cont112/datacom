#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <unistd.h>

void bin_to_str(char* bin, int bin_len, char* str, int* str_len){
  int i;
  (*str_len)=bin_len/8;
  for(i = 0; i < bin_len; i++){
    if(i%8==0){
      str[i/8]=0;
    }
    
    str[i/8]+= bin[i]<<(7-i%8);
  }
}

void c2b1q_to_bin(char* cod, int cod_len, char* bin, int* bin_len){
  int i, j = 0, pos = 1;
  (*bin_len) = 2*cod_len;
  for(i = 0; i < cod_len; i++){
    if(cod[i] == -3){
      if(pos){
        bin[j++]=1;
        bin[j++]=1;
      }else{
        bin[j++]=0;
        bin[j++]=1;
      }
      pos=0;
    }
    else if(cod[i] == -1){
      if(pos){
        bin[j++]=1;
        bin[j++]=0;
      }else{
        bin[j++]=0;
        bin[j++]=0;
      }
      pos=0;
    }
    else if(cod[i] == 1){
      if(pos){
        bin[j++]=0;
        bin[j++]=0;
      }else{
        bin[j++]=1;
        bin[j++]=0;
      }
      pos=1;
    }
    else if(cod[i] == 3){
      if(pos){
        bin[j++]=0;
        bin[j++]=1;
      }else{
        bin[j++]=1;
        bin[j++]=1;
      }
      pos=1;
    }
  }
}

#define P 11
#define Q 23
#define N P * Q
#define E 31

int extendedEuclides(int e, int totiente){
    uint32_t decryption_key;

    //equation gakesd the form ye + xphi(n) = 1
    int x1 = 1, x2 = 0;
    int y1 = 0, y2 = 1;
    int q, r;

    while(e != 0)
    {
        q = totiente / e;
        r = totiente % e;
        // phiOfn = q * e + r
        // r = phiOfn - q * e
        // r2 = e - q2 * r
        // r3 = r - q3 * r2

        uint32_t tmp = x2;
        x2 = x1 - q * x2;
        x1 = tmp;

        tmp = y2;
        y2 = y1 - q * y2;
        y1 = tmp;

        totiente = e;
        e = r;
    }
    if (y1 < 0)
    {
        y1 = N + y1;
    }
    decryption_key = y1;
    return decryption_key;}

void GetPrivateKey(int *privateKey){
  int totiente = (P-1) * (Q-1);
  (*privateKey) = extendedEuclides(E, totiente);
}

char PotModN(int base, int power, int modulus){
  int ans = 1;
  for(int i = 0; i < power & 0xFF; i++){
    ans *= base & 0xFF;
    ans %= modulus & 0xFF;
  }
  return ans & 0xFF;
}

void decrypt(char* msg, int msg_len, int privateKey, int modulus){
  for(int i = 0; i < msg_len; i++){
    msg[i] = PotModN(msg[i], privateKey, modulus);
  }
}

int main(){
  int sock, client_sock;
  struct sockaddr_in addr, client_addr;
  socklen_t client_size;

  sock = socket(PF_INET, SOCK_STREAM, 0);
  if(sock < 0){
    return 1;
  }

  addr.sin_family = AF_INET;
  addr.sin_port = htons(3000);
  addr.sin_addr.s_addr = htonl(INADDR_ANY);
  if(bind(sock, (struct sockaddr*) &addr, sizeof(addr)) < 0){
    return 1;
  }

  if(listen(sock, 5) < 0){
    return 1;
  }

  client_size = sizeof(client_addr);
  client_sock = accept(sock, (struct sockaddr*) &client_addr, &client_size);
  if(client_sock < 0){
    return 1;
  }

  int privateKey;
  GetPrivateKey(&privateKey);

  printf("Private Key: %d\n", privateKey);

  char rsa_header[2];
  rsa_header[0] = N;
  rsa_header[1] = E;
  ssize_t bytes_sent = send(client_sock, rsa_header, sizeof(rsa_header), 0);

  char buffer[256];
  ssize_t bytes_rec = recv(client_sock, buffer, sizeof(buffer), 0);
  printf("Recieved %zd Bytes\n", bytes_rec);
  printf("Recieved Message: ");
  for(int i = 0; i < bytes_rec; i++){
    printf("%d ", buffer[i]);
  }
  printf("\n");

  char bin[256];
  int bin_len;
  c2b1q_to_bin(buffer, bytes_rec, bin, &bin_len);
  printf("Binary Message: ");
  for(int i = 0; i < bin_len; i++){
    printf("%d", bin[i]);
  }
  printf("\n");

  char str[256];
  int str_len;
  bin_to_str(bin, bin_len, str, &str_len);
  printf("Encrypted Message: ");
  for(int i = 0; i < str_len; i++){
    printf("%c", str[i]);
  }
  printf("\n");


  decrypt(str, str_len, privateKey, N);
  printf("Message: %s\n", str);
  

  close(sock);
  return 0;
}