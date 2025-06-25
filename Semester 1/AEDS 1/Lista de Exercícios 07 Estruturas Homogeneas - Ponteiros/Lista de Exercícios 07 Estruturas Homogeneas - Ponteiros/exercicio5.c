#include <stdio.h>

/*
    Exercício 5 
    Autor - Gabriel Azevedo Fernandes
    Data - 27/11/2022
 */
void imprime(int N,int *V){
  for(int i=0;i<N;i++){
    printf("%d\n",V[i]);
  }
}

void preenche(int N,int *V){
  for(int i=0;i<N;i++){
    scanf("%d",&V[i]);
  }
}

void ordena(int N,int *V){
  for(int i=0;i<N-1;i++){
    int menor=i;
    for(int j=i+1;j<N;j++){
      if(V[j]<V[menor]){
        menor=j;
      }
    }
    int tmp = V[menor];
    V[menor]=V[i];
    V[i]=tmp;
  }
}

int main(void) {
  int N;
  scanf("%d",&N);
  int V[N];
  preenche(N,V);
  ordena(N,V);
  imprime(N,V);
  return 0;
}