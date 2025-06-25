#include <stdio.h>

/* 
     Exercicio -  fazer função que recebe N e retorna o valor de S 
     Autor: Gabriel Azevedo Fernandes
     Data: 25/09/2022
  */

//Módulo
double formula (double valorN)
{
//Declaração de variável
  double S=0;

//estrutura de repet + calc de S
while (valorN>=1)
  {
    S=S + ((valorN*valorN)+1)/(valorN+3);
    valorN--;
  }

//Retornar main
  return (S);
  }

int main(void) 
{

//declaração de variável
int N;
double resultado;
  
//Leitura dos dados
printf("Digite o valor de N: ");
scanf("%d",&N);

//Envia pro módulo
resultado = formula (N);

//Exibe resultado na tela
printf("O resultado é %.2lf\n",resultado);
}