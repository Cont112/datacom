#include "stdafx.hpp"

void bin_to_str(char* bin, int bin_len, char* str, int* str_len){
  (*str_len)=bin_len/8;
  char* p = str;
  for(int i = 0; i < bin_len; i+=8){
    char c = 0;
    for(int j = 0; j < 8; ++j){
      c = c << 1;
      if(bin[i+j] == '1') c |= 1;
    }
    *p++ = c;
  }
  *p = '\0';
}

void c2b1q_to_bin(char* cod, int cod_len, char* bin, int* bin_len){
  int i, j = 0, pos = 1;
  (*bin_len) = 2*cod_len;
  for(i = 0; i < cod_len; i++){
    if(cod[i] == 'a'){ //-3
      if(pos){
        bin[j++]='1';
        bin[j++]='1';
      }else{
        bin[j++]='0';
        bin[j++]='1';
      }
      pos=0;
    }
    else if(cod[i] == 'b'){ //-1
      if(pos){
        bin[j++]='1';
        bin[j++]='0';
      }else{
        bin[j++]='0';
        bin[j++]='0';
      }
      pos=0;
    }
    else if(cod[i] == 'c'){ //1
      if(pos){
        bin[j++]='0';
        bin[j++]='0';
      }else{
        bin[j++]='1';
        bin[j++]='0';
      }
      pos=1;
    }
    else if(cod[i] == 'd'){ //3
      if(pos){
        bin[j++]='0';
        bin[j++]='1';
      }else{
        bin[j++]='1';
        bin[j++]='1';
      }
      pos=1;
    }
  }
}


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

void GetPrivateKey(unsigned char *privateKey){
  int totiente = (P-1) * (Q-1);
  (*privateKey) = extendedEuclides(E, totiente);
}

string decrypt(char* msg, int msg_len, int privateKey, int modulus){
  string result = msg;
  for(int i = 0; i < result.length(); i++){
    result[i] = PotModN(msg[i], privateKey, modulus);
  }
  return result;
}

void str_to_bin(const char* str, int str_len, char* bin, int* bin_len){
  int i, j;
  (*bin_len)=8*str_len;
  for(i = 0; i < str_len; i++){
    for(j = 0; j < 8; j++){
      bin[i*8+j]= ((str[i] & (1 << 7-j)) >> 7-j) + '0';
    }
  }
}

void bin_to_c2b1q(char* bin, int bin_len, char* cod, int* cod_len){
  int i, j = 0, pos = 1;
  (*cod_len) = bin_len/2;
  for(i = 0; i < bin_len; i+=2){
    if(bin[i] == '0' && bin[i+1] == '0'){
      cod[j++] = (pos ? 'c' : 'b'); // 1 -1
    }
    else if(bin[i] == '0' && bin[i+1] == '1'){
      cod[j++] = (pos ? 'd' : 'a'); // 3 -3
    }
    else if(bin[i] == '1' && bin[i+1] == '0'){
      cod[j++] = (pos ? 'b' : 'c'); // -1 1 
      pos = !pos;
    }
    else if(bin[i] == '1' && bin[i+1] == '1'){
      cod[j++] = (pos ? 'a' : 'd'); // -3 3
      pos = !pos;
    }
    else{
      cod[j++] = '0';
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

string encrypt(char* msg, int msg_len, int publicKey, int modulus){
  string text = msg;
  for(int i = 0; i < text.length(); i++){
    text[i] = PotModN(msg[i], publicKey, modulus);
  }
  return text;

}

string encryptTemp(string& str, int key){
    string result = str;
    const int t = 256;

    for(int i = 0; i < result.length(); i++){
      result[i] = (result[i] + key) % t;
    }
    return result;
}

string decryptTemp(string& str, int key){
    string result = str;
    const int t = 256;

    for(int i = 0; i < result.length(); i++){
      result[i] = (result[i] - key + t) % t;
    }
    return result;
}

void convertToVector(vector<int>& d, string receivedMessage){
    for(int i = 0; i < receivedMessage.length(); i++){
        switch (receivedMessage[i]){
            case 'a':
                d.push_back(-3);
                break;
            case 'b':
                d.push_back(-1);
                break;
            case 'c':
                d.push_back(1);
                break;
            case 'd':
                d.push_back(3);
                break;
                
        }
    }
}