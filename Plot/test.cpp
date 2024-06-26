#include <bits/stdc++.h>
using namespace std;

#define MAX 212345
typedef pair<int, int> ii;

//VETOR COM OS VALORES CODIFICADOS
int y[] = {3, -3, 1, -1, -3, 1, 3};
int ylen = 7;

//VETOR COM OS VALORES EM PLOT
ii yplotX[MAX];
ii yplotY[MAX];
int st = 0;

void plot(){
  for(int i = 0; i < ylen; i++){
    if(i != 0){
      yplotX[st] = ii(i, i);
      yplotY[st++] = ii(y[i-1], y[i]);
    }
    yplotX[st] = ii(i, i+1);
    yplotY[st++] = ii(y[i], y[i]);
  }
}

int main(){
  plot();
  for(int i = 0; i < st; i++){
    printf("%d %d: %d %d\n", yplotX[i].first, yplotX[i].second, yplotY[i].first, yplotY[i].second);
  }
  return 0;
}
