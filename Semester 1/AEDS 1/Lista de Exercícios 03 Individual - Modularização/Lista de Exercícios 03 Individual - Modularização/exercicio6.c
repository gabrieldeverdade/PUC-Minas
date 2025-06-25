#include <stdio.h>
/* 
     Exercicio -  escrever função que recebe por parâmetro um 
                  valor inteiro e positivo N e retorna o valor 
                  de S
     Autor: Gabriel Azevedo Fernandes
     Data: 24/09/2022
  */

//Módulo para fazer soma
double somatorio (int num)
{

//Declaração de variáveis
double fat,E=1;
double a;

//Repetição para fatorial
while (num>=1)
  {
    a=1;
    for(fat=1;fat<=num;fat++)
      {
        a = fat * a;
      }
    E += (1/a);
    num--;
    }

//Envio do resultado para main
  return (E);
}

int main(void) 
{
//declaração de variáveis
int N;
double soma;

//coleta dos dados
printf("Digite o valor de N: ");
scanf("%d",&N);
    
//Enviar para módulo
soma = somatorio(N);

//exibe na tela
printf("O valor da soma é %.2lf\n",soma);
  }