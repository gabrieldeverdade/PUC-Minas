#include <stdio.h>
/*
    Autor: Gabriel Azevedo Fernandes
       Exercício - Fazer um programa para ler os coeficientes de uma equação do 
                   primeiro grau (ax + b = 0), calcular e escrever a raiz da 
                   equação
    Data: 09/09/2022 
  */

int main(void) 
{
  //Declaração de variáveis
  double a, b, x=0;

  //Leitura de valores
  printf("Informe os valores de A e B respectivamente: ");
  scanf("%lf %lf", &a, &b);

  x = -b/a; //Cálculo da equação;

    //Exibe resultado
    printf("\nA raiz da equação é %.2lf", x);
  return 0;
}