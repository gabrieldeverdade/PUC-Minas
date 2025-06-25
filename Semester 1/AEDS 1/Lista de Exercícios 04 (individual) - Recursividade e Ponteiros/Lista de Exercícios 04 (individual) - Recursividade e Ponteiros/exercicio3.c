#include <stdio.h>
/*
     Exercicio - Faça uma função para encontrar a soma dos dígitos de um 
                 número usando recursão. Faça um programa principal que leia 
                 um número, acione a função e exiba o resultado gerado 
     Autor: Gabriel Azevedo Fernandes
     Data: 15/10/2022
  */

//Declaração de variáveis
int divisao(int nume, int denomi)
{
  //Condições + recursao
  if (nume/denomi == 0)
  {
    return (0);
  } 
  else 
  {
    return (1 + divisao(nume - denomi,denomi));
  }
}

//Leitura de valores + exibe resultado
int main(void) 
{
  int nume, denomi;
  printf("Digite o numerador e o denominador, respectivamente: ");
  scanf("%d %d", &nume, &denomi);
  printf("O resultado da divisão é %d\n", divisao(nume, denomi));
}