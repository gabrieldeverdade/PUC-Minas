#include <stdio.h>

/*
     Exercicio - Escreva um algoritmo que lê um valor n inteiro 
                 e positivo e que calcula a soma proposta
     Autor: Gabriel Azevedo Fernandes
     Data: 19/09/2022
  */

int main(void) 
{

//Declaração de variáveis

double S = 0, N, termo;

//Coleta de valores
printf("Informe um número número: ");
scanf("%lf",&N);

//Condição da repetição
if (N < 0)
{
  printf("Valor inválido\n");
}
  else
  
//Estrutura da repetição até somar todos termos
{
  while (N>=1)
    {
      S = S + (1/N);
      termo = 1/N;
      N--;
      printf ("%.2lf ",termo);
    }}
  
//Exibe resultado
printf("\nO valor da soma é: %.2lf\n",S);
  }