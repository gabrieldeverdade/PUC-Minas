#include <stdio.h>

/*
    Autor: Gabriel Azevedo Fernandes
       Exercício - Fazer um algoritmo que leia 2 números 
                   inteiros e faça a sua adição. Se o resultado 
                   for maior ou igual a 10, some 5 a este 
                   número. Cao contrário some 7 a ele. Imprima 
                   o resultado final.
    Data: 09/09/2022 
  */

int main(void) 
{
  //Declaração de variáveis
  int num1, num2, soma;

  printf("Digite dois números inteiros: ");
  scanf("%d %d", &num1, &num2);

  soma = num1 + num2;//Adição dos valores informados

  //Condições para que seja feita a soma
  if (soma >= 10)
  {
    printf("\nA soma dos dois valores +5 é igual a: %d", soma+5);//Exibe resultado
  }

  else if (soma <= 9)
  {
    printf("\nA soma dos dois valores +7 é igual a: %d", soma+7);//Exibe resultado
  }
  
  return 0;
}