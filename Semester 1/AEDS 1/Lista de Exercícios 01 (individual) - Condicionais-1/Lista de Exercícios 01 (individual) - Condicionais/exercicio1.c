#include <stdio.h>

/*
    Autor: Gabriel Azevedo Fernandes
       Exercício - Dado dois números, imprimir o maior deles
    Data: 09/09/2022 
  */

int main(void) 
{
  //Declaração de variáveis
  int num1, num2;
  
  printf("\tImprimir o Maior Valor Informado!");
  printf("\n\nDigite dois números inteiros: ");
  scanf("%d %d", &num1, &num2);

  //condições para que seja exibido o maior valor
  if (num1 >= num2) //Se o num1 for maior ou igual a num2 --> num1 é exibido
  {
    printf("\n\nO maior valor é: %d", num1);
  }

  else if (num2 >= num1)//Se o num2 for maior ou igual a num1 --> num2 é exibido
  {
    printf("\n\nO maior valor é: %d", num2);
  }
  return 0;
}