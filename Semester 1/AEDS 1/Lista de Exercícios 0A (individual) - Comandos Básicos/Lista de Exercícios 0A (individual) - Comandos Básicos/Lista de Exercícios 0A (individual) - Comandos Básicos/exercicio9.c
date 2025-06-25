#include <stdio.h>
/*
    Autor: Gabriel Azevedo Fernandes
       Exercício - Ler o numerador e denominador 
                   de uma fração e converte-la 
                   para número decimal.
    Data: 02/08/2022 
  */
int main(void) 
{
  //Declaração de variáveis
int num, den; //Valores a serem lidos
  
printf("Digite a fração (Numerador e Denominador): ");
scanf("%d %d", &num, &den);
  
printf("A fração em decimal é: %f\n", 1.0 * num/den); //Exibição de resultado e cálculo de conversão
  return 0;
}