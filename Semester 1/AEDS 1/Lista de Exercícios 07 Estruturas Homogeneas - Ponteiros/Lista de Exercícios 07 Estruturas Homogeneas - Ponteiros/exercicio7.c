#include <stdio.h>

/*
    Exercício 7 
    Autor - Gabriel Azevedo Fernandes
    Data - 27/11/2022
 */
void preencheVetor(int n,int *V){
  for(int i=0;i<n;i++){
    scanf("%d",&V[i]);
  }
}

void inverteVetor(int n,int *V){
  for(int i=0;i<n-1;i++){
    int maior=i;
    for(int j=i+1;j<n;j++){
      if(V[j]>V[maior]){
        maior=j;
      }
    }
    int tmp = V[i];
    V[i]=V[maior];
    V[maior]=tmp;
  }
}

void imprimeVetor(int n,int *V){
  for(int i=n-1;i>=0;i--){
    printf("%d\n",V[i]);
  }
}

int main(void) {
  int n;
  scanf("%d",&n);
  int V[n];
  preencheVetor(n,V);
  imprimeVetor(n,V);
}