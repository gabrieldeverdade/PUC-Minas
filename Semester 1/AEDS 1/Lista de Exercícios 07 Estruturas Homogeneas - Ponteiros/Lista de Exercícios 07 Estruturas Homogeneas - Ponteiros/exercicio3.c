#include <stdio.h>

/*
    Exercício 3 
    Autor - Gabriel Azevedo Fernandes
    Data - 27/11/2022
 */
void preencheVetor(int N,double *V){
  for(int i=0;i<N;i++){
    printf("Número %d: ",i+1);
    scanf("%lf",&V[i]);
  }
}

double maiorElemento(int N,double *V){
  int maior=V[0];
  for(int i=1;i<N;i++){
    if(V[i]>maior){
      maior=V[i];
    }
  }
  return maior;
}

int main(void) {
  int N;
  printf("Insira o número total de elementos (1 a 100): ");
  scanf("%d",&N);
  double V[N];
  preencheVetor(N, V);
  printf("O maior elemento é %.2lf\n", maiorElemento(N,V));
  return 0;
}