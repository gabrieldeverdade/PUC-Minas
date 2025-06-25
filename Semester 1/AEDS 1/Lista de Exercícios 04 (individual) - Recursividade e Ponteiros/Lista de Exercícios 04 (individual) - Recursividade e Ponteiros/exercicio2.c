#include <stdio.h>
/*
     Exercicio - Faça uma função para encontrar a soma dos dígitos de um 
                 número usando recursão. Faça um programa principal que leia 
                 um número, acione a função e exiba o resultado gerado 
     Autor: Gabriel Azevedo Fernandes
     Data: 15/10/2022
  */

//Declaração de variáveis
int calc(int num)
//Condições e recursão
{
  if (num / 10 == 0)
  {
    return(num);
  }
  else
  {
    return(num % 10 + calc(num/10));
  }
  
}

//Leitura de valores e Exibe Resultado
int main(void) 
{
  int N;
  printf("Digite o número desejado: ");
  scanf("%d",&N);
  printf("A soma dos dígitos é %d\n",calc(N));
}