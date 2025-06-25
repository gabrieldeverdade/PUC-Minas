#include <stdio.h>
#include <stdlib.h>

/*
    Exercício 6 
    Autor - Gabriel Azevedo Fernandes
    Data - 27/11/2022
 */

int main(void) {
  int N, soma = 0;
printf("Insira o número de elementos a serem armazenados no vetor: ");
  scanf("%d", &N);
  printf("Insira %d números de elementos no vetor:\n",N);

  int *vetor = (int *)malloc(N * sizeof(int));

  for (int i = 0; i < N; i++) {
    printf("elemento - %d : ",i);
    scanf("%d", vetor + i);
    soma += *(vetor + i);
  }

  printf("A soma do vetor é: %d\n", soma);

  free(vetor);

  return 0;
}