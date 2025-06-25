#include <stdio.h>
/*       
     Exercicio - Faça uma função recursiva que calcula o valor de S da série a 
                 seguir para n > 0:  S= 1/1!+1/2!+1/3!+...+1/N! double serie 
                 (int n) Faça um programa principal que leia um número, acione 
                 a função e exiba o resultado gerado
     Autor: Gabriel Azevedo Fernandes
     Data: 15/10/2022
  */

//Declaração de variáveis
int fat(int num)
{
  //condições e recursão
  int fatorial=1;
  while(num > 1)
    {
      fatorial *= num;
      num--;
    }
  return (fatorial);
}
double serie(int n)
{
  if (n == 1)
  {
    return(1);
  }
  else
  {
    return ((1.0/fat(n)) + serie(n-1));
  }
}

//Main (Leitura e exibe resultado)
int main(void)
{
  int N;
  double S;
  printf("Digite o número de termos: ");
  scanf("%d",&N);
  if (N <= 0)
  {
    printf("Valor inválido\n");
  }
  else
  {

  S=serie(N);
  printf("O valor da soma é %.2lf\n",S);
  }
}