#include <stdio.h>
/*
    Autor: Gabriel Azevedo Fernandes
       Exercício - Faça um programa para calcular o valor de Y, dado um valor de X
    Data: 09/09/2022 
  */
int main(void) 
{
  //Declaração de variáveis
  double x, y;

  printf("\nInforme o valor de X: ");
  scanf("%lf", &x);

  //Condição + cálculo da função proposta
  if (x <= 1)
  {
    y = 1;
  }
  else if (x <= 2)
  {
    y = 2;
  }
  else if (x <= 3)
  {
    y = x * x;
  }
  else 
  {
    y = x * x * x;
  }

  printf("O valor de Y é igual a: %.2lf\n", y);//Exibe resultado
  return 0;
}
