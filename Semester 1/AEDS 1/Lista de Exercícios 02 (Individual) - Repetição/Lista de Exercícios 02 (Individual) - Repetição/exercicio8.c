#include <stdio.h>
/*
     Exercicio - Faça um programa que imprima todos os 
                   elementos da série de Fibonacci menores que L 
     Autor: Gabriel Azevedo Fernandes
     Data: 19/09/2022
  */


int main(void) 
{
  //Declaração de variáveis
  int n, t1 = 0, t2 = 1;
  int proxTermo = t1 + t2;

  printf("Informe a quantidade de termos (Limite de termos: 20): ");
  scanf("%d", &n);
  printf("%d, %d",t1, t2);

  //Condições + exibe resultado
  while(proxTermo <= n){

    printf("%d, ", proxTermo);
    t1 = t2; 
    t2 = proxTermo;
    proxTermo = t1 + t2;
  }
  return 0;
}