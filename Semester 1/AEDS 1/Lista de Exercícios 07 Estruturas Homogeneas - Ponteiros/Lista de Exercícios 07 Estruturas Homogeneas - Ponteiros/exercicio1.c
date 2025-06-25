#include <stdio.h>
#include <stdlib.h>
/*
    Exercício 1 
    Autor - Gabriel Azevedo Fernandes
    Data - 27/11/2022
 */

#include <stdio.h>

void imprime(int N,int *V){
  printf("Os elementos que você inseriu são: ");
  for(int i=0;i<N;i++){
    printf("elemento - %d : %d\n",i,V[i]);
  }
}

int main(void) {
  int N;
  printf("Insira o número de elementos a serem armazenados no vetor: ");
  scanf("%d", &N);
  printf("Insira %d números de elementos no vetor:\n",N);
  int V[N];
  for(int i=0;i<N;i++){
    printf("elemento - %d : ",i);
    scanf("%d",&V[i]);
  }
  imprime(N,V);
  return 0;
}