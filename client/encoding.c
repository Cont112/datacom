#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

wchar_t *string_to_binary(wchar_t *s) {
  if (s == NULL)
    return 0;

  size_t len = wcslen(s); // ignorar o \n

  wchar_t *binary = (wchar_t *)malloc((len * 8 + 1) *
                                      sizeof(wchar_t)); // 8 bits por caractere
  if (binary == NULL)
    return 0;

  wchar_t *p = binary; // ponteiro para percorrer binary
  for (size_t i = 0; i < len; ++i) {
    wchar_t ch = s[i];
    for (int j = 7; j >= 0; --j) {
      *p++ = (ch & 1 << j) ? L'1' : L'0'; // escreve diretamente
    }
  }
  *p = L'\0';
  return binary;
}

wchar_t *binary_to_string(wchar_t *b) {
  if (b == NULL)
    return 0;

  size_t len = wcslen(b);

  if (len % 8 != 0)
    return 0; // verifica se a sequencia de bits pode ser traduzida

  wchar_t *s = (wchar_t *)malloc((len / 8 + 1) *
                                 sizeof(wchar_t)); // 1 caractere por 8 bits
  if (s == NULL)
    return 0;

  wchar_t *p = s; // ponteiro para percorrer s
  for (size_t i = 0; i < len; i += 8) {
    wchar_t ch = 0;
    for (int j = 0; j < 8; ++j) {
      ch = ch << 1; // desloca um bit para a esquerda
      if (b[i + j] == L'1')
        ch |= 1; // se o bit for 1, seta o bit menos significativo
    }
    *p++ = ch;
  }
  *p = L'\0';

  return s;
}

int *encode_2b1q(wchar_t *bits, size_t len) {
  if (bits == NULL)
    return 0;

  int *encoded = (int *)malloc((len + 1) * sizeof(int));

  if (encoded == NULL)
    return 0;

  int j = 0;
  bool prev_value = true; // assume que o valor original positivo
  for (size_t i = 0; i < 2 * len; i += 2) {
    if (bits[i] == L'0' && bits[i + 1] == L'0') {
      if (prev_value) {
        encoded[j] = 1;
        prev_value = true;
      } else {
        encoded[j] = -1;
        prev_value = false;
      }
    } else if (bits[i] == L'0' && bits[i + 1] == L'1') {
      if (prev_value) {
        encoded[j] = 3;
        prev_value = true;
      } else {
        encoded[j] = -3;
        prev_value = false;
      }
    } else if (bits[i] == L'1' && bits[i + 1] == L'0') {
      if (prev_value) {
        encoded[j] = -1;
        prev_value = false;
      } else {
        encoded[j] = 1;
        prev_value = true;
      }
    } else if (bits[i] == L'1' && bits[i + 1] == L'1') {
      if (prev_value) {
        encoded[j] = -3;
        prev_value = false;
      } else {
        encoded[j] = 3;
        prev_value = true;
      }
    }
    j++;
  }
  return encoded;
}

wchar_t *decode_2b1q(int *signal, size_t len) {
  if (signal == NULL)
    return 0;

  wchar_t *decoded = (wchar_t *)malloc((len * 2 + 1) * sizeof(wchar_t));
  if (decoded == NULL)
    return 0;

  bool prev = true;
  for (size_t i = 0; i < 2 * len; i++) {
    if (signal[i] == 3) {
      if (prev) {
        decoded[2 * i] = L'0';
        decoded[2 * i + 1] = L'1';
      } else {
        decoded[2 * i] = L'1';
        decoded[2 * i + 1] = L'1';
      }
      prev = true;
    } else if (signal[i] == 1) {
      if (prev) {
        decoded[2 * i] = L'0';
        decoded[2 * i + 1] = L'0';
      } else {
        decoded[2 * i] = L'1';
        decoded[2 * i + 1] = L'0';
      }
      prev = true;
    } else if (signal[i] == -1) {
      if (prev) {
        decoded[2 * i] = L'1';
        decoded[2 * i + 1] = L'0';
      } else {
        decoded[2 * i] = L'0';
        decoded[2 * i + 1] = L'0';
      }
      prev = false;
    } else if (signal[i] == -3) {
      if (prev) {
        decoded[2 * i] = L'1';
        decoded[2 * i + 1] = L'1';
      } else {
        decoded[2 * i] = L'0';
        decoded[2 * i + 1] = L'1';
      }
      prev = false;
    }
  }
  decoded[2 * len] = L'\0';
  return decoded;
}

void encrypt(wchar_t *s, wchar_t* key) {
}

int main() {
  setlocale(LC_ALL, "en_US.UTF-8");
  wchar_t ch[256];
  wchar_t *bin, *decoded;
  int *encoded;
  wchar_t key[] = L"Arroz";

  if (fgetws(ch, 256, stdin) != NULL) {
      size_t len = wcslen(ch);
      if(ch[len - 1] == L'\n') {
          ch[len - 1] = L'\0';
      }
  }

  //xor_cypher(ch, key);
  //wprintf(L"%ls\n", ch);

  bin = string_to_binary(ch);
  wprintf(L"%ls\n", bin);

  size_t n = wcslen(bin) / 2;
  encoded = encode_2b1q(bin, n);

  for (int i = 0; i < n; i++) {
    wprintf(L"%d ", encoded[i]);
  }
  wprintf(L"\n");

  FILE *fptr;
  fptr = fopen("encoded.txt", "a");
  for (int i = 0; i < n; i++) {
    fprintf(fptr, "%d %d\n ", i, encoded[i]);
  }
  fclose(fptr);

  decoded = decode_2b1q(encoded, n);

  wprintf(L"%ls\n", decoded);

  bin = binary_to_string(decoded);
  wprintf(L"%ls\n", bin);

 // xor_cypher(bin, key);
  //wprintf(L"%ls\n", bin);

  free(bin);
  free(encoded);
  free(decoded);
  return 0;
}
