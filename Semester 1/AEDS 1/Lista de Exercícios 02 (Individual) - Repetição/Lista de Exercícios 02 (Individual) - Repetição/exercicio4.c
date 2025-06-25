#include <stdio.h>

/*
     Exercicio - Escrever um algoritmo que lê um valor N 
                 inteiro e positivo e que calcula e escreve o 
                 valor de E
     Autor: Gabriel Azevedo Fernandes
     Data: 19/09/2022
  */
int main(void) 
{
//Declaração de variáveis
double N,E=1, a;
double fat=1, valor;

//Coleta dos valores
printf("Informe o número N: ");
scanf("%lf",&N);

//Condição + cálculo

for (a=1;a<=N;a++)
  {
    for(valor = a; valor > 1; valor--)
      {
        fat=fat*valor;
      }
  E = E + 1/fat;
  }

//Exibe resultado
printf("\nO valor de E é: %.2lf",E);
  }