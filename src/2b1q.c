#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>

wchar_t* string_to_binary(wchar_t* s) {
    if(s == NULL) return 0; 
    size_t len = wcslen(s);

    wchar_t *binary = (wchar_t *) malloc((len*8 + 1) * sizeof(wchar_t)); //8 bits por caractere
    if(binary == NULL) return 0;
    
    wchar_t* p = binary; //ponteiro para percorrer binary
    for(size_t i = 0; i < len; ++i) {
        wchar_t ch = s[i];
        for(int j = 7; j >= 0; --j){
            *p++ = (ch & 1 << j) ? L'1' : L'0'; //escreve diretamente
        }
    }
    *p = L'\0';
    return binary;
}

wchar_t * binary_to_string(wchar_t * b){
  if(b == NULL) return 0;
  size_t len = wcslen(b);
  if(len % 8 != 0) return 0; //verifica se a sequencia de bits pode ser traduzida

  wchar_t *s = (wchar_t *) malloc((len/8 + 1) * sizeof(wchar_t)); //1 caractere por 8 bits
  if(s == NULL) return 0;

  wchar_t *p = s; //ponteiro para percorrer s
  for(size_t i = 0; i < len; i += 8){
    wchar_t ch = 0;
    for(int j = 0; j < 8; ++j){
      ch = ch << 1; //desloca um bit para a esquerda
      if(b[i+j] == L'1') ch |= 1; //se o bit for 1, seta o bit menos significativo
    }
    *p++ = ch;
  }
  *p = L'\0';

  return s;
}

char* encode_2b1q(char* s){
  return NULL;
}

char* decode_2b1q(char* s){
  return NULL;
}

int main(){
  setlocale(LC_ALL, "en_US.UTF-8");
  wchar_t ch[256];

  if (fgetws(ch, 256, stdin) != NULL){
  wprintf(L"%ls\n", string_to_binary(ch));
  wprintf(L"%ls\n", binary_to_string(string_to_binary(ch)));
  }
 

  return 0;
}
