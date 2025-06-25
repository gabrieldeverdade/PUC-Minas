#include <stdio.h>
/*
     Exercicio - Faça um programa que imprima os L primeiros  
                   elementos da série de Fibonacci. Por exemplo,  
                   se o usuário digitou o número 40, deverão ser  
                   apresentados os 40 números da sequência na 
                   tela. 
     Autor: Gabriel Azevedo Fernandes
     Data: 19/09/2022
  */
int main(void) 
{
  //Declaração de variáveis
  int i, n, t1 = 0, t2 = 1, proxTermo;

  printf("Informe a quantidade de termos:");
  scanf("%i", &n);

  for(i = 1; i <= n; i++){

    //Exibe resultado
    printf("%i, ", t1);
    proxTermo = t1 +t2; // somando o primeiro termo mais o segundo termo t1 + t2 = 1
    t1 = t2; // 1
    t2 = proxTermo; // 0 1 1  = t1 = 1 t2 = 1 // 0 1 1
  }
  return 0;
}