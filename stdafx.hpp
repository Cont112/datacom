#pragma once
#include <bits/stdc++.h>
#include <raylib.h>
#include <string>
#include <bitset>


#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800
#define OUTER_PADDING 5
#define INNER_PADDING 10
#define RATIO_2_5 2./5
#define RATIO_3_5 3./5
#define RATIO_1_2 1./2
#define FONT_SPACING 1


#define P 11
#define Q 23

#define N P * Q
#define E 31



using namespace std;

void str_to_bin(const char* str, int str_len, char* bin, int* bin_len);
void bin_to_c2b1q(char* bin, int bin_len, char* cod, int* cod_len);
int PotModN(int base, int power, int modulus);
string encrypt(char* msg, int msg_len, int publicKey, int modulus);
void bin_to_str(char* bin, int bin_len, char* str, int* str_len);
void c2b1q_to_bin(char* cod, int cod_len, char* bin, int* bin_len);
int extendedEuclides(int e, int totiente);
void GetPrivateKey(unsigned char *privateKey);
void decrypt(char* msg, int msg_len, int privateKey, int modulus);
string encryptTemp(string& str, int key);
string decryptTemp(string& str, int key);
void convertToVector(vector<int>& d, string receivedMessage);
