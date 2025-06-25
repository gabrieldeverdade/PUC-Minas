#include <stdio.h>
/*
     Exercicio - Faça uma função em C para contar os dígitos de um determinado 
                 número usando recursão. Faça um programa principal que leia um 
                 número, acione a função e exiba o resultado gerado 
     Autor: Gabriel Azevedo Fernandes
     Data: 15/10/2022
  */

int calc(int num)//variaveis
//Condições e recursão
{
  if (num /10 == 0)
  {
    return(1);
  }
    
  else
  {
    return(1 + calc(num/10));
  }
  
}

//Leitura de valores e exibe resultado
int main(void) 
{
  int N;
  printf("Digite o número desejado: ");
  scanf("%d",&N);
  printf("O total de dígitos é %d\n",calc(N));
}